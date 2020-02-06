#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	_colour = RGB(0, 0, 0);
}

DirectionalLight::DirectionalLight(const Vector& direction, const COLORREF& colour)
{
	_direction = direction;
	_colour = colour;
}

DirectionalLight::DirectionalLight(const DirectionalLight& other)
{
	_direction = other.GetDirection();
	_colour = other.GetColour();
}

Vector DirectionalLight::GetDirection() const
{
	return _direction;
}

void DirectionalLight::SetDirection(const Vector& direction)
{
	_direction = direction;
}

COLORREF DirectionalLight::GetColour() const
{
	return _colour;
}

void DirectionalLight::SetColour(const COLORREF& colour)
{
	_colour = colour;
}

DirectionalLight& DirectionalLight::operator=(const DirectionalLight& rhs)
{
	if (this != &rhs)
	{
		_direction = rhs.GetDirection();
		_colour = rhs.GetColour();
	}
	return *this;
}
