#include "Model.h"
#include "RGBColour.h"
#include <algorithm>
#include <array>
#include <cmath>

Model::Model()
{
}

Model::~Model()
{
}

const std::vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

const std::vector<Vertex>& Model::GetLocalVertices()
{
	return _localVertices;
}

const std::vector<Vertex>& Model::GetTransformedVertices()
{
	return _transformedVertices;
}

const std::vector<UVCoords>& Model::GetUVCoords()
{
	return _uvCoords;
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

size_t Model::GetVertexCount() const
{
	return _localVertices.size();
}

Texture& Model::GetTexture()
{
	return _texture;
}

void Model::AddVertex(float x, float y, float z)
{
	_localVertices.push_back(Vertex(x, y, z));
}

void Model::AddPolygon(int i0, int i1, int i2, int uvIndex0, int uvIndex1, int uvIndex2)
{
	_polygons.push_back(Polygon3D(i0, i1, i2, uvIndex0, uvIndex1, uvIndex2));
}

void Model::AddTextureUV(float u, float v)
{
	_uvCoords.push_back(UVCoords(u, v));
}

void Model::DehomogenizeVertices()
{
	for (Vertex& vertex : _transformedVertices)
	{
		vertex.DehomogenizeVertex();
	}
}

void Model::ApplyTransformToLocalVertices(const Matrix& transform)
{
	_transformedVertices.clear();
	_transformedVertices.reserve(_localVertices.size()); 
	for (Vertex& vertex : _localVertices)
	{
		_transformedVertices.push_back(transform * vertex);
	}
}

void Model::ApplyTransformToTransformedVertices(const Matrix& transform)
{
	for (Vertex& vertex : _transformedVertices)
	{
		vertex = transform * vertex;
	}
}

void Model::CalculateBackfaces(const Vertex& cameraPos)
{
	for (Polygon3D& polygon : _polygons)
	{
		// Get the Vertices that make up the polygon.
		Vertex v0 = _transformedVertices[polygon.GetVertexIndex(0)];
		Vertex v1 = _transformedVertices[polygon.GetVertexIndex(1)];
		Vertex v2 = _transformedVertices[polygon.GetVertexIndex(2)];

		// Create the normal vector for the polygon and normalise it.
		Vector a = v0 - v2;
		Vector b = v0 - v1;
		Vector normal = Vector::CrossProduct(b, a);
		// Save the normal to the polygon
		polygon.SetNormal(normal);

		// Create the vector from the polygon to the camera.
		// Then get the dot product between that vector and the normal 
		// to check the polygon is facing us.
		Vector eyeVector = cameraPos - v0;
		if (Vector::DotProdcut(normal, eyeVector) < 0.0f)
		{
			polygon.SetCulled(true);
		}
		else
		{
			polygon.SetCulled(false);
		}
	}
}

void Model::CalculateVertexNormals()
{
	// Reset normals first
	for (Vertex& vertex : _transformedVertices)
	{
		vertex.SetNormal(Vector(0.0f, 0.0f, 0.0f));
		vertex.SetPolygonCount(0);
	}

	for (Polygon3D& polygon : _polygons)
	{
		for (int i = 0; i < 3; i++)
		{
			Vertex& vertex = _transformedVertices[polygon.GetVertexIndex(i)];
			vertex.SetNormal(vertex.GetNormal() + polygon.GetNormal());
			vertex.SetPolygonCount(vertex.GetPolygonCount() + 1);
		}
	}

	for (Vertex& vertex : _transformedVertices)
	{
		vertex.SetNormal(vertex.GetNormal() / (float)vertex.GetPolygonCount());
	}
}

void Model::Sort()
{
	for (Polygon3D& polygon : _polygons)
	{
		// Calculate the z depth of each polygon
		float zDepth = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			zDepth += _transformedVertices[polygon.GetVertexIndex(i)].GetZ();
		}
		polygon.SetZDepth(zDepth / 3);
	}

	// Sort the polygons by their z depth from the camera
	std::sort(_polygons.begin(), _polygons.end(), [](const Polygon3D& a, const Polygon3D& b) 
	{
			return a.GetZDepth() > b.GetZDepth();
	});
}

void Model::CalculateAmbientLighting(const AmbientLight& light)
{
	// Light up the polygons with a uniform ambient colour 
	RGBColour lightColour(light.GetColour());
	RGBColour total = lightColour * _ambient;

	for (Polygon3D& polygon : _polygons)
	{
		polygon.SetColour(total.GetColorref());
	}

	// Same for vertex lighting
	for (Vertex& vertex : _transformedVertices)
	{
		vertex.SetColour(total.GetColorref());
	}
}

void Model::CalculateDirectionalLighting(std::vector<DirectionalLight> lights)
{
	for (Polygon3D& polygon : _polygons)
	{
		RGBColour total(polygon.GetColour());

		for (DirectionalLight& light : lights)
		{
			// If the angle is more than 90 Degrees (less than 0 dot product) 
			// don't bother calculating anything, 0 light will be added to the polygons colour
			float angle = Vector::DotProdcut(Vector::Normalise(light.GetDirection() * -1), Vector::Normalise(polygon.GetNormal()));
			if (angle > 0.0f)
			{
				total = total + (RGBColour(light.GetColour()) * _diffuse * angle);
			}
		}
		total.ClampColour();
		polygon.SetColour(total.GetColorref());
	}
}

