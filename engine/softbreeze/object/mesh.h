

#ifndef SOFTBREEZE_MESH_H
#define SOFTBREEZE_MESH_H

#include "vertex.h"


softbreeze_namespace_beg

struct Mesh
{
	Mesh()
	{
		vertexNum = 0;
		indexNum  = 0;

		vertices  = 0;
		indices	  = 0;				
	}

	~Mesh()
	{
		if(vertices != 0) {
			delete vertices;
		}

		if(indices != 0) {
			delete indices;
		}
	}


	Vertex*			vertices;
	int				vertexNum;

	unsigned int*	indices;				
	int				indexNum;
};




softbreeze_namespace_end


#endif

