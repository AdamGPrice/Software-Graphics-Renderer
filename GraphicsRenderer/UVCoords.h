#pragma once
class UVCoords
{
public:
	UVCoords();
	UVCoords(float u, float v);
	UVCoords(const UVCoords& other);

	float GetU() const;
	void SetU(float u);
	float GetV() const;
	void SetV(float v);

	// Operators
	UVCoords& operator= (const UVCoords& rhs);
	const UVCoords operator+ (const UVCoords& rhs) const;
	const UVCoords operator- (const UVCoords& rhs) const;
	const UVCoords operator* (float scaler) const;
	const UVCoords operator/ (float scaler) const;

private:
	float _u;
	float _v;
};

