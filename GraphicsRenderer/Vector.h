#pragma once
class Vector
{
public:
	Vector();
	Vector(float x, float y, float z);
	Vector(const Vector& other);

	// Accessors
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float z);

	// Operators
	Vector& operator= (const Vector& rhs);
	bool operator== (const Vector& rhs);
	const Vector operator+ (const Vector& rhs) const;
	const Vector operator- (const Vector& rhs) const;
	const Vector operator* (float scaler) const;
	const Vector operator/ (float scaler) const;

	// Instance methods
	float Magnitude() const;
	void Normalise();

	// Static methods 
	static float DotProdcut(const Vector& a, const Vector& b);
	static Vector CrossProduct(const Vector& a, const Vector& b);
	static Vector Normalise(const Vector& vec);

private:
	float _x;
	float _y;
	float _z;
};

