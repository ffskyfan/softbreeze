

#ifndef SOFTBREEZE_VERTEX_BUFFER_H
#define SOFTBREEZE_VERTEX_BUFFER_H

softbreeze_namespace_beg

struct VertexBuffer
{
	VertexBuffer()
	{
	}

	~VertexBuffer()
	{
		std::vector<VertexList*>::iterator it =	lists.begin();
		std::vector<VertexList*>::iterator itEnd =	lists.end();
		for(; it != itEnd; it++) {
			VertexList* vertices = *it;
			if(vertices) {
				delete vertices;
			}
		}

	}

	std::vector<VertexList*>	lists;
};




softbreeze_namespace_end



#endif

