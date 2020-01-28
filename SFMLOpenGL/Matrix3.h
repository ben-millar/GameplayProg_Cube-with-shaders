#ifndef MY_MATRIX
#define MY_MATRIX
#include "Vector3.h"

namespace gpp
{
	class Matrix3
	{
	public:
		Matrix3();
		Matrix3(
			float t_a11, float t_a12, float t_a13,
			float t_a21, float t_a22, float t_a23,
			float t_a31, float t_a32, float t_a33);
		Matrix3(const Vector3 t_row1, const Vector3 t_row2, const Vector3 t_row3);
		~Matrix3();

		std::string toString()const;

		bool operator ==(const Matrix3 other)const;
		bool operator !=(const Matrix3 other)const;


		Matrix3 operator +(const Matrix3 t_other) const;
		Matrix3 operator -(const Matrix3 t_other) const;
		Matrix3 operator *(const Matrix3 t_other) const;
		Vector3 operator *(const Vector3 t_vector)const;
		// Did not implement Vector*Matrix as in C# code
		Matrix3 operator *(const float t_scale)const;

		Matrix3 transpose()const;
		float determinant() const;
		Matrix3 inverse() const;

		Vector3 row(const int t_row)const; // 0 is first row then 1,2
		Vector3 column(const int t_column) const;

		static Matrix3 rotationZ(const float t_angleRadians); // counterclockwise
		static Matrix3 rotationY(const float t_angleRadians);
		static Matrix3 rotationX(const float t_angleRadians);// {1,-3,2} = Matrix3::rotationX(PI/2)*{1,2,3}

		static Matrix3 translation(const Vector3 t_displacement); // 2d translation make sure z=1
		static Matrix3 scale(const float t_scalingfactor);


	private:
		static const int NUM_ROWS = 3;
		static const int NUM_COLS = 3;
		float m[NUM_ROWS][NUM_COLS];
	};
}
#endif // !MY_MATRIX