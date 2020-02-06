#pragma once
#include <Windows.h>

class AmbientLight
{
public:
	AmbientLight();
	AmbientLight(const COLORREF& colour);
	AmbientLight(const AmbientLight& other);

	COLORREF GetColour() const;
	void SetColour(COLORREF colour);

	AmbientLight& operator= (const AmbientLight& rhs);
private:
	COLORREF _colour;
};

