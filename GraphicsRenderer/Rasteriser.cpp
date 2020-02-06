#include "Rasteriser.h"

Rasteriser app;

bool Rasteriser::Initialise()
{
	if (!MD2Loader::LoadModel("MD2Models/marvin.md2", "MD2Models/marvin.pcx", _model,
		&Model::AddPolygon,
		&Model::AddVertex,
		&Model::AddTextureUV))
	{
		return false;
	}

	// Create objects for the scene
	_camera = Camera(0.0f, 0.0f, 0.0f, Vertex(0.0f, 0.0f, -45.0f));
	_ambientLight = AmbientLight(RGB(255, 255, 255));
	//_directionalLights.push_back(DirectionalLight(Vector(1.0f, -0.2f, 0.6f), RGB(255, 255, 255)));
	//_pointLights.push_back(PointLight(Vertex(15.0f, 10.0f, -20.0f), RGB(0, 0, 255), 1.0f, 0.05f, 0.0f));
	return true;
}

void Rasteriser::Update(const Bitmap& bitmap)
{
	// Displaying the code
	if (_frameCount < 50)
	{
		_state = RenderStates::Wireframe;
		_displayText = L"Wireframe";
	}
	else if (_frameCount < 140)
	{
		_displayText = L"Wireframe: X Rotation";
		_xAngle += 4.0f;
	}
	else if (_frameCount < 230)
	{
		_displayText = L"Wireframe: Y Rotation";
		_yAngle += 4.0f;
	}
	else if (_frameCount < 320)
	{
		_displayText = L"Wireframe: Z Rotation";
		_zAngle += 4.0f;
	}
	else if (_frameCount < 340)
	{
		_displayText = L"Wireframe: X Scale";
		_xScale += 0.1f;
	}
	else if (_frameCount < 360)
	{
		_xScale -= 0.1f;
	}
	else if (_frameCount < 380)
	{
		_displayText = L"Wireframe: Y Scale";
		_yScale += 0.1f;
	}
	else if (_frameCount < 400)
	{
		_yScale -= 0.1f;
	}
	else if (_frameCount < 420)
	{
		_displayText = L"Wireframe: Z Scale";
		_zScale += 0.1f;
	}
	else if (_frameCount < 440)
	{
		_zScale -= 0.1f;
	}
	else if (_frameCount < 460)
	{
		_displayText = L"Wireframe: X Tanslation";
		_xOff += 3.0f;
	}
	else if (_frameCount < 480)
	{
		_xOff -= 3.0f;
	}
	else if (_frameCount < 500)
	{
		_displayText = L"Wireframe: Y Tanslation";
		_yOff += 3.0f;
	}
	else if (_frameCount < 520)
	{
		_yOff -= 3.0f;
	}
	else if (_frameCount < 540)
	{
		_displayText = L"Wireframe: Z Tanslation";
		_zOff += 5.0f;
	}
	else if (_frameCount < 560)
	{
		_zOff -= 5.0f;
	}
	else if (_frameCount < 650)
	{
		_state = RenderStates::WireframeCulled;
		_displayText = L"Wireframe: Backface Culling + Sorting";
	}
	else if (_frameCount < 740)
	{
		_state = RenderStates::GDISolidFlat;
		_displayText = L"GDI Solid Flat: Ambient Lighting";
	}
	else if (_frameCount < 810)
	{
		_displayText = L"GDI Solid Flat: Directional Light";
		if (_frameCount == 740)
		{
			_directionalLights.push_back(DirectionalLight(Vector(1.0f, -0.2f, 0.6f), RGB(255, 255, 255)));
		}
	}
	else if (_frameCount < 880)
	{
		_displayText = L"GDI Solid Flat: Point Light";
		if (_frameCount == 810)
		{
			_pointLights.push_back(PointLight(Vertex(15.0f, 10.0f, -20.0f), RGB(0, 0, 255), 1.0f, 0.05f, 0.0f));
		}
	}
	else if (_frameCount < 920)
	{
		_state = RenderStates::MySolidFlat;
		_displayText = L"Solid Flat: My Rasterization Code";
	}
	else if (_frameCount < 965)
	{
		_state = RenderStates::GouraudShading;
		_displayText = L"Goraud Shading: Specular Highlights";
	}
	else if (_frameCount < 1000)
	{
		_displayText = L"Goraud Shading: Spot Light";
		if (_frameCount == 965)
		{
			_spotLights.push_back(SpotLight(Vertex(0.0f, 0.0f, -25), Vector(0.0f, 0.0f, 1.0f), RGB(255, 0, 0), 1.0f, 0.01f, 0.0f, 8.0f, 12.0f));
		}
	}
	else if (_frameCount < 1200)
	{
		_state = RenderStates::Textured;
		_displayText = L"Textured With Perspective Correction";
	}
	else
	{
		_state = RenderStates::Wireframe;
		_frameCount = 0;
		_xAngle = 0.0f;
		_yAngle = 0.0f;
		_zAngle = 0.0f;
		_xOff = 0.0f;
		_yOff = 0.0f;
		_zOff = 0.0f;
		_xScale = 1.0f;
		_yScale = 1.0f;
		_zScale = 1.0f;

		//Reset faced to not be culled
		_model.SetBackfaces(false);
		_directionalLights.clear();
		_pointLights.clear();
		_spotLights.clear();
	}
	_frameCount++;

	if (_frameCount >= 560)
	{
		_yAngle += 2.0f;
	}

	_modelTransformation = Matrix::TranslationMatrix(_xOff, _yOff, _zOff) * Matrix::ScalingMatrix(_xScale, _yScale, _zScale) * Matrix::XYZRotationMatrix(_xAngle, _yAngle, _zAngle);
	GeneratePerspectiveMatrix(1.0f, (float)bitmap.GetWidth() / (float)bitmap.GetHeight());
	GenerateScreenMatrix(1.0f, bitmap.GetWidth(), bitmap.GetHeight());
}

