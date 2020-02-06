#include "Vertex.h"

Vertex::Vertex()
	: _x(0.0f), _y(0.0f), _z(0.0f), _w(1.0f)
{
}

Vertex::Vertex(float x, float y, float z)
	: _x(x), _y(y), _z(z), _w(1.0f)
{
}

Vertex::Vertex(const Vertex& other)
	: _x(other.GetX()), _y(other.GetY()), _z(other.GetZ()), _w(other.GetW())
{
	SetNormal(other.GetNormal());
	SetColour(other.GetColour());
	SetPolygonCount(other.GetPolygonCount());
	SetUV(other.GetUV());
	SetZRecip(other.GetZRecip());
	SetPreTransformZ(other.GetPreTransformZ());
}

float Vertex::GetX() const
{
	return _x;
}

void Vertex::SetX(const float x)
{
	_x = x;
}

float Vertex::GetY() const
{
	return _y;
}

void Vertex::SetY(const float y)
{
	_y = y;
}

float Vertex::GetZ() const
{
	return _z;
}

void Vertex::SetZ(const float z)
{
	_z = z;
}

float Vertex::GetW() const
{
	return _w;
}

void Vertex::SetW(const float w)
{
	_w = w;
}

Vector Vertex::GetNormal() const
{
	return _normal;
}

void Vertex::SetNormal(const Vector& normal)
{
	_normal = normal;
}

COLORREF Vertex::GetColour() const
{
	return _colour;
}

void Vertex::SetColour(const COLORREF& colour)
{
	_colour = colour;
}

int Vertex::GetPolygonCount() const
{
	return _polygonCount;
}

void Vertex::SetPolygonCount(int count)
{
	_polygonCount = count;
}

UVCoords Vertex::GetUV() const
{
	return _uv;
}

void Vertex::SetUV(UVCoords uv)
{
	_uv = uv;
}

float Vertex::GetPreTransformZ() const
{
	return _preTransformZ;
}

void Vertex::SetPreTransformZ(float preZ)
{
	_preTransformZ = preZ;
}

float Vertex::GetZRecip() const
{
	return _zRecip;
}

void Vertex::SetZRecip(float zRecip)
{
	_zRecip = zRecip;
}

Vertex& Vertex::operator=(const Vertex& rhs)
{
	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
		_w = rhs.GetW();
		_normal = rhs.GetNormal();
		_colour = rhs.GetColour();
		_polygonCount = rhs.GetPolygonCount();
		_uv = rhs.GetUV();
		_zRecip = rhs.GetZRecip();
		_preTransformZ = rhs.GetPreTransformZ();
	}
	return *this;
}

bool Vertex::operator==(const Vertex& rhs) const
{
	return _x == rhs.GetX() && _y == rhs.GetY() && _z == rhs.GetZ() && _w == rhs.GetW();
}

const Vector Vertex::operator+(const Vertex& rhs) const
{
	return Vector(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ());
}

const Vector Vertex::operator-(const Vertex& rhs) const
{
	return Vector(_x - rhs.GetX(), _y - rhs.GetY(), _z - rhs.GetZ());
}

void Vertex::DehomogenizeVertex()
{
	SetPreTransformZ(GetW());
	SetX(GetX() / GetW());
	SetY(GetY() / GetW());
	SetZ(GetZ() / GetW());
	SetW(GetW() / GetW());
}
