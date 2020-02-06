#pragma once
#include <Windows.h>
#include "Vector.h"
#include "UVCoords.h"
class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(const Vertex& other);

	// Accessors
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float z);
	float GetW() const;
	void SetW(const float w);
	Vector GetNormal() const;
	void SetNormal(const Vector& normal);
	COLORREF GetColour() const;
	void SetColour(const COLORREF& colour);
	int GetPolygonCount() const;
	void SetPolygonCount(int count);
	UVCoords GetUV() const;
	void SetUV(UVCoords uv);
	float GetPreTransformZ() const;
	void SetPreTransformZ(float preZ);
	float GetZRecip() const;
	void SetZRecip(float zRecip);

	// Operators
	Vertex& operator= (const Vertex& rhs);
	bool operator== (const Vertex& rhs) const;
	const Vector operator+ (const Vertex& rhs) const;
	const Vector operator- (const Vertex& rhs) const;

	void DehomogenizeVertex();
private:
	float _x;
	float _y;
	float _z;
	float _w;
	Vector _normal;
	UVCoords _uv;
	float _zRecip{ 0 };
	COLORREF _colour{ RGB(0, 0, 0) };
	int _polygonCount{ 0 };
	float _preTransformZ{ 0 };
};