void Rasteriser::Render(const Bitmap& bitmap)
{
	bitmap.Clear(RGB(0, 0, 0));

	// Pick which rendering state to use 
	switch (_state)
	{
	case RenderStates::Wireframe:
		_model.ApplyTransformToLocalVertices(_modelTransformation);
		ProjectionCalculations();

		DrawWireFrame(bitmap.GetDC());
		break;
	case RenderStates::WireframeCulled:
		_model.ApplyTransformToLocalVertices(_modelTransformation);
		_model.CalculateBackfaces(_camera.GetPosition());
		ProjectionCalculations();

		DrawWireFrame(bitmap.GetDC());
		break;
	case RenderStates::GDISolidFlat:
		_model.ApplyTransformToLocalVertices(_modelTransformation);
		_model.CalculateBackfaces(_camera.GetPosition());
		_model.CalculateAmbientLighting(_ambientLight);
		_model.CalculateDirectionalLighting(_directionalLights);
		_model.CalculatePointLighting(_pointLights);
		ProjectionCalculations();

		DrawSolidFlat(bitmap.GetDC());
		break;
	case RenderStates::MySolidFlat:
		_model.ApplyTransformToLocalVertices(_modelTransformation);
		_model.CalculateBackfaces(_camera.GetPosition());
		_model.CalculateAmbientLighting(_ambientLight);
		_model.CalculateDirectionalLighting(_directionalLights);
		_model.CalculatePointLighting(_pointLights);
		ProjectionCalculations();

		MyDrawSolidFlat(bitmap.GetDC());
		break;
	case RenderStates::GouraudShading:
		_model.ApplyTransformToLocalVertices(_modelTransformation);
		_model.CalculateBackfaces(_camera.GetPosition());
		_model.CalculateVertexNormals();
		_model.CalculateAmbientLighting(_ambientLight);
		_model.CalculateVertexDirectionalLighting(_directionalLights, _camera.GetPosition());
		_model.CalculateVertexPointLighting(_pointLights, _camera.GetPosition());
		_model.CalcualteVertexSpotLighting(_spotLights, _camera.GetPosition());
		ProjectionCalculations();

		DrawGouraud(bitmap.GetDC());
		break;
	case RenderStates::Textured:
		_model.ApplyTransformToLocalVertices(_modelTransformation);
		_model.CalculateBackfaces(_camera.GetPosition());
		_model.CalculateVertexNormals();
		_model.CalculateAmbientLighting(_ambientLight);
		_model.CalculateVertexDirectionalLighting(_directionalLights, _camera.GetPosition());
		_model.CalculateVertexPointLighting(_pointLights, _camera.GetPosition());
		_model.CalcualteVertexSpotLighting(_spotLights, _camera.GetPosition());
		ProjectionCalculations();

		DrawSolidTextured(bitmap.GetDC());
		break;
	default:
		break;
	}

	DrawString(bitmap, _displayText.c_str());
}

