#pragma once
#include <Windows.h>
#include "Vector.h"

class DirectionalLight
{
public:
	DirectionalLight();
	DirectionalLight(const Vector& direction, const COLORREF& colour);
	DirectionalLight(const DirectionalLight& other);

	Vector GetDirection() const;
	void SetDirection(const Vector& direction);
	COLORREF GetColour() const;
	void SetColour(const COLORREF& colour);

	DirectionalLight& operator= (const DirectionalLight& rhs);
private:
	Vector _direction;
	COLORREF _colour;
};

