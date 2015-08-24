
#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vector3.h"
#include "Vector4.h"
#include "MathDef.h"

#include <math.h>
#include <cstring>

class starMatrix3;


class starMatrix4
{
public:
	starMatrix4();
	explicit starMatrix4(const starVector4& x,const starVector4& y,const starVector4& z,const starVector4& w);
	explicit starMatrix4(const float xx,const float xy,const float xz,const float xw,
						 const float yx,const float yy,const float yz,const float yw,
						 const float zx,const float zy,const float zz,const float zw,
						 const float wx,const float wy,const float wz,const float ww);

	explicit starMatrix4( const starMatrix3 &rotation, const starVector3 &translation );
	explicit starMatrix4( const float src[ 4 ][ 4 ] );
	explicit starMatrix4( const float src[ 16 ]);


	const starVector4&	operator[]( int index ) const;
	starVector4&		operator[]( int index );

	starMatrix4			operator*( const float a ) const;
	starVector4			operator*( const starVector4 &vec ) const;
	starVector3			operator*( const starVector3 &vec ) const;
	starMatrix4			operator*( const starMatrix4 &a ) const;
	starMatrix4			operator+( const starMatrix4 &a ) const;
	starMatrix4			operator-( const starMatrix4 &a ) const;

	starMatrix4&		operator*=( const float a );
	starMatrix4&		operator*=( const starMatrix4 &a );
	starMatrix4&		operator+=( const starMatrix4 &a );
	starMatrix4&		operator-=( const starMatrix4 &a );

	friend starMatrix4	operator*( const float a, const starMatrix4 &mat );
	friend starVector4	operator*( const starVector4 &vec, const starMatrix4 &mat );
	friend starVector3	operator*( const starVector3 &vec, const starMatrix4 &mat );
	friend starVector4&	operator*=( starVector4 &vec, const starMatrix4 &mat );
	friend starVector3&	operator*=( starVector3 &vec, const starMatrix4 &mat );

	bool				Compare( const starMatrix4 &a ) const;						
	bool				Compare( const starMatrix4 &a, const float epsilon ) const;	
	bool				operator==( const starMatrix4 &a ) const;					
	bool				operator!=( const starMatrix4 &a ) const;					

	void				Zero( );
	void				Identity(  );
	bool				IsIdentity( const float epsilon = MATRIX_EPSILON ) const;


public:
	starVector4 data[4];

};


extern starMatrix4 matrix4_zero;
extern starMatrix4 matrix4_identity;

__forceinline starMatrix4::starMatrix4(const starVector4& x,const starVector4& y,const starVector4& z,const starVector4& w)
{
	data[0]= x;
	data[1]= y;
	data[2]= z;
	data[3]= w;
}


__forceinline starMatrix4::starMatrix4(const float xx,const float xy,const float xz,const float xw,
						 const float yx,const float yy,const float yz,const float yw,
						 const float zx,const float zy,const float zz,const float zw,
						 const float wx,const float wy,const float wz,const float ww)
{
	data[0][0] = xx;	data[0][1] = xy;	data[0][2] = xz;	data[0][3] = xw;
	data[1][0] = yx;	data[1][1] = yy;	data[1][2] = yz;	data[1][3] = yw;
	data[2][0] = zx;	data[2][1] = zy;	data[2][2] = zz;	data[2][3] = zw;
	data[3][0] = wx;	data[3][1] = wy;	data[3][2] = wz;	data[3][3] = ww;
}


__forceinline starMatrix4::starMatrix4( const starMatrix3 &rotation, const starVector3 &translation )
{


}


__forceinline starMatrix4::starMatrix4( const float src[ 4 ][ 4 ] )
{
	data[0][0] = src[0][0];	data[0][1] = src[0][1];	data[0][2] = src[0][2];	data[0][3] = src[0][3];
	data[1][0] = src[1][0];	data[1][1] = src[1][1];	data[1][2] = src[1][2];	data[1][3] = src[1][3];
	data[2][0] = src[2][0];	data[2][1] = src[2][1];	data[2][2] = src[2][2];	data[2][3] = src[2][3];
	data[3][0] = src[3][0];	data[3][1] = src[3][1];	data[3][2] = src[3][2];	data[3][3] = src[3][3];
}