void Rasteriser::ProjectionCalculations()
{
	_model.ApplyTransformToTransformedVertices(_camera.GetViewMatrix());
	_model.Sort();
	_model.ApplyTransformToTransformedVertices(_perspectiveTransformation);
	_model.DehomogenizeVertices();
	_model.ApplyTransformToTransformedVertices(_screenTransformation);
}

void Rasteriser::DrawWireFrame(const HDC& hdc)
{
	std::vector<Vertex> vertices = _model.GetTransformedVertices();
	std::vector<Polygon3D> polygons = _model.GetPolygons();

	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	HGDIOBJ oldPen = SelectObject(hdc, pen);

	for (const Polygon3D& polygon : polygons)
	{
		if (!polygon.GetCulled()) 
		{
			// Move to last vertex and draw a line to each vertex in the polygon
			Vertex lastVertex = vertices[polygon.GetVertexIndex(2)];
			MoveToEx(hdc, (int)lastVertex.GetX(), (int)lastVertex.GetY(), NULL);
			for (int i = 0; i < 3; i++)
			{
				Vertex v = vertices[polygon.GetVertexIndex(i)];
				LineTo(hdc, (int)v.GetX(), (int)v.GetY());
			}
		}
	}

	SelectObject(hdc, oldPen);
	DeleteObject(pen);
}

void Rasteriser::DrawSolidFlat(const HDC& hdc)
{
	std::vector<Vertex> vertices = _model.GetTransformedVertices();
	std::vector<Polygon3D> polygons = _model.GetPolygons();

	for (Vertex& vertex : vertices)
	{
		vertex.SetX(std::floor(vertex.GetX()));
		vertex.SetY(std::floor(vertex.GetY()));
	}

	for (const Polygon3D& polygon : polygons)
	{
		if (!polygon.GetCulled())
		{
			// Create pen and brush but store a refernce to old ones
			HPEN pen = CreatePen(PS_SOLID, 0, polygon.GetColour());
			HBRUSH brush = CreateSolidBrush(polygon.GetColour());
			HGDIOBJ oldPen = SelectObject(hdc, pen);
			HGDIOBJ oldBrush = SelectObject(hdc, brush);

			POINT verts[3];
			for (int i = 0; i < 3; i++)
			{
				Vertex v = vertices[polygon.GetVertexIndex(i)];
				verts[i] = { (long)v.GetX(), (long)v.GetY() };
			}

			Polygon(hdc, verts, 3);

			// Delete pen and brush select old ones
			SelectObject(hdc, oldPen);
			SelectObject(hdc, oldBrush);
			DeleteObject(pen);
			DeleteObject(brush);
		}
	}
}

void Rasteriser::MyDrawSolidFlat(const HDC& hdc)
{
	std::vector<Vertex> vertices = _model.GetTransformedVertices();
	std::vector<Polygon3D> polygons = _model.GetPolygons();

	// floor all the x and y's before rasterising
	for (Vertex& vertex : vertices)
	{
		vertex.SetX(std::floor(vertex.GetX()));
		vertex.SetY(std::floor(vertex.GetY()));
	}

	for (const Polygon3D& polygon : polygons)
	{
		if (!polygon.GetCulled())
		{
			std::vector<Vertex> polygonVertices;
			polygonVertices.reserve(3);
			for (int i = 0; i < 3; i++)
			{
				polygonVertices.push_back(vertices[polygon.GetVertexIndex(i)]);
			}
			FillPolygonFlat(hdc, polygonVertices, polygon.GetColour());
		}
	}
}