void Model::CalculatePointLighting(std::vector<PointLight> lights)
{
	for (Polygon3D& polygon : _polygons)
	{
		RGBColour total(polygon.GetColour());

		for (PointLight& light : lights)
		{
			// Get the Vector to the light source, the length of that vector and normalise it
			Vertex polyPos = _transformedVertices[polygon.GetVertexIndex(0)];
			Vector lightDir = light.GetPosition() - polyPos;
			float distance = lightDir.Magnitude();
			lightDir.Normalise();

			float angle = Vector::DotProdcut(lightDir, Vector::Normalise(polygon.GetNormal()));
			if (angle > 0.0f)
			{
				// Calculate the attenuation for this light given a distance
				float attenuation = light.CalculateAttenuation(distance);
				total = total + (RGBColour(light.GetColour()) * _diffuse * angle * attenuation);
			}
		}
		total.ClampColour();
		polygon.SetColour(total.GetColorref());
	}
}

void Model::CalculateVertexDirectionalLighting(std::vector<DirectionalLight> lights, Vertex cameraPos)
{
	for (Vertex& vertex : _transformedVertices)
	{
		RGBColour total(vertex.GetColour());

		for (DirectionalLight& light : lights)
		{
			Vector lightDir = Vector::Normalise(light.GetDirection() * -1);
			float angle = Vector::DotProdcut(lightDir, Vector::Normalise(vertex.GetNormal()));
			if (angle > 0.0f)
			{
				RGBColour diffuseColour = RGBColour(light.GetColour());
				diffuseColour = diffuseColour * _diffuse * angle;
				total = total + diffuseColour;

				// Specular Lighting
				Vector eyeVector = Vector::Normalise(cameraPos - vertex);
				Vector halfWayVector = (lightDir + eyeVector) / (lightDir.Magnitude() + eyeVector.Magnitude());

				float specularAngle = Vector::DotProdcut(Vector::Normalise(vertex.GetNormal()), halfWayVector);
				if (specularAngle > 0.0f) {
					RGBColour specularColour = RGBColour(light.GetColour()) * _specular * pow(specularAngle, _shininess) * 3;
					total = total + specularColour;
				}
			}
		}
		total.ClampColour();
		vertex.SetColour(total.GetColorref());
	}
}

void Model::CalculateVertexPointLighting(std::vector<PointLight> lights, Vertex cameraPos)
{
	for (Vertex& vertex : _transformedVertices)
	{
		RGBColour total(vertex.GetColour());

		for (PointLight& light : lights)
		{

			// Get the Vector to the light source, the length of that vector and normalise it
			Vector lightDir = light.GetPosition() - vertex;
			float distance = lightDir.Magnitude();

			// If the angle is more than 90 Degrees (less than 0 dot product) 
			// don't bother calculating anything, 0 light will be added to the polygons colour
			float angle = Vector::DotProdcut(Vector::Normalise(lightDir), Vector::Normalise(vertex.GetNormal()));
			if (angle > 0.0f)
			{
				// Calculate the attenuation for this light given a distance
				float attenuation = light.CalculateAttenuation(distance);
				
				RGBColour diffuseColour = RGBColour(light.GetColour()) * _diffuse * angle * attenuation;
				total = total + diffuseColour;

				// Specular Lighting
				Vector eyeVector = Vector::Normalise(cameraPos - vertex);
				Vector halfWayVector = (lightDir + eyeVector) / (lightDir.Magnitude() + eyeVector.Magnitude());

				float specularAngle = Vector::DotProdcut(Vector::Normalise(vertex.GetNormal()), halfWayVector);
				if (specularAngle > 0.0f) {
					RGBColour specularColour = RGBColour(light.GetColour()) * _specular * pow(specularAngle, _shininess) * attenuation * 3;
					total = total + specularColour;
				}
			}
		}
		total.ClampColour();
		vertex.SetColour(total.GetColorref());
	}
}

void Model::CalcualteVertexSpotLighting(std::vector<SpotLight> lights, Vertex cameraPos)
{
	for (Vertex& vertex : _transformedVertices)
	{
		RGBColour total(vertex.GetColour());

		for (SpotLight& light : lights)
		{
			// Get the Vector to the light source, the length of that vector and normalise it
			Vector lightDir = light.GetPosition() - vertex;
			float distance = lightDir.Magnitude();

			// Calculate the attenuation for this light given a distance
			float attenuation = light.CalculateAttenuation(distance);

			float angle = Vector::DotProdcut(Vector::Normalise(lightDir), Vector::Normalise(vertex.GetNormal()));
			if (angle > 0.0f)
			{
				float spotAngle = Vector::DotProdcut(Vector::Normalise(lightDir * -1), Vector::Normalise(light.GetDirection()));
				if (spotAngle < cos(light.GetOuterAngle()))
				{
					// Don't add any light
				}
				else if (spotAngle > cos(light.GetInnerAngle()))
				{
					// Add the max amount of light
					RGBColour diffuseColour = RGBColour(light.GetColour()) * _diffuse * angle * attenuation;
					total = total + diffuseColour;
				}
				else
				{
					float t = (spotAngle - cos(light.GetOuterAngle())) / (cos(light.GetInnerAngle() - cos(light.GetOuterAngle())));
					float result = (3.0f - 2.0f * t) * (t * t);
					// Add the a fall of light between the outer and inner angles
					RGBColour diffuseColour = RGBColour(light.GetColour()) * _diffuse * angle * attenuation * result;
					total = total + diffuseColour;
				}
			}
		}
		total.ClampColour();
		vertex.SetColour(total.GetColorref());
	}
}

void Model::SetBackfaces(bool culled)
{
	for (Polygon3D& polygon : _polygons)
	{
		polygon.SetCulled(culled);
	}
}
