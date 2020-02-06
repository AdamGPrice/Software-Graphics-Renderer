#include "Vector.h"
#include <cmath>

Vector::Vector()
	: _x(0.0f), _y(0.0f), _z(0.0f)
{
}

Vector::Vector(float x, float y, float z)
	: _x(x), _y(y), _z(z)
{
}

Vector::Vector(const Vector& other)
	: _x(other.GetX()), _y(other.GetY()), _z(other.GetZ())
{
}

float Vector::GetX() const
{
	return _x;
}

void Vector::SetX(const float x)
{
	_x = x;
}

float Vector::GetY() const
{
	return _y;
}

void Vector::SetY(const float y)
{
	_y = y;
}

float Vector::GetZ() const
{
	return _z;
}

void Vector::SetZ(const float z)
{
	_z = z;
}

Vector& Vector::operator=(const Vector& rhs)
{
	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
	}
	return *this;
}

bool Vector::operator==(const Vector& rhs)
{
	return _x == rhs.GetX() && _y == rhs.GetY() && _z == rhs.GetZ();
}

const Vector Vector::operator+(const Vector& rhs) const
{
	return Vector(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ());
}

const Vector Vector::operator-(const Vector& rhs) const
{
	return Vector(_x - rhs.GetX(), _y - rhs.GetY(), _z - rhs.GetZ());
}

const Vector Vector::operator*(float scaler) const
{
	return Vector(_x * scaler, _y * scaler, _z * scaler);
}

const Vector Vector::operator/(float scaler) const
{
	return Vector(_x / scaler, _y / scaler, _z / scaler);
}

float Vector::Magnitude() const
{
	return sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2));
}

void Vector::Normalise()
{
	float mag = Magnitude();
	_x = _x / mag;
	_y = _y / mag;
	_z = _z / mag;
}

float Vector::DotProdcut(const Vector& a, const Vector& b)
{
	return a.GetX() * b.GetX() + a.GetY() * b.GetY() + a.GetZ() * b.GetZ();
}

Vector Vector::CrossProduct(const Vector& a, const Vector& b)
{
	float x = a.GetY() * b.GetZ() - a.GetZ() * b.GetY();
	float y = a.GetZ() * b.GetX() - a.GetX() * b.GetZ();
	float z = a.GetX() * b.GetY() - a.GetY() * b.GetX();
	return Vector(x, y, z);
}

Vector Vector::Normalise(const Vector& vec)
{
	Vector result;
	float mag = vec.Magnitude();
	result.SetX(vec.GetX() / mag);
	result.SetY(vec.GetY() / mag);
	result.SetZ(vec.GetZ() / mag);
	return result;
}