void Rasteriser::FillPolygonFlat(const HDC& hdc, std::vector<Vertex> vertices, COLORREF colour)
{
	// Sort the three vertices into descending order by their y-coordinate
	std::sort(vertices.begin(), vertices.end(), [](const Vertex& a, const Vertex& b)
	{
		return a.GetY() < b.GetY();
	});

	Vertex v0 = vertices[0];
	Vertex v1 = vertices[1];
	Vertex v2 = vertices[2];

	if ((int)v1.GetY() == (int)v2.GetY())
	{
		FillBottomTriangleFlat(hdc, v0, v1, v2, colour);
	}
	else if ((int)v0.GetY() == (int)v1.GetY())
	{
		FillTopTriangleFlat(hdc, v0, v1, v2, colour);
	}
	else
	{
		Vertex v3(v0.GetX() + ((v1.GetY() - v0.GetY()) / (v2.GetY() - v0.GetY()) * (v2.GetX() - v0.GetX())), v1.GetY(), 1.0f);
		FillBottomTriangleFlat(hdc, v0, v1, v3, colour);
		FillTopTriangleFlat(hdc, v1, v3, v2, colour);
	}
}

void Rasteriser::FillBottomTriangleFlat(const HDC& hdc, const Vertex& v0, const Vertex& v1, const Vertex& v2, COLORREF colour)
{
	float slope1 = (v1.GetX() - v0.GetX()) / (v1.GetY() - v0.GetY());
	float slope2 = (v2.GetX() - v0.GetX()) / (v2.GetY() - v0.GetY());

	float x1 = v0.GetX();
	float x2 = v0.GetX() + 0.5f;

	if (slope2 < slope1)
	{
		float slopeTmp = slope1;
		slope1 = slope2;
		slope2 = slopeTmp;
	}

	for (int y = (int)v0.GetY(); y <= (int)v1.GetY(); y++)
	{
		for (int x = (int)x1 + 1; x <= (int)x2; x++)
		{
			SetPixelV(hdc, x, y, colour);
		}
		x1 += slope1;
		x2 += slope2;
	}
}

void Rasteriser::FillTopTriangleFlat(const HDC& hdc, const Vertex& v0, const Vertex& v1, const Vertex& v2, COLORREF colour)
{
	float slope1 = (v2.GetX() - v0.GetX()) / (v2.GetY() - v0.GetY());
	float slope2 = (v2.GetX() - v1.GetX()) / (v2.GetY() - v1.GetY());

	float x1 = v2.GetX();
	float x2 = v2.GetX() + 0.5f;

	if (slope1 < slope2)
	{
		float slopeTmp = slope1;
		slope1 = slope2;
		slope2 = slopeTmp;
	}

	for (int y = (int)v2.GetY(); y > (int)v0.GetY(); y--)
	{
		for (int x = (int)x1 + 1; x <= (int)x2; x++)
		{
			SetPixelV(hdc, x, y, colour);
		}
		x1 -= slope1;
		x2 -= slope2;
	}
}

void Rasteriser::DrawGouraud(const HDC& hdc)
{
	std::vector<Vertex> vertices = _model.GetTransformedVertices();
	std::vector<Polygon3D> polygons = _model.GetPolygons();

	for (Vertex& vertex : vertices)
	{
		vertex.SetX(std::floor(vertex.GetX()));
		vertex.SetY(std::floor(vertex.GetY()));
	}

	for (const Polygon3D& polygon : polygons)
	{
		if (!polygon.GetCulled())
		{
			std::vector<Vertex> polygonVertices;
			polygonVertices.reserve(3);
			for (int i = 0; i < 3; i++)
			{
				polygonVertices.push_back(vertices[polygon.GetVertexIndex(i)]);
			}
			FillPolygonGouraud(hdc, polygonVertices);
		}
	}
}

