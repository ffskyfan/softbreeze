
#ifndef VECTOR3_H
#define VECTOR3_H


#include <math.h>

softbreeze_namespace_beg

class Vector3
{
public:
	Vector3();
	Vector3( const Vector3& a );
	explicit Vector3( float x, float y,float z);


	float				operator[]( int index ) const;
	float &				operator[]( int index );

	Vector3&		operator =(const Vector3& a);
	Vector3			operator -();

	Vector3			operator +(const Vector3& a) const; 
	Vector3			operator -(const Vector3& a) const;  
	float				operator *(const Vector3& a) const;
	Vector3			operator *(const float a) const;
	Vector3			operator /(const float a) const;

	friend Vector3	operator *(const float a, const Vector3& v);

	Vector3&		operator +=(const Vector3& a);
	Vector3&		operator -=(const Vector3& a);
	Vector3&		operator *=(const float& a);
	Vector3&		operator /=(const float& a);

	bool				operator == (const Vector3& a) const ;
	bool				operator != (const Vector3& a) const ;
	bool				operator <	 (const Vector3& a) const ;

	float				Length() const;
	float				LengthSqr() const;

	void				Normalize();
	void				Zero();

	Vector3			Cross(const Vector3& a) const ;
	Vector3&		Cross(const Vector3& a,const Vector3& b);
	 

	void				Lerp( const Vector3 &v1, const Vector3 &v2, const float l );
	void				SLerp( const Vector3 &v1, const Vector3 &v2, const float l );



public:
	float x,y,z;
};

__forceinline Vector3::Vector3()
{
}


__forceinline Vector3::Vector3(const Vector3& a)
{
	x = a.x;
	y = a.y;
	z = a.z;
}


__forceinline Vector3::Vector3( float x, float y,float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


__forceinline float Vector3::operator[]( int index ) const
{
	return (&x)[index];
}

__forceinline float &Vector3::operator[]( int index )
{
	return (&x)[index];
}


__forceinline Vector3& Vector3::operator=(const Vector3& a)
{
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;

	return *this;
}


__forceinline Vector3 Vector3::operator-() 
{
	return Vector3(-x,-y,-z);
}


__forceinline Vector3 Vector3::operator+(const Vector3& a) const
{
	return Vector3(x+a.x,y+a.y,z+a.z);

}

__forceinline Vector3 Vector3::operator-(const Vector3& a) const
{
	return Vector3(x-a.x,y-a.y,z-a.z);

}

__forceinline Vector3 Vector3::operator *(const float a) const
{
	return Vector3(x*a,y*a,z*a);
}

__forceinline float Vector3::operator *(const Vector3& a) const
{
	return x*a.x+y*a.y+z*a.z;
}

__forceinline Vector3 Vector3::operator /(const float a) const
{
	return Vector3(x/a,y/a,z/a);
}

__forceinline Vector3	operator *(const float a, const Vector3& v)
{
	return Vector3(v.x*a, v.y*a, v.z*a);
}

__forceinline Vector3& Vector3::operator+=(const Vector3& a) 
{
	x += a.x;
	y += a.y;
	z += a.z;

	return *this;
}

__forceinline Vector3& Vector3::operator-=(const Vector3& a) 
{
	x -= a.x;
	y -= a.y;
	z -= a.z;

	return *this;
}

__forceinline Vector3& Vector3::operator*=(const float& a) 
{
	x *= a;
	y *= a;
	z *= a;

	return *this;
}

__forceinline Vector3& Vector3::operator/=(const float& a) 
{
	float invA = 1.0f/a;
	x *= invA;
	y *= invA;
	z *= invA;

	return *this;
}


__forceinline bool Vector3::operator == (const Vector3& a) const
{
	return x==a.x && y==a.y && z==a.z;

}

__forceinline bool Vector3::operator != (const Vector3& a) const
{
	return x!=a.x || y!=a.y || z!=a.z;

}


__forceinline float Vector3::Length() const
{
	return sqrt(x*x + y*y + z*z);
}

__forceinline float Vector3::LengthSqr() const
{
	return x*x + y*y + z*z;
}

__forceinline void Vector3::Normalize()
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

__forceinline void Vector3::Zero()
{
	x = 0;
	y = 0;
	z = 0;
}



__forceinline Vector3 Vector3::Cross(const Vector3& a) const
{
	return Vector3(y*a.z-z*a.y, z*a.x-x*a.z, x*a.y-y*a.z);
}

__forceinline Vector3& Vector3::Cross(const Vector3& a,const Vector3& b)
{
	x = y*a.z-z*a.y;
	y = z*a.x-x*a.z;
	z = x*a.y-y*a.z;

	return *this;
}


softbreeze_namespace_end


#endif
