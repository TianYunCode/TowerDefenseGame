#pragma once

#include <cmath>

class TwoVector
{
public:
	double m_x = 0;
	double m_y = 0;

public:
	TwoVector() = default;
	~TwoVector() = default;

	TwoVector(double x, double y);

	TwoVector operator+(const TwoVector& vec) const;
	void operator+=(const TwoVector& vec);

	TwoVector operator-(const TwoVector& vec) const;
	void operator-=(const TwoVector& vec);

	double operator*(const TwoVector& vec) const;
	TwoVector operator*(double val) const;

	void operator*=(double val);
	bool operator==(const TwoVector& vec) const;

	bool operator>(const TwoVector& vec) const;
	bool operator<(const TwoVector& vec) const;

	double length() const;
	TwoVector normalize() const;
	bool approxZero() const;
};