void Rasteriser::FillPolygonGouraud(const HDC& hdc, std::vector<Vertex> vertices)
{
	// Sort the three vertices into descending order by their y-coordinate
	std::sort(vertices.begin(), vertices.end(), [](const Vertex& a, const Vertex& b)
	{
		return a.GetY() < b.GetY();
	});

	Vertex v0 = vertices[0];
	Vertex v1 = vertices[1];
	Vertex v2 = vertices[2];

	if ((int)v1.GetY() == (int)v2.GetY())
	{
		FillBottomTriangleGouraud(hdc, v0, v1, v2);
	}
	else if ((int)v0.GetY() == (int)v1.GetY())
	{
		FillTopTriangleGouraud(hdc, v0, v1, v2);
	}
	else
	{
		float slope = (v1.GetY() - v0.GetY()) / (v2.GetY() - v0.GetY());
		//Get a new Vertex;
		Vertex v3(v0.GetX() + slope * (v2.GetX() - v0.GetX()), v1.GetY(), 1.0f);
		// Put Vertex Colours into RGBColour classes for easier manipulation
		RGBColour c0(v0.GetColour());
		RGBColour c2(v2.GetColour());
		RGBColour newColour = c0 + ((c2 - c0) * slope);
		v3.SetColour(newColour.GetColorref());

		FillBottomTriangleGouraud(hdc, v0, v1, v3);
		FillTopTriangleGouraud(hdc, v1, v3, v2);
	}
}

void Rasteriser::FillBottomTriangleGouraud(const HDC& hdc, const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	float slope1 = (v1.GetX() - v0.GetX()) / (v1.GetY() - v0.GetY());
	float slope2 = (v2.GetX() - v0.GetX()) / (v2.GetY() - v0.GetY());

	float x1 = v0.GetX();
	float x2 = v0.GetX() + 0.5f;

	// Put Vertex Colours into RGBColour classes for easier manipulation
	RGBColour c0(v0.GetColour());
	RGBColour c1(v1.GetColour());
	RGBColour c2(v2.GetColour());

	/* get the change of color components along edge (v1, v0) */
	float diff1 = 1 / (v1.GetY() - v0.GetY());
	RGBColour colourSlope1 = (c1 - c0) * diff1;
	/* get the change of color components along edge (v2, v0) */
	float diff2 = 1 / (v2.GetY() - v0.GetY());
	RGBColour colourSlope2 = (c2 - c0) * diff2;
	/* get starting values */
	RGBColour colour1 = c0;
	RGBColour colour2 = c0;

	// Swap bottom vertices so slope1 is on the left side if not already
	if (slope2 < slope1)
	{
		float slopeTmp = slope1;
		slope1 = slope2;
		slope2 = slopeTmp;

		RGBColour tempColour = colourSlope1;
		colourSlope1 = colourSlope2;
		colourSlope2 = tempColour;
	}

	for (int y = (int)v0.GetY(); y <= (int)v1.GetY(); y++)
	{
		for (int x = (int)x1 + 1; x <= (int)x2; x++)
		{
			// cast to int then back to floats for division
			float t = (x - x1) / (x2 - x1);
			RGBColour output = colour1 * (1 - t) + colour2 * t;
			SetPixelV(hdc, x, y, output.GetColorref());
		}
		// Coordinate slopes
		x1 += slope1;
		x2 += slope2;
		// RGB slopes
		colour1 = colour1 + colourSlope1;
		colour2 = colour2 + colourSlope2;
	}
}

