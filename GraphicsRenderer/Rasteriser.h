#pragma once
#include "Framework.h"
#include "Model.h"
#include "Matrix.h"
#include "Vertex.h"
#include "MD2Loader.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "RGBColour.h"
#include <cmath>
#include <vector>
#include <string>

enum class RenderStates
{
	Wireframe,
	WireframeCulled,
	GDISolidFlat,
	MySolidFlat,
	GouraudShading,
	Textured
};

class Rasteriser : public Framework
{
public:
	bool Initialise();
	void Update(const Bitmap& bitmap);
	void Render(const Bitmap& bitmap);
	void DrawWireFrame(const HDC& hdc);
	void DrawSolidFlat(const HDC& hdc);
	// Solid flat fill
	void MyDrawSolidFlat(const HDC& hdc);
	void FillPolygonFlat(const HDC& hdc, std::vector<Vertex> vertices, COLORREF colour);
	void FillBottomTriangleFlat(const HDC& hdc, const Vertex& v0, const Vertex& v1, const Vertex& v2, COLORREF colour);
	void FillTopTriangleFlat(const HDC& hdc, const Vertex& v0, const Vertex& v1, const Vertex& v2, COLORREF colour);
	// Gouraud shading
	void DrawGouraud(const HDC& hdc);
	void FillPolygonGouraud(const HDC& hdc, std::vector<Vertex> vertices);
	void FillBottomTriangleGouraud(const HDC& hdc, const Vertex& v0, const Vertex& v1, const Vertex& v2);
	void FillTopTriangleGouraud(const HDC& hdc, const Vertex& v0, const Vertex& v1, const Vertex& v2);
	// Texture shading
	void DrawSolidTextured(const HDC& hdc);
	void FillSolidTextured(const HDC& hdc, std::vector<Vertex> vertices);
	void FillBottomTriangleTextured(const HDC& hdc, const Vertex& v0, const Vertex& v1, const Vertex& v2);
	void FillTopTriangleTextured(const HDC& hdc, const Vertex& v0, const Vertex& v1, const Vertex& v2);

	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateScreenMatrix(float d, int width, int height);

	void DrawString(const Bitmap& bitmap, LPCTSTR text);
	void ProjectionCalculations();
private:
	Model _model;
	Camera _camera;
	AmbientLight _ambientLight;
	std::vector<DirectionalLight> _directionalLights;
	std::vector<PointLight> _pointLights;
	std::vector<SpotLight> _spotLights;

	Matrix _modelTransformation;
	Matrix _perspectiveTransformation;
	Matrix _screenTransformation;

	// Model Properties
	float _xAngle{ 0.0f };
	float _yAngle{ 0.0f };
	float _zAngle{ 0.0f };
	float _xOff{ 0.0f };
	float _yOff{ 0.0f };
	float _zOff{ 0.0f };
	float _xScale{ 1.0f };
	float _yScale{ 1.0f };
	float _zScale{ 1.0f };

	// For displaying purposes
	int _frameCount{ 0 };
	std::wstring _displayText = L"";
	RenderStates _state = RenderStates::Wireframe;
};

