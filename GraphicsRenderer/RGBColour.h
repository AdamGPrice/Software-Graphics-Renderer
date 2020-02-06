#pragma once
#include <Windows.h>
#include <array>

class RGBColour
{
public:
	RGBColour();
	RGBColour(float r, float g, float b);
	RGBColour(const COLORREF& colour);
	RGBColour(const RGBColour& other);

	float GetR() const;
	void SetR(float red);
	float GetG() const;
	void SetG(float green);
	float GetB() const;
	void SetB(float blue);

	COLORREF GetColorref();
	void ClampColour();

	RGBColour& operator= (const RGBColour& rhs);
	const RGBColour operator+ (const RGBColour& rhs) const;
	const RGBColour operator- (const RGBColour& rhs) const;
	const RGBColour operator* (const RGBColour& rhs) const;
	const RGBColour operator* (float scaler) const;
	const RGBColour operator/ (float scaler) const;
	const RGBColour operator* (std::array<float, 3> coefficients) const;

private:
	float _r;
	float _g;
	float _b;
};

