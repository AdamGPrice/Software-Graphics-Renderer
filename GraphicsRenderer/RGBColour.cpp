#include "RGBColour.h"

RGBColour::RGBColour()
	: _r(0), _g(0), _b(0)
{
}

RGBColour::RGBColour(float r, float g, float b)
	: _r(r), _g(g), _b(b)
{
}

RGBColour::RGBColour(const COLORREF& colour)
	: _r(GetRValue(colour)), _g(GetGValue(colour)), _b(GetBValue(colour))
{
}

RGBColour::RGBColour(const RGBColour& other)
	: _r(other.GetR()), _g(other.GetG()), _b(other.GetB())
{
}

float RGBColour::GetR() const
{
	return _r;
}

void RGBColour::SetR(float red)
{
	_r = red;
}

float RGBColour::GetG() const
{
	return _g;
}

void RGBColour::SetG(float green)
{
	_g = green;
}

float RGBColour::GetB() const
{
	return _b;
}

void RGBColour::SetB(float blue)
{
	_b = blue;
}

COLORREF RGBColour::GetColorref()
{
	return RGB(_r, _g, _b);
}

void RGBColour::ClampColour()
{
	if (_r > 255) _r = 255;
	else if (_r < 0) _r = 0;
	if (_g > 255) _g = 255;
	else if (_g < 0) _g = 0;
	if (_b > 255) _b = 255;
	else if (_b < 0) _b = 0;
}


RGBColour& RGBColour::operator=(const RGBColour& rhs)
{
	if (this != &rhs)
	{
		_r = rhs.GetR();
		_g = rhs.GetG();
		_b = rhs.GetB();
	}
	return *this;
}

const RGBColour RGBColour::operator+(const RGBColour& rhs) const
{
	return RGBColour(_r + rhs.GetR(), _g + rhs.GetG(), _b + rhs.GetB());
}

const RGBColour RGBColour::operator-(const RGBColour& rhs) const
{
	return RGBColour(_r - rhs.GetR(), _g - rhs.GetG(), _b - rhs.GetB());
}

const RGBColour RGBColour::operator*(const RGBColour& rhs) const
{
	return RGBColour(_r * rhs.GetR(), _g * rhs.GetG(), _b * rhs.GetB());
}

const RGBColour RGBColour::operator*(float scaler) const
{
	return RGBColour(_r * scaler, _g * scaler, _b * scaler);
}

const RGBColour RGBColour::operator/(float scaler) const
{
	return RGBColour(_r / scaler, _g / scaler, _b / scaler);
}

const RGBColour RGBColour::operator*(std::array<float, 3> coefficients) const
{
	return RGBColour(_r * coefficients[0], _g * coefficients[1], _b * coefficients[2]);
}
