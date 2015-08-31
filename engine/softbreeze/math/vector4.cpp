
#include "../softbreeze.h"
#include "vector4.h"


softbreeze_namespace_beg


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




softbreeze_namespace_end

