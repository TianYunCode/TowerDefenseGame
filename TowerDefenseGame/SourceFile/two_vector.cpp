#include "two_vector.h"

TwoVector::TwoVector(double x, double y) : x(x), y(y)
{

}

TwoVector TwoVector::operator+(const TwoVector& vec) const
{
	return TwoVector(x + vec.x, y + vec.y);
}

void TwoVector::operator+=(const TwoVector& vec)
{
	x += vec.x, y += vec.y;
}

TwoVector TwoVector::operator-(const TwoVector& vec) const
{
	return TwoVector(x - vec.x, y - vec.y);
}

void TwoVector::operator-=(const TwoVector& vec)
{
	x -= vec.x, y -= vec.y;
}

double TwoVector::operator*(const TwoVector& vec) const
{
	return x * vec.x + y * vec.y;
}

TwoVector TwoVector::operator*(double val) const
{
	return TwoVector(x * val, y * val);
}

void TwoVector::operator*=(double val)
{
	x *= val, y *= val;
}

bool TwoVector::operator==(const TwoVector& vec) const
{
	return x == vec.x && y == vec.y;
}

bool TwoVector::operator>(const TwoVector& vec) const
{
	return length() > vec.length();
}

bool TwoVector::operator<(const TwoVector& vec) const
{
	return length() < vec.length();
}

double TwoVector::length() const
{
	return sqrt(x * x + y * y);
}

TwoVector TwoVector::normalize() const
{
	double len = length();

	if (len == 0) return TwoVector(0, 0);

	return TwoVector(x / len, y / len);
}

bool TwoVector::approx_zero() const
{
	return length() < 0.0001;
}