__forceinline starMatrix4::starMatrix4( const float src[ 16 ])
{
	data[0][0] = src[0];	data[0][1] = src[1];	data[0][2] = src[2];	data[0][3] = src[3];
	data[1][0] = src[4];	data[1][1] = src[5];	data[1][2] = src[6];	data[1][3] = src[7];
	data[2][0] = src[8];	data[2][1] = src[9];	data[2][2] = src[10];	data[2][3] = src[11];
	data[3][0] = src[12];	data[3][1] = src[13];	data[3][2] = src[14];	data[3][3] = src[15];
}



__forceinline const starVector4& starMatrix4::	operator[]( int index ) const
{
	return data[index];
}

__forceinline starVector4& starMatrix4::operator[]( int index )
{
	return data[index];
}

__forceinline starMatrix4 starMatrix4::operator*( const float a ) const
{
	return starMatrix4(
		data[0].x*a, data[0].y*a, data[0].z*a, data[0].w*a,
		data[1].x*a, data[1].y*a, data[1].z*a, data[1].w*a,
		data[2].x*a, data[2].y*a, data[2].z*a, data[2].w*a,
		data[3].x*a, data[3].y*a, data[3].z*a, data[3].w*a);
}

__forceinline starVector4 starMatrix4::operator*( const starVector4 &vec ) const
{
	return starVector4(
		data[0].x*vec.x + data[0].y*vec.y + data[0].z*vec.z + data[0].w*vec.w,
		data[1].x*vec.x + data[1].y*vec.y + data[1].z*vec.z + data[1].w*vec.w,
		data[2].x*vec.x + data[2].y*vec.y + data[2].z*vec.z + data[2].w*vec.w,
		data[3].x*vec.x + data[3].y*vec.y + data[3].z*vec.z + data[3].w*vec.w);

}


__forceinline starVector3 starMatrix4::operator*( const starVector3 &vec ) const
{
	float s = data[3].x*vec.x + data[3].y*vec.y + data[3].z*vec.z + data[3].w;
	if( s == 0.0f ){
		return starVector3(0.0f,0.0f,0.0f);
	}

	if( s == 1.0f ) {
		return starVector3(
			data[0].x*vec.x + data[0].y*vec.y + data[0].z*vec.z + data[0].w,
			data[1].x*vec.x + data[1].y*vec.y + data[1].z*vec.z + data[1].w,
			data[2].x*vec.x + data[2].y*vec.y + data[2].z*vec.z + data[2].w);
	} else {
		float invS = 1.0f / s;
		return starVector3(
			(data[0].x*vec.x + data[0].y*vec.y + data[0].z*vec.z + data[0].w) * invS,
			(data[1].x*vec.x + data[1].y*vec.y + data[1].z*vec.z + data[1].w) * invS,
			(data[2].x*vec.x + data[2].y*vec.y + data[2].z*vec.z + data[2].w) * invS);
	}
}


__forceinline starMatrix4 starMatrix4::operator*( const starMatrix4 &a ) const
{
	int i, j;
	const float *m1Ptr, *m2Ptr;
	float *dstPtr;
	starMatrix4 dst;

	m1Ptr = reinterpret_cast<const float *>(this);
	m2Ptr = reinterpret_cast<const float *>(&a);
	dstPtr = reinterpret_cast<float *>(&dst);

	for ( i = 0; i < 4; i++ ) {
		for ( j = 0; j < 4; j++ ) {
			*dstPtr = m1Ptr[0] * m2Ptr[ 0 * 4 + j ]
					+ m1Ptr[1] * m2Ptr[ 1 * 4 + j ]
					+ m1Ptr[2] * m2Ptr[ 2 * 4 + j ]
					+ m1Ptr[3] * m2Ptr[ 3 * 4 + j ];
			dstPtr++;
		}
		m1Ptr += 4;
	}
	return dst;
}


__forceinline starMatrix4 starMatrix4::operator+( const starMatrix4 &a ) const
{
	return starMatrix4 (
		data[0].x + a.data[0].x,data[0].y + a.data[0].y,data[0].z + a.data[0].z, data[0].w + a.data[0].w,
		data[1].x + a.data[1].x,data[1].y + a.data[1].y,data[1].z + a.data[1].z, data[1].w + a.data[1].w,
		data[2].x + a.data[2].x,data[2].y + a.data[2].y,data[2].z + a.data[2].z, data[2].w + a.data[2].w,
		data[3].x + a.data[3].x,data[3].y + a.data[3].y,data[3].z + a.data[3].z, data[3].w + a.data[3].w);
}

