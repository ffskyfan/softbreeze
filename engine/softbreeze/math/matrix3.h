

#ifndef MATRIX3_H
#define MATRIX3_H

#include "vector3.h"
#include "vector4.h"
#include "math_def.h"

#include <math.h>
#include <cstring>


softbreeze_namespace_beg

class Matrix3;


class Matrix3
{
public:
	Matrix3();
	explicit Matrix3(const Vector3& x,const Vector3& y,const Vector3& z);
	explicit Matrix3(const float xx,const float xy,const float xz,
						 const float yx,const float yy,const float yz,
						 const float zx,const float zy,const float zz);

	explicit Matrix3( const float src[ 3 ][ 3 ] );
	explicit Matrix3( const float src[ 9 ]);


	const Vector3&	operator[]( int index ) const;
	Vector3&		operator[]( int index );

	Matrix3			operator*( const float a ) const;
	Matrix3			operator*( const Matrix3 &a ) const;
	Matrix3			operator+( const Matrix3 &a ) const;
	Matrix3			operator-( const Matrix3 &a ) const;

	Matrix3&		operator*=( const float a );
	Matrix3&		operator*=( const Matrix3 &a );
	Matrix3&		operator+=( const Matrix3 &a );
	Matrix3&		operator-=( const Matrix3 &a );

	friend Matrix3	operator*( const float a, const Matrix3 &mat );
	friend Vector3	operator*( const Vector3 &vec, const Matrix3 &mat );
	friend Vector3&	operator*=( Vector3 &vec, const Matrix3 &mat );

	bool				Compare( const Matrix3 &a ) const;						
	bool				Compare( const Matrix3 &a, const float epsilon ) const;	
	bool				operator==( const Matrix3 &a ) const;					
	bool				operator!=( const Matrix3 &a ) const;					

	void				Zero( );
	void				Identity(  );
	bool				IsIdentity( const float epsilon = MATRIX_EPSILON ) const;


public:
	Vector3 data[4];

};


extern Matrix3 matrix3_zero;
extern Matrix3 matrix3_identity;

__forceinline Matrix3::Matrix3(const Vector3& x,const Vector3& y,const Vector3& z)
{
	data[0]= x;
	data[1]= y;
	data[2]= z;
}


__forceinline Matrix3::Matrix3(const float xx,const float xy,const float xz,
									   const float yx,const float yy,const float yz,
									   const float zx,const float zy,const float zz)
{
	data[0][0] = xx;	data[0][1] = xy;	data[0][2] = xz;	
	data[1][0] = yx;	data[1][1] = yy;	data[1][2] = yz;	
	data[2][0] = zx;	data[2][1] = zy;	data[2][2] = zz;	
}


__forceinline Matrix3::Matrix3( const float src[ 3 ][ 3 ] )
{
	data[0][0] = src[0][0];	data[0][1] = src[0][1];	data[0][2] = src[0][2];	
	data[1][0] = src[1][0];	data[1][1] = src[1][1];	data[1][2] = src[1][2];
	data[2][0] = src[2][0];	data[2][1] = src[2][1];	data[2][2] = src[2][2];
}

__forceinline Matrix3::Matrix3( const float src[ 9 ])
{
	data[0][0] = src[0];	data[0][1] = src[1];	data[0][2] = src[2];	
	data[1][0] = src[3];	data[1][1] = src[4];	data[1][2] = src[5];	
	data[2][0] = src[6];	data[2][1] = src[7];	data[2][2] = src[8];
}



__forceinline const Vector3& Matrix3::	operator[]( int index ) const
{
	return data[index];
}

__forceinline Vector3& Matrix3::operator[]( int index )
{
	return data[index];
}

__forceinline Matrix3 Matrix3::operator*( const float a ) const
{
	return Matrix3(
		data[0].x*a, data[0].y*a, data[0].z*a,
		data[1].x*a, data[1].y*a, data[1].z*a,
		data[2].x*a, data[2].y*a, data[2].z*a);
}



__forceinline Matrix3 Matrix3::operator*( const Matrix3 &a ) const
{
	int i, j;
	const float *m1Ptr, *m2Ptr;
	float *dstPtr;
	Matrix3 dst;

	m1Ptr = reinterpret_cast<const float *>(this);
	m2Ptr = reinterpret_cast<const float *>(&a);
	dstPtr = reinterpret_cast<float *>(&dst);

	for ( i = 0; i < 3; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			*dstPtr = m1Ptr[0] * m2Ptr[ 0 * 3 + j ]
					+ m1Ptr[1] * m2Ptr[ 1 * 3 + j ]
					+ m1Ptr[2] * m2Ptr[ 2 * 3 + j ];
			dstPtr++;
		}
		m1Ptr += 3;
	}
	return dst;
}


