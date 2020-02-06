#include "Matrix.h"
#include <cmath>

Matrix::Matrix()
{
}

Matrix::Matrix(const std::initializer_list<float> list)
{
	if (list.size() == ROWS * COLS)
	{
		auto iterator = list.begin();
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				_m[i][j] = *iterator;
				iterator++;
			}
		}
	}
	else
	{
		throw "ERROR::MATRIX_CLASS::Invalid count of floats for the initializer list.";
	}
}

Matrix::Matrix(const Matrix& other)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++) {
			_m[i][j] = other._m[i][j];
		}
	}
}

float Matrix::GetM(int row, int column) const
{
	return _m[row][column];
}

void Matrix::SetM(int row, int column, float value)
{
	_m[row][column] = value;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++) {
				_m[i][j] = other._m[i][j];
			}
		}
	}
	return *this;
}

bool Matrix::operator==(const Matrix& other) const
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (_m[i][j] != other._m[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

const Matrix Matrix::operator*(const Matrix& other) const
{
	Matrix result;

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			float sum = 0;
			for (int k = 0; k < COLS; k++)
			{
				sum += _m[i][k] * other._m[k][j];
			}
			result._m[i][j] = sum;
		}
	}

	return result;
}

const Vertex Matrix::operator*(const Vertex& vertex) const
{
	Vertex result;

	result.SetX(_m[0][0] * vertex.GetX() + _m[0][1] * vertex.GetY() + _m[0][2] * vertex.GetZ() + _m[0][3] * vertex.GetW());
	result.SetY(_m[1][0] * vertex.GetX() + _m[1][1] * vertex.GetY() + _m[1][2] * vertex.GetZ() + _m[1][3] * vertex.GetW());
	result.SetZ(_m[2][0] * vertex.GetX() + _m[2][1] * vertex.GetY() + _m[2][2] * vertex.GetZ() + _m[2][3] * vertex.GetW());
	result.SetW(_m[3][0] * vertex.GetX() + _m[3][1] * vertex.GetY() + _m[3][2] * vertex.GetZ() + _m[3][3] * vertex.GetW());

	// the Vertex need to keep all of its properties
	result.SetNormal(vertex.GetNormal());
	result.SetColour(vertex.GetColour());
	result.SetPolygonCount(vertex.GetPolygonCount());
	result.SetUV(vertex.GetUV());
	result.SetZRecip(vertex.GetZRecip());
	result.SetPreTransformZ(vertex.GetPreTransformZ());
	return result;
}

Matrix Matrix::IdentityMatrix()
{
	return Matrix({ 1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1 });
}

Matrix Matrix::TranslationMatrix(float x, float y, float z)
{
	return Matrix({ 1, 0, 0, x,
					0, 1, 0, y,
					0, 0, 1, z, 
					0, 0, 0, 1 });
}

Matrix Matrix::ScalingMatrix(float x, float y, float z)
{
	return Matrix({ x, 0, 0, 0,
					0, y, 0, 0,
					0, 0, z, 0,
					0, 0, 0, 1 });
}

Matrix Matrix::XRotationMatrix(float angle)
{
	float radians = Radians(angle);

	return Matrix({ 1,      0,             0,       0,
					0, cos(radians), -sin(radians), 0,
					0, sin(radians),  cos(radians), 0,
					0,      0,             0,       1 });
}

Matrix Matrix::YRotationMatrix(float angle)
{
	float radians = Radians(angle);

	return Matrix({ cos(radians), 0, sin(radians), 0,
						 0,       1,      0,	   0,
				   -sin(radians), 0, cos(radians), 0,
					     0,       0,      0,       1 });
}

Matrix Matrix::ZRotationMatrix(float angle)
{
	float radians = Radians(angle);

	return Matrix({ cos(radians), -sin(radians), 0, 0, 
				    sin(radians),  cos(radians), 0, 0, 
					      0,             0,      1, 0, 
					      0,			 0,      0, 1, });
}

Matrix Matrix::XYZRotationMatrix(float angleX, float angleY, float angleZ)
{
	return XRotationMatrix(angleX) * YRotationMatrix(angleY) * ZRotationMatrix(angleZ);
}
