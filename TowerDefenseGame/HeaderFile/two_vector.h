#ifndef _TWO_VECTOR_H_
#define _TWO_VECTOR_H_

#include <cmath>

//二维向量类
class TwoVector
{
public:
	double x = 0;
	double y = 0;

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

	double length() const;		 //求向量的长度
	TwoVector normalize() const; //标准化
	bool approx_zero() const;    //是否接近0，怪物移动的时候，用来判定有没有到达目标
};

#endif