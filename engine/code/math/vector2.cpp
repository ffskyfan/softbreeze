
#include "Vector2.h"




void starVector2::Lerp(const starVector2 &v1, const starVector2 &v2, const float l)
{
	if(l <= 0.0f) {
		(*this) = v1;
	} else if (l >=1.0){
		(*this) = v2;
	} else {
		(*this) = v1 + l*( v2 - v1 );
	}
}