void Rasteriser::FillTopTriangleGouraud(const HDC& hdc, const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	float slope1 = (v2.GetX() - v0.GetX()) / (v2.GetY() - v0.GetY());
	float slope2 = (v2.GetX() - v1.GetX()) / (v2.GetY() - v1.GetY());

	float x1 = v2.GetX();
	float x2 = v2.GetX() + 0.5f;

	// Put Vertex Colours into RGBColour classes for easier manipulation
	RGBColour c0(v0.GetColour());
	RGBColour c1(v1.GetColour());
	RGBColour c2(v2.GetColour());

	/* get the change of color components along edge (v2,v0) */
	float diff1 = 1 / (v2.GetY() - v0.GetY());
	RGBColour colourSlope1 = (c2 - c0) * diff1;
	/* get the change of color components along edge (v2,v1) */
	float diff2 = 1 / (v2.GetY() - v1.GetY());
	RGBColour colourSlope2 = (c2 - c1) * diff2;
	/* set starting values */
	RGBColour colour1 = c2;
	RGBColour colour2 = c2;

	if (slope1 < slope2)
	{
		float slopeTmp = slope1;
		slope1 = slope2;
		slope2 = slopeTmp;

		RGBColour tempColour = colourSlope1;
		colourSlope1 = colourSlope2;
		colourSlope2 = tempColour;
	}

	for (int y = (int)v2.GetY(); y > (int)v0.GetY(); y--)
	{
		for (int x = (int)x1 + 1; x <= (int)x2; x++)
		{
			float t = (x - x1) / (x2 - x1);
			RGBColour output = colour1 * (1 - t) + colour2 * t;
			SetPixelV(hdc, x, y, output.GetColorref());
		}
		x1 -= slope1;
		x2 -= slope2;

		colour1 = colour1 - colourSlope1;
		colour2 = colour2 - colourSlope2;
	}
}

void Rasteriser::DrawSolidTextured(const HDC& hdc)
{
	std::vector<Vertex> vertices = _model.GetTransformedVertices();
	std::vector<Polygon3D> polygons = _model.GetPolygons();
	std::vector<UVCoords> uvs = _model.GetUVCoords();

	for (Vertex& vertex : vertices)
	{
		vertex.SetX(std::floor(vertex.GetX()));
		vertex.SetY(std::floor(vertex.GetY()));
	}

	for (const Polygon3D& polygon : polygons)
	{
		if (!polygon.GetCulled())
		{
			std::vector<Vertex> polygonVertices;
			polygonVertices.reserve(3);
			for (int i = 0; i < 3; i++)
			{
				Vertex vertex = vertices[polygon.GetVertexIndex(i)];
				vertex.SetUV(uvs[polygon.GetUVIndex(i)] / vertex.GetPreTransformZ());
				vertex.SetZRecip(1 / vertex.GetPreTransformZ());
				polygonVertices.push_back(vertex);
			}
			FillSolidTextured(hdc, polygonVertices);
		}
	}
}

void Rasteriser::FillSolidTextured(const HDC& hdc, std::vector<Vertex> vertices)
{
	// Sort the three vertices into descending order by their y-coordinate
	std::sort(vertices.begin(), vertices.end(), [](const Vertex& a, const Vertex& b)
	{
		return a.GetY() < b.GetY();
	});

	Vertex v0 = vertices[0];
	Vertex v1 = vertices[1];
	Vertex v2 = vertices[2];

	if ((int)v1.GetY() == (int)v2.GetY())
	{
		FillBottomTriangleTextured(hdc, v0, v1, v2);
	}
	else if ((int)v0.GetY() == (int)v1.GetY())
	{
		FillTopTriangleTextured(hdc, v0, v1, v2);
	}
	else
	{
		// Create a new vertex to split the triangle into two
		float slope = (v1.GetY() - v0.GetY()) / (v2.GetY() - v0.GetY());
		// Get a new Vertex Position;
		Vertex v3(v0.GetX() + slope * (v2.GetX() - v0.GetX()), v1.GetY(), 1.0f);
		// interpolate the new colour for the vertex
		RGBColour c0(v0.GetColour());
		RGBColour c2(v2.GetColour());
		RGBColour newColour = c0 + ((c2 - c0) * slope);
		v3.SetColour(newColour.GetColorref());
		// interpolate the new uv coords for the vertex
		UVCoords newUV = v0.GetUV() + ((v2.GetUV() - v0.GetUV()) * slope);
		v3.SetUV(newUV);
		// interpolate the new zRecip for the vertex
		v3.SetZRecip(v0.GetZRecip() + (v2.GetZRecip() - v0.GetZRecip()) * slope);

		FillBottomTriangleTextured(hdc, v0, v1, v3);
		FillTopTriangleTextured(hdc, v1, v3, v2);
	}
}

