
#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

class starVector2
{
public:
	starVector2();
	starVector2( const starVector2& a );
	explicit starVector2( float x, float y);


	float				operator[]( int index ) const;
	float &				operator[]( int index );

	starVector2&		operator =(const starVector2& a);
	starVector2			operator -();

	starVector2			operator +(const starVector2& a) const; 
	starVector2			operator -(const starVector2& a) const;  
	float				operator *(const starVector2& a) const;
	starVector2			operator *(const float a) const;
	starVector2			operator /(const float a) const;

	friend starVector2	operator *(const float a, const starVector2& v);

	starVector2&		operator +=(const starVector2& a);
	starVector2&		operator -=(const starVector2& a);
	starVector2&		operator *=(const float& a);
	starVector2&		operator /=(const float& a);

	bool				operator == (const starVector2& a) const ;
	bool				operator != (const starVector2& a) const ;

	float				Length() const;
	float				LengthSqr() const;

	void				Normalize();
	void				Zero();

	void				Lerp(const starVector2 &v1, const starVector2 &v2, const float l);

public:
	float x,y;
};

__forceinline starVector2::starVector2()
{
}


__forceinline starVector2::starVector2(const starVector2& a)
{
	x = a.x;
	y = a.y;
}


__forceinline starVector2::starVector2( float x, float y)
{
	this->x = x;
	this->y = y;
}

__forceinline float starVector2::operator[]( int index ) const
{
	return (&x)[index];
}

__forceinline float &starVector2::operator[]( int index )
{
	return (&x)[index];
}

__forceinline starVector2& starVector2::operator=(const starVector2& a)
{
	this->x = a.x;
	this->y = a.y;

	return *this;
}


__forceinline starVector2 starVector2::operator-() 
{
	return starVector2(-x,-y);
}


__forceinline starVector2 starVector2::operator+(const starVector2& a) const
{
	return starVector2(a.x+x,a.y+y);

}

__forceinline starVector2 starVector2::operator-(const starVector2& a) const
{
	return starVector2(x-a.x,y-a.y);

}

__forceinline starVector2 starVector2::operator *(const float a) const
{
	return starVector2(x*a,y*a);
}

__forceinline float starVector2::operator *(const starVector2& a) const
{
	return x*a.x+y*a.y;
}



__forceinline starVector2 starVector2::operator /(const float a) const
{
	return starVector2(x/a,y/a);
}

__forceinline starVector2	operator *(const float a, const starVector2& v)
{
	return starVector2(a*v.x, a*v.y);
}

__forceinline starVector2& starVector2::operator+=(const starVector2& a) 
{
	x += a.x;
	y += a.y;

	return *this;
}

__forceinline starVector2& starVector2::operator-=(const starVector2& a) 
{
	x -= a.x;
	y -= a.y;

	return *this;
}

__forceinline starVector2& starVector2::operator*=(const float& a) 
{
	x *= a;
	y *= a;

	return *this;
}

__forceinline starVector2& starVector2::operator/=(const float& a) 
{
	float invA = 1.0f/a;
	x *= invA;
	y *= invA;

	return *this;
}


__forceinline bool starVector2::operator == (const starVector2& a) const
{
	return x==a.x && y==a.y ;

}

__forceinline bool starVector2::operator != (const starVector2& a) const
{
	return x!=a.x || y!=a.y ;

}

__forceinline float starVector2::Length() const
{
	return sqrt(x*x + y*y);
}

__forceinline float starVector2::LengthSqr() const
{
	return x*x + y*y ;
}

__forceinline void starVector2::Normalize()
{
	float lengthSqr = x*x + y*y ;
	if( lengthSqr != 0.0f)
	{
		float invLength = 1.0f/sqrt(lengthSqr);
		x *= invLength;
		y *= invLength;
	}
}

__forceinline void starVector2::Zero()
{
	x = 0;
	y = 0;
}




#endif

