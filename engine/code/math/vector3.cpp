

#include "Vector3.h"


void starVector3::Lerp( const starVector3 &v1, const starVector3 &v2, const float l )
{
	if(l <= 0.0f) {
		(*this) = v1;
	} else if (l >=1.0){
		(*this) = v2;
	} else {
		(*this) = v1 + l*( v2 - v1 );
	}
}



#define SLERP_DELTA  1e-6
void starVector3::SLerp( const starVector3 &v1, const starVector3 &v2, const float t )
{
	if(t <= 0.0f) {
		(*this) = v1;
		return;
	} else if (t >=1.0){
		(*this) = v2;
		return;
	}

	float omega, cosom, sinom, scale0, scale1;
	cosom = v1 * v2;
	if( (1.0f-cosom) > SLERP_DELTA ) {
		omega = acos(cosom);
		sinom = sin(omega);
		scale0 = sin((1.0f-t)*omega) / sinom;
		scale1 = sin(t*omega) / sinom;
	} else {//非常接近，用线性差值
		scale0 = 1.0f-t;
		scale1 = t;
	}

	(*this) = scale0*v1 + scale1*v2;

}
