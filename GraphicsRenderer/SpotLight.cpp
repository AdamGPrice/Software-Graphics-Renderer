#include "SpotLight.h"

SpotLight::SpotLight()
{
}

SpotLight::SpotLight(const Vertex& position, const Vector& direction, const COLORREF& colour, float a, float b, float c, float innerAngle, float outerAngle)
{
	_position = position;
	_direction = direction;
	_colour = colour;
	_attentuation[0] = a;
	_attentuation[1] = b;
	_attentuation[2] = c;
	_innerAngle = innerAngle;
	_outerAngle = outerAngle;
}

SpotLight::SpotLight(const SpotLight& other)
{
	_position = other.GetPosition();
	_direction = other.GetDirection();
	_colour = other.GetColour();
	_attentuation[0] = other._attentuation[0];
	_attentuation[1] = other._attentuation[1];
	_attentuation[2] = other._attentuation[2];
	_innerAngle = other.GetInnerAngle();
	_outerAngle = other.GetOuterAngle();
}

Vertex SpotLight::GetPosition() const
{
	return _position;
}

void SpotLight::SetPosition(const Vertex& position)
{
	_position = position;
}

Vector SpotLight::GetDirection() const
{
	return _direction;
}

void SpotLight::SetDirection(const Vector& direction)
{
	_direction = direction;
}

COLORREF SpotLight::GetColour() const
{
	return _colour;
}

void SpotLight::SetColour(const COLORREF& colour)
{
	_colour = colour;
}

float SpotLight::GetInnerAngle() const
{
	return _innerAngle;
}

void SpotLight::SetInnerAngle(float angle)
{
	_innerAngle = angle;
}

float SpotLight::GetOuterAngle() const
{
	return _outerAngle;
}

void SpotLight::SetOuterAngle(float angle)
{
	_outerAngle = angle;
}

float SpotLight::CalculateAttenuation(float d) const
{
	float a = _attentuation[0];
	float b = _attentuation[1];
	float c = _attentuation[2];
	return 1.0f / (a + (b * d) + (c * (d * d)));
}

SpotLight& SpotLight::operator=(const SpotLight& rhs)
{
	if (this != &rhs)
	{
		_position = rhs.GetPosition();
		_direction = rhs.GetDirection();
		_colour = rhs.GetColour();
		_attentuation[0] = rhs._attentuation[0];
		_attentuation[1] = rhs._attentuation[1];
		_attentuation[2] = rhs._attentuation[2];
		_innerAngle = rhs.GetInnerAngle();
		_outerAngle = rhs.GetOuterAngle();
	}
	return *this;
}
