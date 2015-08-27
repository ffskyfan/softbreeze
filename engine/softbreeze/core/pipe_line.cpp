
#include "../softbreeze.h"
#include "../math/matrix4.h"

#include "pipe_line.h"


softbreeze_namespace_beg

namespace PipeLine
{


	const Matrix4 ProjectionMatrix = Matrix4(1,0,0,0,
											 0,1,0,0,
											 0,0,1,1,
											 0,0,0,0);

}


softbreeze_namespace_end



