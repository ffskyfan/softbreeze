

#ifndef VECTOR4_H
#define VECTOR4_H

#include <math.h>

class starVector4
{
public:
	starVector4();
	starVector4( const starVector4& a );
	explicit starVector4( float x, float y,float z,float w);

	float				operator[]( int index ) const;
	float &				operator[]( int index );

	starVector4&		operator =(const starVector4& a);
	starVector4			operator -();

	starVector4			operator +(const starVector4& a) const; 
	starVector4			operator -(const starVector4& a) const;  
	starVector4			operator *(const float a) const;
	starVector4			operator /(const float a) const;

	friend starVector4	operator *(const float a, const starVector4& v);

	starVector4&		operator +=(const starVector4& a);
	starVector4&		operator -=(const starVector4& a);
	starVector4&		operator *=(const float& a);
	starVector4&		operator /=(const float& a);

	bool				operator == (const starVector4& a) const ;
	bool				operator != (const starVector4& a) const ;
	bool				operator <	 (const starVector4& a) const ;

	float				Length() const;
	float				LengthSqr() const;

	void				Normalize();
	void				Zero();

	float				Dot(const starVector4& a) const ;

	void				Lerp( const starVector4 &v1, const starVector4 &v2, const float l );


public:
	float x,y,z,w;
};

__forceinline starVector4::starVector4()
{
}


__forceinline starVector4::starVector4(const starVector4& a)
{
	x = a.x;
	y = a.y;
	z = a.z;
	w = a.w;
}


__forceinline starVector4::starVector4( float x, float y,float z,float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

__forceinline float starVector4::operator[]( int index ) const
{
	return (&x)[index];
}

__forceinline float &starVector4::operator[]( int index )
{
	return (&x)[index];
}


__forceinline starVector4& starVector4::operator=(const starVector4& a)
{
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
	this->w = a.w;

	return *this;
}


__forceinline starVector4 starVector4::operator-() 
{
	return starVector4(-x,-y,-z,-w);
}


__forceinline starVector4 starVector4::operator+(const starVector4& a) const
{
	return starVector4(x+a.x,y+a.y,z+a.z,w+a.w+w);

}

__forceinline starVector4 starVector4::operator-(const starVector4& a) const
{
	return starVector4(x-a.x,y-a.y,z-a.z,w-a.w);

}

__forceinline starVector4 starVector4::operator *(const float a) const
{
	return starVector4(x*a,y*a,z*a,w*a);
}


__forceinline starVector4 starVector4::operator /(const float a) const
{
	return starVector4(x/a,y/a,z/a,w/a);
}


__forceinline starVector4	operator *(const float a, const starVector4& v)
{
	return starVector4(v.x*a,v.y*a,v.z*a,v.w*a);
}

__forceinline starVector4& starVector4::operator+=(const starVector4& a) 
{
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;

	return *this;
}

__forceinline starVector4& starVector4::operator-=(const starVector4& a) 
{
	x -= a.x;
	y -= a.y;
	z -= a.z;
	w -= a.w;

	return *this;
}

__forceinline starVector4& starVector4::operator*=(const float& a) 
{
	x *= a;
	y *= a;
	z *= a;
	w *= a;

	return *this;
}

__forceinline starVector4& starVector4::operator/=(const float& a) 
{
	float invA = 1.0f/a;
	x *= invA;
	y *= invA;
	z *= invA;
	w *= invA;

	return *this;
}


__forceinline bool starVector4::operator == (const starVector4& a) const
{
	return x==a.x && y==a.y && z==a.z && w==a.w;

}

__forceinline bool starVector4::operator != (const starVector4& a) const
{
	return x!=a.x || y!=a.y || z!=a.z || w!=a.w;

}


__forceinline float starVector4::Length() const
{
	return sqrt(x*x + y*y + z*z + w*w);
}

__forceinline float starVector4::LengthSqr() const
{
	return x*x + y*y + z*z + w*w;
}

__forceinline void starVector4::Normalize()
{
	float lengthSqr = x*x + y*y + z*z + w*w;
	if( lengthSqr != 0.0f)
	{
		float invLength = 1.0f/sqrt(lengthSqr);
		x *= invLength;
		y *= invLength;
		z *= invLength;
		w *= invLength;
	}
}

__forceinline void starVector4::Zero()
{
	x = y = z = w = 0;
}


__forceinline float starVector4::Dot(const starVector4& a) const
{
	return x*a.x+y*a.y+z*a.z+w*a.w;
}

#endif

