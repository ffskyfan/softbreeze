

#ifndef SOFTBREEZE_MESH_H
#define SOFTBREEZE_MESH_H

#include "vertex.h"
#include <vector>

softbreeze_namespace_beg

struct Mesh
{
	Mesh()
	{
	}

	~Mesh()
	{
	}


	std::vector<Vertex>				vertices;
	std::vector<unsigned int>		indices;
};




softbreeze_namespace_end


#endif

