#include "TwoVector.h"

TwoVector::TwoVector(double x, double y) : m_x(x), m_y(y) 
{

}

TwoVector TwoVector::operator+(const TwoVector& vec) const
{
	return TwoVector(m_x + vec.m_x, m_y + vec.m_y);
}

void TwoVector::operator+=(const TwoVector& vec)
{
	m_x += vec.m_x, m_y += vec.m_y;
}

TwoVector TwoVector::operator-(const TwoVector& vec) const
{
	return TwoVector(m_x - vec.m_x, m_y - vec.m_y);
}

void TwoVector::operator-=(const TwoVector& vec)
{
	m_x -= vec.m_x, m_y -= vec.m_y;
}

double TwoVector::operator*(const TwoVector& vec) const
{
	return m_x * vec.m_x + m_y * vec.m_y;
}

TwoVector TwoVector::operator*(double val) const
{
	return TwoVector(m_x * val, m_y * val);
}

void TwoVector::operator*=(double val)
{
	m_x *= val, m_y *= val;
}

bool TwoVector::operator==(const TwoVector& vec) const
{
	return m_x == vec.m_x && m_y == vec.m_y;
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
	return sqrt(m_x * m_x + m_y * m_y);
}

TwoVector TwoVector::normalize() const
{
	double len = length();

	if (len == 0)
	{
		return TwoVector(0, 0);
	}

	return TwoVector(m_x / len, m_y / len);
}

bool TwoVector::approxZero() const
{
	return length() < 0.0001;
}