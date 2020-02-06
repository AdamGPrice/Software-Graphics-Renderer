#include "Camera.h"

Camera::Camera()
	: _xRotation(0.0f), _yRotation(0.0f), _zRotation(0.0f), _position(Vertex(0.0f, 0.0f, 0.0f))
{
}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
	: _xRotation(xRotation), _yRotation(yRotation), _zRotation(zRotation), _position(position)
{
}

Camera::Camera(const Camera& other)
	: _xRotation(other._xRotation), _yRotation(other._yRotation), _zRotation(other._zRotation), _position(other._position)
{
}

Camera::~Camera()
{
}

Camera& Camera::operator=(const Camera& rhs)
{
	if (this != &rhs)
	{
		_xRotation = rhs._xRotation;
		_yRotation = rhs._yRotation;
		_zRotation = rhs._zRotation;
		_position = rhs._position;
	}
	return *this;
}

Vertex Camera::GetPosition() const
{
	return _position;
}

Matrix Camera::GetViewMatrix()
{
	Matrix rotation = Matrix::XYZRotationMatrix(-_xRotation, -_yRotation, -_zRotation);
	Matrix translation = Matrix::TranslationMatrix(-_position.GetX(), -_position.GetY(), -_position.GetZ());

	return rotation * translation;
}
