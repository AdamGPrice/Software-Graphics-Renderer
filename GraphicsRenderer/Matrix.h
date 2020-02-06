#pragma once
#include "Vertex.h"
#include <initializer_list>

#define PI	3.14159265358979323846
#define Radians(angle) (float)PI / 180 * angle

const int ROWS = 4;
const int COLS = 4;

class Matrix
{
public:
	Matrix();
	Matrix(const std::initializer_list<float> initList);
	Matrix(const Matrix& other);

	float GetM(int row, int column) const;
	void SetM(int row, int column, float value);

	Matrix& operator= (const Matrix& other);
	bool operator==(const Matrix& other) const;
	const Matrix operator*(const Matrix& other) const;
	const Vertex operator*(const Vertex& vertex) const;

	static Matrix IdentityMatrix();
	static Matrix TranslationMatrix(float x, float y, float z);
	static Matrix ScalingMatrix(float x, float y, float z);
	static Matrix XRotationMatrix(float angle);
	static Matrix YRotationMatrix(float angle);
	static Matrix ZRotationMatrix(float angle);
	static Matrix XYZRotationMatrix(float angleX, float angleY, float angleZ);
private:
	float _m[ROWS][COLS]{ 0.0f };
};