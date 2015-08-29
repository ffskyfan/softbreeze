
#ifndef SOFTBREEZE_PIPE_LINE_H
#define SOFTBREEZE_PIPE_LINE_H

softbreeze_namespace_beg

namespace PipeLine
{
	void Projection(const VertexList& vertexList, OUTPUT VertexList& output);

	void ToScreen(const VertexList& vertexList, int width, int height, OUTPUT VertexList& output);

	void DrawVertexList(const VertexList& vertexList, UCHAR* video_buffer, int lpitch);
}

softbreeze_namespace_end

#endif


