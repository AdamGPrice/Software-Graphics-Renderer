#pragma once
#include <Windows.h>
#include "Vector.h"

class Polygon3D
{
public:
	Polygon3D();
	~Polygon3D();
	Polygon3D(int index0, int index1, int index2, int uvIndex0, int uvIndex1, int uvIndex2);
	Polygon3D(const Polygon3D& other);

	// Accessors
	int GetVertexIndex(int i) const;
	int GetUVIndex(int i) const;
	bool GetCulled() const;
	void SetCulled(bool cull);
	Vector GetNormal() const;
	void SetNormal(const Vector& normal);
	float GetZDepth() const;
	void SetZDepth(float zDepth);
	COLORREF GetColour() const;
	void SetColour(const COLORREF& colour);

	Polygon3D& operator= (const Polygon3D& rhs);
private:
	int _vertexIndices[3];
	int _uvIndices[3];
	bool _culled;
	Vector _normal;
	float _zDepth;
	COLORREF _colour;
};
