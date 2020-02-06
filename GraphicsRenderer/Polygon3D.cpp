#include "Polygon3D.h"

Polygon3D::Polygon3D()
{
	_vertexIndices[0] = 0;
	_vertexIndices[1] = 0;
	_vertexIndices[2] = 0;
	_uvIndices[0] = 0;
	_uvIndices[1] = 0;
	_uvIndices[2] = 0;
	_culled = false;
	_zDepth = 0.0f;
	_colour = RGB(0, 0, 0);
}

Polygon3D::~Polygon3D()
{

}

Polygon3D::Polygon3D(int index0, int index1, int index2, int uvIndex0, int uvIndex1, int uvIndex2)
{
	_vertexIndices[0] = index0;
	_vertexIndices[1] = index1;
	_vertexIndices[2] = index2;
	_uvIndices[0] = uvIndex0;
	_uvIndices[1] = uvIndex1;
	_uvIndices[2] = uvIndex2;
	_culled = false;
	_zDepth = 0.0f;
	_colour = RGB(0, 0, 0);
}

Polygon3D::Polygon3D(const Polygon3D& other)
{
	_vertexIndices[0] = other.GetVertexIndex(0);
	_vertexIndices[1] = other.GetVertexIndex(1);
	_vertexIndices[2] = other.GetVertexIndex(2);
	_uvIndices[0] = other.GetUVIndex(0);
	_uvIndices[1] = other.GetUVIndex(1);
	_uvIndices[2] = other.GetUVIndex(2);
	_culled = other.GetCulled();
	_normal = other.GetNormal();
	_zDepth = other.GetZDepth();
	_colour = other.GetColour();
}

int Polygon3D::GetVertexIndex(int i) const
{
	return _vertexIndices[i];
}

int Polygon3D::GetUVIndex(int i) const
{
	return _uvIndices[i];
}

bool Polygon3D::GetCulled() const
{
	return _culled;
}

void Polygon3D::SetCulled(bool cull)
{
	_culled = cull;
}

Vector Polygon3D::GetNormal() const
{
	return _normal;
}

void Polygon3D::SetNormal(const Vector& normal)
{
	_normal = normal;
}

float Polygon3D::GetZDepth() const
{
	return _zDepth;
}

void Polygon3D::SetZDepth(float zDepth)
{
	_zDepth = zDepth;
}

COLORREF Polygon3D::GetColour() const
{
	return _colour;
}

void Polygon3D::SetColour(const COLORREF& colour)
{
	_colour = colour;
}

Polygon3D& Polygon3D::operator=(const Polygon3D& rhs)
{
	if (this != &rhs)
	{
		_vertexIndices[0] = rhs.GetVertexIndex(0);
		_vertexIndices[1] = rhs.GetVertexIndex(1);
		_vertexIndices[2] = rhs.GetVertexIndex(2);
		_uvIndices[0] = rhs.GetUVIndex(0);
		_uvIndices[1] = rhs.GetUVIndex(1);
		_uvIndices[2] = rhs.GetUVIndex(2);
		_culled = rhs.GetCulled();
		_normal = rhs.GetNormal();
		_zDepth = rhs.GetZDepth();
		_colour = rhs.GetColour();
	}
	return *this;
}
