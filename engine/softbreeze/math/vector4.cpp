
#include "vector4.h"




void Vector4::Lerp( const Vector4 &v1, const Vector4 &v2, const float l )
{
	if(l <= 0.0f) {
		(*this) = v1;
	} else if (l >=1.0){
		(*this) = v2;
	} else {
		(*this) = v1 + l*( v2 - v1 );
	}
}


