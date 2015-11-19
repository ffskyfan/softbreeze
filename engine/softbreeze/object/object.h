

#ifndef SOFTBREEZE_OBJECT_H
#define SOFTBREEZE_OBJECT_H

#include "mesh.h"
#include "../math/vector3.h"


softbreeze_namespace_beg

class Object
{
	Object()
	{
	}

	~Mesh()
	{
	}


	Mesh*			mesh;
	Vector3			pos;
};




softbreeze_namespace_end


#endif

