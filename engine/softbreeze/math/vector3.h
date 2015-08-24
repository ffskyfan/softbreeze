
#ifndef VECTOR3_H
#define VECTOR3_H


#include <math.h>

class starVector3
{
public:
	starVector3();
	starVector3( const starVector3& a );
	explicit starVector3( float x, float y,float z);


	float				operator[]( int index ) const;
	float &				operator[]( int index );

	starVector3&		operator =(const starVector3& a);
	starVector3			operator -();

	starVector3			operator +(const starVector3& a) const; 
	starVector3			operator -(const starVector3& a) const;  
	float				operator *(const starVector3& a) const;
	starVector3			operator *(const float a) const;
	starVector3			operator /(const float a) const;

	friend starVector3	operator *(const float a, const starVector3& v);

	starVector3&		operator +=(const starVector3& a);
	starVector3&		operator -=(const starVector3& a);
	starVector3&		operator *=(const float& a);
	starVector3&		operator /=(const float& a);

	bool				operator == (const starVector3& a) const ;
	bool				operator != (const starVector3& a) const ;
	bool				operator <	 (const starVector3& a) const ;

	float				Length() const;
	float				LengthSqr() const;

	void				Normalize();
	void				Zero();

	starVector3			Cross(const starVector3& a) const ;
	starVector3&		Cross(const starVector3& a,const starVector3& b);
	 

	void				Lerp( const starVector3 &v1, const starVector3 &v2, const float l );
	void				SLerp( const starVector3 &v1, const starVector3 &v2, const float l );



public:
	float x,y,z;
};

__forceinline starVector3::starVector3()
{
}


__forceinline starVector3::starVector3(const starVector3& a)
{
	x = a.x;
	y = a.y;
	z = a.z;
}


__forceinline starVector3::starVector3( float x, float y,float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


__forceinline float starVector3::operator[]( int index ) const
{
	return (&x)[index];
}

__forceinline float &starVector3::operator[]( int index )
{
	return (&x)[index];
}


__forceinline starVector3& starVector3::operator=(const starVector3& a)
{
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;

	return *this;
}


__forceinline starVector3 starVector3::operator-() 
{
	return starVector3(-x,-y,-z);
}


__forceinline starVector3 starVector3::operator+(const starVector3& a) const
{
	return starVector3(x+a.x,y+a.y,z+a.z);

}

__forceinline starVector3 starVector3::operator-(const starVector3& a) const
{
	return starVector3(x-a.x,y-a.y,z-a.z);

}

__forceinline starVector3 starVector3::operator *(const float a) const
{
	return starVector3(x*a,y*a,z*a);
}

__forceinline float starVector3::operator *(const starVector3& a) const
{
	return x*a.x+y*a.y+z*a.z;
}

__forceinline starVector3 starVector3::operator /(const float a) const
{
	return starVector3(x/a,y/a,z/a);
}

__forceinline starVector3	operator *(const float a, const starVector3& v)
{
	return starVector3(v.x*a, v.y*a, v.z*a);
}

__forceinline starVector3& starVector3::operator+=(const starVector3& a) 
{
	x += a.x;
	y += a.y;
	z += a.z;

	return *this;
}

__forceinline starVector3& starVector3::operator-=(const starVector3& a) 
{
	x -= a.x;
	y -= a.y;
	z -= a.z;

	return *this;
}

__forceinline starVector3& starVector3::operator*=(const float& a) 
{
	x *= a;
	y *= a;
	z *= a;

	return *this;
}

__forceinline starVector3& starVector3::operator/=(const float& a) 
{
	float invA = 1.0f/a;
	x *= invA;
	y *= invA;
	z *= invA;

	return *this;
}


__forceinline bool starVector3::operator == (const starVector3& a) const
{
	return x==a.x && y==a.y && z==a.z;

}

__forceinline bool starVector3::operator != (const starVector3& a) const
{
	return x!=a.x || y!=a.y || z!=a.z;

}


__forceinline float starVector3::Length() const
{
	return sqrt(x*x + y*y + z*z);
}

__forceinline float starVector3::LengthSqr() const
{
	return x*x + y*y + z*z;
}

__forceinline void starVector3::Normalize()
{
	float lengthSqr = x*x + y*y + z*z;
	if( lengthSqr != 0.0f)
	{
		float invLength = 1.0f/sqrt(lengthSqr);
		x *= invLength;
		y *= invLength;
		z *= invLength;
	}
}

__forceinline void starVector3::Zero()
{
	x = 0;
	y = 0;
	z = 0;
}



__forceinline starVector3 starVector3::Cross(const starVector3& a) const
{
	return starVector3(y*a.z-z*a.y, z*a.x-x*a.z, x*a.y-y*a.z);
}

__forceinline starVector3& starVector3::Cross(const starVector3& a,const starVector3& b)
{
	x = y*a.z-z*a.y;
	y = z*a.x-x*a.z;
	z = x*a.y-y*a.z;

	return *this;
}


#endif
