#include "PointLight.h"

PointLight::PointLight()
{
}

PointLight::PointLight(const Vertex& position, const COLORREF& colour, float a, float b, float c)
{
	_position = position;
	_colour = colour;
	_attentuation[0] = a;
	_attentuation[1] = b;
	_attentuation[2] = c;
}

PointLight::PointLight(const PointLight& other)
{
	_position = other.GetPosition();
	_colour = other.GetColour();
	_attentuation[0] = other._attentuation[0];
	_attentuation[1] = other._attentuation[1];
	_attentuation[2] = other._attentuation[2];
}

Vertex PointLight::GetPosition() const
{
	return _position;
}

void PointLight::SetPosition(const Vertex& position)
{
	_position = position;
}

COLORREF PointLight::GetColour() const
{
	return _colour;
}

void PointLight::SetColour(const COLORREF& colour)
{
	_colour = colour;
}

float PointLight::CalculateAttenuation(float d) const
{
	float a = _attentuation[0];
	float b = _attentuation[1];
	float c = _attentuation[2];
	return 1.0f / (a + (b * d) + (c * (d * d)));
}

PointLight& PointLight::operator=(const PointLight& rhs)
{
	if (this != &rhs)
	{
		_position = rhs.GetPosition();
		_colour = rhs.GetColour();
		_attentuation[0] = rhs._attentuation[0];
		_attentuation[1] = rhs._attentuation[1];
		_attentuation[2] = rhs._attentuation[2];
	}
	return *this;
}
