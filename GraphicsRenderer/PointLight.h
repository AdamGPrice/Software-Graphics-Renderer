#pragma once
#include "Vertex.h"
#include "Vector.h"
#include <windows.h>

class PointLight
{
public:
	PointLight();
	PointLight(const Vertex& position, const COLORREF& colour, float a, float b, float c);
	PointLight(const PointLight& other);

	Vertex GetPosition() const;
	void SetPosition(const Vertex& position);
	COLORREF GetColour() const;
	void SetColour(const COLORREF& colour);
	float CalculateAttenuation(float distance) const;

	PointLight& operator= (const PointLight& rhs);

private:
	Vertex _position;
	COLORREF _colour;
	float _attentuation[3] = { 0.0f };
};