void Rasteriser::FillBottomTriangleTextured(const HDC& hdc, const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	float slope1 = (v1.GetX() - v0.GetX()) / (v1.GetY() - v0.GetY());
	float slope2 = (v2.GetX() - v0.GetX()) / (v2.GetY() - v0.GetY());

	float x1 = v0.GetX();
	float x2 = v0.GetX() + 0.5f;

	// Put Vertex Colours into RGBColour classes for easier manipulation
	RGBColour c0(v0.GetColour());
	RGBColour c1(v1.GetColour());
	RGBColour c2(v2.GetColour());

	float diff1 = 1 / (v1.GetY() - v0.GetY());
	float diff2 = 1 / (v2.GetY() - v0.GetY());
	/* get the change of color components along edge (v1, v0) */
	RGBColour colourSlope1 = (c1 - c0) * diff1;
	/* get the change of color components along edge (v2, v0) */
	RGBColour colourSlope2 = (c2 - c0) * diff2;
	/* get starting values */
	RGBColour colour1 = c0;
	RGBColour colour2 = c0;

	UVCoords uvSlope1 = (v1.GetUV() - v0.GetUV()) * diff1;
	UVCoords uvSlope2 = (v2.GetUV() - v0.GetUV()) * diff2;
	UVCoords uv1 = v0.GetUV();
	UVCoords uv2 = v0.GetUV();

	float recipSlope1 = (v1.GetZRecip() - v0.GetZRecip()) * diff1;
	float recipSlope2 = (v2.GetZRecip() - v0.GetZRecip()) * diff2;
	float recip1 = v0.GetZRecip();
	float recip2 = v0.GetZRecip();

	// Swap bottom vertices so slope1 is on the left side if not already
	if (slope2 < slope1)
	{
		float slopeTmp = slope1;
		slope1 = slope2;
		slope2 = slopeTmp;

		RGBColour tempColour = colourSlope1;
		colourSlope1 = colourSlope2;
		colourSlope2 = tempColour;

		UVCoords tempUV = uvSlope1;
		uvSlope1 = uvSlope2;
		uvSlope2 = tempUV;

		float tempSlope = recipSlope1;
		recipSlope1 = recipSlope2;
		recipSlope2 = tempSlope;
	}

	for (int y = (int)v0.GetY(); y <= (int)v1.GetY(); y++)
	{
		for (int x = (int)x1 + 1; x <= (int)x2; x++)
		{
			float t = (x - x1) / (x2 - x1);
			RGBColour lighting = colour1 * (1 - t) + colour2 * t;
			float recip = recip1 * (1 - t) + recip2 * t;
			UVCoords uv = (uv1 * (1 - t) + uv2 * t) / recip;
			RGBColour textureColour(_model.GetTexture().GetTextureValue((int)uv.GetU(), (int)uv.GetV()));
			textureColour = textureColour * (lighting / 100);
			textureColour.ClampColour();
			SetPixelV(hdc, x, y, textureColour.GetColorref());
		}
		// Coordinates
		x1 += slope1;
		x2 += slope2;
		// RGB interpolation offset
		colour1 = colour1 + colourSlope1;
		colour2 = colour2 + colourSlope2;
		// UV interpolation offset
		uv1 = uv1 + uvSlope1;
		uv2 = uv2 + uvSlope2;
		// zRecup interpolation offset
		recip1 = recip1 + recipSlope1;
		recip2 = recip2 + recipSlope2;
	}
}

