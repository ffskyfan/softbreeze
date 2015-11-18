

#ifndef SOFTBREEZE_VERTEX_LIST_H
#define SOFTBREEZE_VERTEX_LIST_H

#include "vertex.h"
#include <vector>


softbreeze_namespace_beg

struct VertexList
{
	VertexList()
	{
	}

	~VertexList()
	{
	}


	std::vector<Vertex>		vertices;

	std::vector<int>		indices;

	Vector3					pos;
};




softbreeze_namespace_end


#endif

