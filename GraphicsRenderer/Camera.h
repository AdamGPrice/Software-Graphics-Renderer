#pragma once
#include "Vertex.h"
#include "Matrix.h"

class Camera
{
public:
	Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	Camera(const Camera& other);
	~Camera();
	Camera& operator=(const Camera& rhs);

	Vertex GetPosition() const;
	Matrix GetViewMatrix();
private:
	float _xRotation;
	float _yRotation;
	float _zRotation;
	Vertex _position;
};

