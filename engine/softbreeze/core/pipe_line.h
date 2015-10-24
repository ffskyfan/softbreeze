
#ifndef SOFTBREEZE_PIPE_LINE_H
#define SOFTBREEZE_PIPE_LINE_H

softbreeze_namespace_beg

namespace PipeLine
{

	void Transform(const VertexList& vertexList, const Matrix4& matrix, OUTPUT VertexList& output);

	void Projection(const VertexList& vertexList, OUTPUT VertexList& output);

	void ToScreen(const VertexList& vertexList, int width, int height, OUTPUT VertexList& output);

	void DrawVertexList(const VertexList& vertexList);
}

softbreeze_namespace_end

#endif


