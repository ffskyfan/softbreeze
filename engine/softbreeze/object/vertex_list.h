

#ifndef SOFTBREEZE_VERTEX_LIST_H
#define SOFTBREEZE_VERTEX_LIST_H

#include "vertex.h"
#include <vector>



struct VertexList
{
	VertexList()
	{
	}

	~VertexList()
	{
	}


	std::vector<Vertex>	vertices;

	std::vector<int>	indices;
};






#endif

