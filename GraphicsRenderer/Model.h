#pragma once
#include "Polygon3D.h"
#include "Vertex.h"
#include "Matrix.h"
#include "UVCoords.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Texture.h"
#include <vector>
#include <array>

class Model
{
public:
	Model();
	~Model();
	// Accessors
	const std::vector<Polygon3D>& GetPolygons();
	const std::vector<Vertex>& GetLocalVertices();
	const std::vector<Vertex>& GetTransformedVertices();
	const std::vector<UVCoords>& GetUVCoords();
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;
	Texture& GetTexture();
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2, int uvIndex0, int uvIndex1, int uvIndex2);
	void AddTextureUV(float u, float v);

	void DehomogenizeVertices();
	void ApplyTransformToLocalVertices(const Matrix& transform);
	void ApplyTransformToTransformedVertices(const Matrix& transform);
	void CalculateBackfaces(const Vertex& cameraPos);
	void CalculateVertexNormals();
	void Sort();
	void CalculateAmbientLighting(const AmbientLight& light);
	void CalculateDirectionalLighting(std::vector<DirectionalLight> lights);
	void CalculatePointLighting(std::vector<PointLight> lights);
	void CalculateVertexDirectionalLighting(std::vector<DirectionalLight> lights, Vertex CameraPos);
	void CalculateVertexPointLighting(std::vector<PointLight> lights, Vertex cameraPos);
	void CalcualteVertexSpotLighting(std::vector<SpotLight> lights, Vertex cameraPos);

	void SetBackfaces(bool culled);

private:
	std::vector<Polygon3D> _polygons;
	std::vector<Vertex> _localVertices;
	std::vector<Vertex> _transformedVertices;
	std::vector<UVCoords> _uvCoords;
	Texture _texture;

	std::array<float, 3> _ambient{ 0.05f, 0.05f, 0.05f };
	std::array<float, 3> _diffuse{ 0.5f, 0.5f, 0.5f };
	std::array<float, 3> _specular{ 1.0f, 1.0f, 1.0f };
	float _shininess{ 8.0f };
};