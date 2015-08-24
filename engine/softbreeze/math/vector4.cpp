
#include "Vector4.h"




void starVector4::Lerp( const starVector4 &v1, const starVector4 &v2, const float l )
{
	if(l <= 0.0f) {
		(*this) = v1;
	} else if (l >=1.0){
		(*this) = v2;
	} else {
		(*this) = v1 + l*( v2 - v1 );
	}
}


