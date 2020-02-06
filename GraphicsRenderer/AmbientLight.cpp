#include "AmbientLight.h"

AmbientLight::AmbientLight()
{
	_colour = RGB(0, 0, 0);
}

AmbientLight::AmbientLight(const COLORREF& colour)
{
	_colour = colour;
}

AmbientLight::AmbientLight(const AmbientLight& other)
{
	_colour = other.GetColour();
}

COLORREF AmbientLight::GetColour() const
{
	return _colour;
}

void AmbientLight::SetColour(COLORREF colour)
{
	_colour = colour;
}

AmbientLight& AmbientLight::operator=(const AmbientLight& rhs)
{
	if (this != &rhs)
	{
		_colour = rhs.GetColour();
	}
	return *this;
}