void Rasteriser::FillTopTriangleTextured(const HDC& hdc, const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	float slope1 = (v2.GetX() - v0.GetX()) / (v2.GetY() - v0.GetY());
	float slope2 = (v2.GetX() - v1.GetX()) / (v2.GetY() - v1.GetY());

	float x1 = v2.GetX();
	float x2 = v2.GetX() + 0.5f;

	// Put Vertex Colours into RGBColour classes for easier manipulation
	RGBColour c0(v0.GetColour());
	RGBColour c1(v1.GetColour());
	RGBColour c2(v2.GetColour());

	float diff1 = 1 / (v2.GetY() - v0.GetY());
	float diff2 = 1 / (v2.GetY() - v1.GetY());
	/* get the change of color components along edge (v2,v0) */
	RGBColour colourSlope1 = (c2 - c0) * diff1;
	/* get the change of color components along edge (v2,v1) */
	RGBColour colourSlope2 = (c2 - c1) * diff2;
	/* set starting values */
	RGBColour colour1 = c2;
	RGBColour colour2 = c2;

	UVCoords uvSlope1 = (v2.GetUV() - v0.GetUV()) * diff1;
	UVCoords uvSlope2 = (v2.GetUV() - v1.GetUV()) * diff2;
	UVCoords uv1 = v2.GetUV();
	UVCoords uv2 = v2.GetUV();

	float recipSlope1 = (v2.GetZRecip() - v0.GetZRecip()) * diff1;
	float recipSlope2 = (v2.GetZRecip() - v1.GetZRecip()) * diff2;
	float recip1 = v2.GetZRecip();
	float recip2 = v2.GetZRecip();

	if (slope1 < slope2)
	{
		float slopeTmp = slope1;
		slope1 = slope2;
		slope2 = slopeTmp;

		RGBColour tempColour = colourSlope1;
		colourSlope1 = colourSlope2;
		colourSlope2 = tempColour;

		UVCoords tempUV = uvSlope1;
		uvSlope1 = uvSlope2;
		uvSlope2 = tempUV;

		float tempSlope = recipSlope1;
		recipSlope1 = recipSlope2;
		recipSlope2 = tempSlope;
	}

	for (int y = (int)v2.GetY(); y > (int)v0.GetY(); y--)
	{
		for (int x = (int)x1 + 1; x <= (int)x2; x++)
		{
			float t = (x - x1) / (x2 - x1);
			RGBColour lighting = colour1 * (1 - t) + colour2 * t;
			float recip = recip1 * (1 - t) + recip2 * t;
			UVCoords uv = (uv1 * (1 - t) + uv2 * t) / recip;
			RGBColour textureColour(_model.GetTexture().GetTextureValue((int)uv.GetU(), (int)uv.GetV()));
			textureColour = textureColour * (lighting / 100);
			textureColour.ClampColour();
			SetPixelV(hdc, x, y, textureColour.GetColorref());
		}
		x1 -= slope1;
		x2 -= slope2;
		// RGB interpolation offset
		colour1 = colour1 - colourSlope1;
		colour2 = colour2 - colourSlope2;
		// UV interpolation offset
		uv1 = uv1 - uvSlope1;
		uv2 = uv2 - uvSlope2;
		// zRecup interpolation offset
		recip1 = recip1 - recipSlope1;
		recip2 = recip2 - recipSlope2;
	}
}

void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	_perspectiveTransformation = Matrix({ d / aspectRatio, 0, 0, 0,
										  0, d, 0, 0,
										  0, 0, d, 0,
										  0, 0, 1, 0 });
}

void Rasteriser::GenerateScreenMatrix(float d, int width, int height)
{
	float w = (float)width / 2;
	float h = (float)height / 2;

	_screenTransformation = Matrix({ w,  0,  0,   w,
									 0, -h,  0,   h,
									 0,  0, d/2, d/2,
									 0,  0,  0,   1 });
}

void Rasteriser::DrawString(const Bitmap& bitmap, LPCTSTR text)
{
	HDC hdc = bitmap.GetDC();
	HFONT hFont, hOldFont;

	// Retrieve a handle to the variable stock font.  
	hFont = hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Myfont"));

	// Select the variable stock font into the specified device context. 
	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));

		// Display the text string.  
		TextOut(hdc, 10, 10, text, lstrlen(text));

		// Restore the original font.        
		SelectObject(hdc, hOldFont);
	}
	DeleteObject(hFont);
}