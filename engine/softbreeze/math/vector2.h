
#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

class Vector2
{
public:
	Vector2();
	Vector2( const Vector2& a );
	explicit Vector2( float x, float y);


	float				operator[]( int index ) const;
	float &				operator[]( int index );

	Vector2&		operator =(const Vector2& a);
	Vector2			operator -();

	Vector2			operator +(const Vector2& a) const; 
	Vector2			operator -(const Vector2& a) const;  
	float				operator *(const Vector2& a) const;
	Vector2			operator *(const float a) const;
	Vector2			operator /(const float a) const;

	friend Vector2	operator *(const float a, const Vector2& v);

	Vector2&		operator +=(const Vector2& a);
	Vector2&		operator -=(const Vector2& a);
	Vector2&		operator *=(const float& a);
	Vector2&		operator /=(const float& a);

	bool				operator == (const Vector2& a) const ;
	bool				operator != (const Vector2& a) const ;

	float				Length() const;
	float				LengthSqr() const;

	void				Normalize();
	void				Zero();

	void				Lerp(const Vector2 &v1, const Vector2 &v2, const float l);

public:
	float x,y;
};

__forceinline Vector2::Vector2()
{
}


__forceinline Vector2::Vector2(const Vector2& a)
{
	x = a.x;
	y = a.y;
}


__forceinline Vector2::Vector2( float x, float y)
{
	this->x = x;
	this->y = y;
}

__forceinline float Vector2::operator[]( int index ) const
{
	return (&x)[index];
}

__forceinline float &Vector2::operator[]( int index )
{
	return (&x)[index];
}

__forceinline Vector2& Vector2::operator=(const Vector2& a)
{
	this->x = a.x;
	this->y = a.y;

	return *this;
}


__forceinline Vector2 Vector2::operator-() 
{
	return Vector2(-x,-y);
}


__forceinline Vector2 Vector2::operator+(const Vector2& a) const
{
	return Vector2(a.x+x,a.y+y);

}

__forceinline Vector2 Vector2::operator-(const Vector2& a) const
{
	return Vector2(x-a.x,y-a.y);

}

__forceinline Vector2 Vector2::operator *(const float a) const
{
	return Vector2(x*a,y*a);
}

__forceinline float Vector2::operator *(const Vector2& a) const
{
	return x*a.x+y*a.y;
}



__forceinline Vector2 Vector2::operator /(const float a) const
{
	return Vector2(x/a,y/a);
}

__forceinline Vector2	operator *(const float a, const Vector2& v)
{
	return Vector2(a*v.x, a*v.y);
}

__forceinline Vector2& Vector2::operator+=(const Vector2& a) 
{
	x += a.x;
	y += a.y;

	return *this;
}

__forceinline Vector2& Vector2::operator-=(const Vector2& a) 
{
	x -= a.x;
	y -= a.y;

	return *this;
}

__forceinline Vector2& Vector2::operator*=(const float& a) 
{
	x *= a;
	y *= a;

	return *this;
}

__forceinline Vector2& Vector2::operator/=(const float& a) 
{
	float invA = 1.0f/a;
	x *= invA;
	y *= invA;

	return *this;
}


__forceinline bool Vector2::operator == (const Vector2& a) const
{
	return x==a.x && y==a.y ;

}

__forceinline bool Vector2::operator != (const Vector2& a) const
{
	return x!=a.x || y!=a.y ;

}

__forceinline float Vector2::Length() const
{
	return sqrt(x*x + y*y);
}

__forceinline float Vector2::LengthSqr() const
{
	return x*x + y*y ;
}

__forceinline void Vector2::Normalize()
{
	float lengthSqr = x*x + y*y ;
	if( lengthSqr != 0.0f)
	{
		float invLength = 1.0f/sqrt(lengthSqr);
		x *= invLength;
		y *= invLength;
	}
}

__forceinline void Vector2::Zero()
{
	x = 0;
	y = 0;
}




#endif

