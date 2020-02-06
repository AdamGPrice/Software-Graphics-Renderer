#include "UVCoords.h"

UVCoords::UVCoords()
	:_u(0.0f), _v(0.0f)
{
}

UVCoords::UVCoords(float u, float v)
	: _u(u), _v(v)
{
}

UVCoords::UVCoords(const UVCoords& other)
	: _u(other.GetU()), _v(other.GetV())
{
}

float UVCoords::GetU() const
{
	return _u;
}

void UVCoords::SetU(float u)
{
	_u = u;
}

float UVCoords::GetV() const
{
	return _v;
}

void UVCoords::SetV(float v)
{
	_v = v;
}

UVCoords& UVCoords::operator=(const UVCoords& rhs)
{
	if (this != &rhs)
	{
		_u = rhs.GetU();
		_v = rhs.GetV();
	}
	return *this;
}

const UVCoords UVCoords::operator+(const UVCoords& rhs) const
{
	return UVCoords(_u + rhs.GetU(), _v + rhs.GetV());
}

const UVCoords UVCoords::operator-(const UVCoords& rhs) const
{
	return UVCoords(_u - rhs.GetU(), _v - rhs.GetV());
}

const UVCoords UVCoords::operator*(float scaler) const
{
	return UVCoords(_u * scaler, _v * scaler);
}

const UVCoords UVCoords::operator/(float scaler) const
{
	return UVCoords(_u / scaler, _v / scaler);
}