__forceinline starMatrix4 starMatrix4::operator-( const starMatrix4 &a ) const
{
	return starMatrix4 (
		data[0].x - a.data[0].x,data[0].y - a.data[0].y,data[0].z - a.data[0].z, data[0].w - a.data[0].w,
		data[1].x - a.data[1].x,data[1].y - a.data[1].y,data[1].z - a.data[1].z, data[1].w - a.data[1].w,
		data[2].x - a.data[2].x,data[2].y - a.data[2].y,data[2].z - a.data[2].z, data[2].w - a.data[2].w,
		data[3].x - a.data[3].x,data[3].y - a.data[3].y,data[3].z - a.data[3].z, data[3].w - a.data[3].w);
}


__forceinline starMatrix4& starMatrix4::operator*=( const float a )
{
	data[0].x *= a; data[0].y *= a; data[0].z *= a; data[0].w *= a;
	data[1].x *= a; data[1].y *= a; data[1].z *= a; data[1].w *= a;
	data[2].x *= a; data[2].y *= a; data[2].z *= a; data[2].w *= a;
	data[3].x *= a; data[3].y *= a; data[3].z *= a; data[3].w *= a;

}

__forceinline starMatrix4& starMatrix4::operator*=( const starMatrix4& a )
{
	(*this) = (*this) * a;
	return *this;
}

__forceinline starMatrix4& starMatrix4::operator+=( const starMatrix4& a )
{
	data[0].x += a[0].x; data[0].y += a[0].y; data[0].z += a[0].z; data[0].w += a[0].w;
	data[1].x += a[1].x; data[1].y += a[1].y; data[1].z += a[1].z; data[1].w += a[1].w;
	data[2].x += a[2].x; data[2].y += a[2].y; data[2].z += a[2].z; data[2].w += a[2].w;
	data[3].x += a[3].x; data[3].y += a[3].y; data[3].z += a[3].z; data[3].w += a[3].w;
	return *this;
}

__forceinline starMatrix4& starMatrix4::operator-=( const starMatrix4& a )
{
	data[0].x -= a[0].x; data[0].y -= a[0].y; data[0].z -= a[0].z; data[0].w -= a[0].w;
	data[1].x -= a[1].x; data[1].y -= a[1].y; data[1].z -= a[1].z; data[1].w -= a[1].w;
	data[2].x -= a[2].x; data[2].y -= a[2].y; data[2].z -= a[2].z; data[2].w -= a[2].w;
	data[3].x -= a[3].x; data[3].y -= a[3].y; data[3].z -= a[3].z; data[3].w -= a[3].w;
	return *this;
}


__forceinline starMatrix4	operator*( const float a, const starMatrix4 &mat )
{
	return mat*a;
}

__forceinline starVector4	operator*( const starVector4 &vec, const starMatrix4 &mat )
{
	return mat*vec;
}

__forceinline starVector3	operator*( const starVector3 &vec, const starMatrix4 &mat )
{
	return mat*vec;
}

__forceinline starVector4&	operator*=( starVector4 &vec, const starMatrix4 &mat )
{
	vec = mat*vec;
	return vec;
}

__forceinline starVector3&	operator*=( starVector3 &vec, const starMatrix4 &mat )
{
	vec = mat*vec;
	return vec;
}


__forceinline bool starMatrix4::Compare( const starMatrix4 &a ) const
{
	unsigned int i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(data);
	ptr2 = reinterpret_cast<const float *>(a.data);
	for ( i = 0; i < 4*4; i++ ) {
		if ( ptr1[i] != ptr2[i] ) {
			return false;
		}
	}
	return true;
}

__forceinline bool starMatrix4::Compare( const starMatrix4 &a, const float epsilon ) const 
{
	unsigned int i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(data);
	ptr2 = reinterpret_cast<const float *>(a.data);
	for ( i = 0; i < 4*4; i++ ) {
		if ( fabs( ptr2[i] - ptr2[i]) > epsilon ) {
			return false;
		}
	}
	return true;
}

__forceinline bool starMatrix4::operator==( const starMatrix4 &a ) const 
{
	return Compare(a);
}


__forceinline bool starMatrix4::operator!=( const starMatrix4 &a ) const 
{
	return !Compare(a);
}


__forceinline void starMatrix4::Zero( )
{
	memset((void*)data, 0, sizeof(starMatrix4));
}

__forceinline void starMatrix4::Identity( )
{
	(*this) = matrix4_identity;
}
	
__forceinline bool starMatrix4::IsIdentity( const float epsilon ) const
{
	return Compare(matrix4_identity,epsilon);
}

#endif
















