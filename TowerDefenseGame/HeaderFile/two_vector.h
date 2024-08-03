#ifndef _TWO_VECTOR_H_
#define _TWO_VECTOR_H_

#include <cmath>

//��ά������
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

	double length() const;		 //�������ĳ���
	TwoVector normalize() const; //��׼��
	bool approx_zero() const;    //�Ƿ�ӽ�0�������ƶ���ʱ�������ж���û�е���Ŀ��
};

#endif