__forceinline Matrix3 Matrix3::operator+( const Matrix3 &a ) const
{
	return Matrix3 (
		data[0].x + a.data[0].x,data[0].y + a.data[0].y,data[0].z + a.data[0].z,
		data[1].x + a.data[1].x,data[1].y + a.data[1].y,data[1].z + a.data[1].z,
		data[2].x + a.data[2].x,data[2].y + a.data[2].y,data[2].z + a.data[2].z);
}

__forceinline Matrix3 Matrix3::operator-( const Matrix3 &a ) const
{
	return Matrix3 (
		data[0].x - a.data[0].x,data[0].y - a.data[0].y,data[0].z - a.data[0].z,
		data[1].x - a.data[1].x,data[1].y - a.data[1].y,data[1].z - a.data[1].z,
		data[2].x - a.data[2].x,data[2].y - a.data[2].y,data[2].z - a.data[2].z);
}


__forceinline Matrix3& Matrix3::operator*=( const float a )
{
	data[0].x *= a; data[0].y *= a; data[0].z *= a; 
	data[1].x *= a; data[1].y *= a; data[1].z *= a; 
	data[2].x *= a; data[2].y *= a; data[2].z *= a; 
}

__forceinline Matrix3& Matrix3::operator*=( const Matrix3& a )
{
	(*this) = (*this) * a;
	return *this;
}

__forceinline Matrix3& Matrix3::operator+=( const Matrix3& a )
{
	data[0].x += a[0].x; data[0].y += a[0].y; data[0].z += a[0].z; 
	data[1].x += a[1].x; data[1].y += a[1].y; data[1].z += a[1].z; 
	data[2].x += a[2].x; data[2].y += a[2].y; data[2].z += a[2].z; 
	return *this;
}

__forceinline Matrix3& Matrix3::operator-=( const Matrix3& a )
{
	data[0].x -= a[0].x; data[0].y -= a[0].y; data[0].z -= a[0].z;
	data[1].x -= a[1].x; data[1].y -= a[1].y; data[1].z -= a[1].z;
	data[2].x -= a[2].x; data[2].y -= a[2].y; data[2].z -= a[2].z;
	return *this;
}


__forceinline Matrix3	operator*( const float a, const Matrix3 &mat )
{
	return mat*a;
}

__forceinline Vector3	operator*( const Vector3 &vec, const Matrix3 &mat )
{
	return Vector3(
		vec.x*mat.data[0].x + vec.y*mat.data[1].x + vec.z*mat.data[2].x,
		vec.x*mat.data[0].y + vec.y*mat.data[1].y + vec.z*mat.data[2].y,
		vec.x*mat.data[0].z + vec.y*mat.data[1].z + vec.z*mat.data[2].z);
}


__forceinline Vector3&	operator*=( Vector3 &vec, const Matrix3 &mat )
{
	vec = vec*mat;
	return vec;
}

__forceinline bool Matrix3::Compare( const Matrix3 &a ) const
{
	unsigned int i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(data);
	ptr2 = reinterpret_cast<const float *>(a.data);
	for ( i = 0; i < 3*3; i++ ) {
		if ( ptr1[i] != ptr2[i] ) {
			return false;
		}
	}
	return true;
}

__forceinline bool Matrix3::Compare( const Matrix3 &a, const float epsilon ) const 
{
	unsigned int i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(data);
	ptr2 = reinterpret_cast<const float *>(a.data);
	for ( i = 0; i < 3*3; i++ ) {
		if ( fabs( ptr2[i] - ptr2[i]) > epsilon ) {
			return false;
		}
	}
	return true;
}

__forceinline bool Matrix3::operator==( const Matrix3 &a ) const 
{
	return Compare(a);
}


__forceinline bool Matrix3::operator!=( const Matrix3 &a ) const 
{
	return !Compare(a);
}


__forceinline void Matrix3::Zero( )
{
	memset((void*)data, 0, sizeof(Matrix3));
}

__forceinline void Matrix3::Identity( )
{
	(*this) = matrix3_identity;
}
	
__forceinline bool Matrix3::IsIdentity( const float epsilon ) const
{
	return Compare(matrix3_identity,epsilon);
}





softbreeze_namespace_end




#endif

















