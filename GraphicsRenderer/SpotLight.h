#pragma once
#include "Vertex.h"
#include "Vector.h"

class SpotLight
{
public:
	SpotLight();
	SpotLight(const Vertex& position, const Vector& direction, const COLORREF& colour, float a, float b, float c, float innerAngle, float outerAngle);
	SpotLight(const SpotLight& other);

	Vertex GetPosition() const;
	void SetPosition(const Vertex& position);
	Vector GetDirection() const;
	void SetDirection(const Vector& direction);
	COLORREF GetColour() const;
	void SetColour(const COLORREF& colour);
	float GetInnerAngle() const;
	void SetInnerAngle(float angle);
	float GetOuterAngle() const;
	void SetOuterAngle(float angle);

	float CalculateAttenuation(float distance) const;

	SpotLight& operator= (const SpotLight& rhs);

private:
	Vertex _position;
	Vector _direction;
	COLORREF _colour;
	float _attentuation[3] = { 0.0f };
	float _innerAngle{ 0.0f };
	float _outerAngle{ 0.0f };
};

