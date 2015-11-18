

#ifndef VECTOR4_H
#define VECTOR4_H

#include <math.h>



softbreeze_namespace_beg

class Vector4
{
public:
	Vector4();
	Vector4( const Vector4& a );
	explicit Vector4( float x, float y,float z,float w);

	float				operator[]( int index ) const;
	float &				operator[]( int index );

	Vector4&			operator =(const Vector4& a);
	Vector4				operator -();

	Vector4				operator +(const Vector4& a) const; 
	Vector4				operator -(const Vector4& a) const;  
	Vector4				operator *(const float a) const;
	Vector4				operator /(const float a) const;

	friend Vector4		operator *(const float a, const Vector4& v);

	Vector4&			operator +=(const Vector4& a);
	Vector4&			operator -=(const Vector4& a);
	Vector4&			operator *=(const float& a);
	Vector4&			operator /=(const float& a);

	bool				operator == (const Vector4& a) const ;
	bool				operator != (const Vector4& a) const ;
	bool				operator <	 (const Vector4& a) const ;

	float				Length() const;
	float				LengthSqr() const;

	void				Normalize();
	void				Zero();

	float				Dot(const Vector4& a) const ;

	void				Lerp( const Vector4 &v1, const Vector4 &v2, const float l );


public:
	float x,y,z,w;
};

__forceinline Vector4::Vector4()
{
}


__forceinline Vector4::Vector4(const Vector4& a)
{
	x = a.x;
	y = a.y;
	z = a.z;
	w = a.w;
}


__forceinline Vector4::Vector4( float x, float y,float z,float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

__forceinline float Vector4::operator[]( int index ) const
{
	return (&x)[index];
}

__forceinline float &Vector4::operator[]( int index )
{
	return (&x)[index];
}


__forceinline Vector4& Vector4::operator=(const Vector4& a)
{
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
	this->w = a.w;

	return *this;
}


__forceinline Vector4 Vector4::operator-() 
{
	return Vector4(-x,-y,-z,-w);
}


__forceinline Vector4 Vector4::operator+(const Vector4& a) const
{
	return Vector4(x+a.x,y+a.y,z+a.z,w+a.w+w);

}

__forceinline Vector4 Vector4::operator-(const Vector4& a) const
{
	return Vector4(x-a.x,y-a.y,z-a.z,w-a.w);

}

__forceinline Vector4 Vector4::operator *(const float a) const
{
	return Vector4(x*a,y*a,z*a,w*a);
}


__forceinline Vector4 Vector4::operator /(const float a) const
{
	return Vector4(x/a,y/a,z/a,w/a);
}


__forceinline Vector4	operator *(const float a, const Vector4& v)
{
	return Vector4(v.x*a,v.y*a,v.z*a,v.w*a);
}

__forceinline Vector4& Vector4::operator+=(const Vector4& a) 
{
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;

	return *this;
}

__forceinline Vector4& Vector4::operator-=(const Vector4& a) 
{
	x -= a.x;
	y -= a.y;
	z -= a.z;
	w -= a.w;

	return *this;
}

__forceinline Vector4& Vector4::operator*=(const float& a) 
{
	x *= a;
	y *= a;
	z *= a;
	w *= a;

	return *this;
}

__forceinline Vector4& Vector4::operator/=(const float& a) 
{
	float invA = 1.0f/a;
	x *= invA;
	y *= invA;
	z *= invA;
	w *= invA;

	return *this;
}


__forceinline bool Vector4::operator == (const Vector4& a) const
{
	return x==a.x && y==a.y && z==a.z && w==a.w;

}

__forceinline bool Vector4::operator != (const Vector4& a) const
{
	return x!=a.x || y!=a.y || z!=a.z || w!=a.w;

}


__forceinline float Vector4::Length() const
{
	return sqrt(x*x + y*y + z*z + w*w);
}

__forceinline float Vector4::LengthSqr() const
{
	return x*x + y*y + z*z + w*w;
}

__forceinline void Vector4::Normalize()
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

__forceinline void Vector4::Zero()
{
	x = y = z = w = 0;
}


__forceinline float Vector4::Dot(const Vector4& a) const
{
	return x*a.x+y*a.y+z*a.z+w*a.w;
}


softbreeze_namespace_end

#endif

