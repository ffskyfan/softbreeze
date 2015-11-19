
#ifndef SOFTBREEZE_PIPE_LINE_H
#define SOFTBREEZE_PIPE_LINE_H

softbreeze_namespace_beg

namespace PipeLine
{
	void Transform(const VertexBuffer& vertexBuffer, const Matrix4& matrix, OUTPUT VertexBuffer& output);

	void ToWorld(const VertexBuffer& vertexBuffer, OUTPUT VertexBuffer& output);

	void RemoveBackface(const VertexBuffer& vertexBuffer, const Camera& camera, OUTPUT VertexBuffer& output);

	void ToCamera(const VertexBuffer& vertexBuffer, const Camera& camera, OUTPUT VertexBuffer& output);

	void Clipping(const VertexBuffer& vertexBuffer, const Camera& camera, OUTPUT VertexBuffer& output);

	void Projection(const VertexBuffer& vertexBuffer,const Camera& camera, OUTPUT VertexBuffer& output);

	void ToScreen(const VertexBuffer& vertexBuffer, int width, int height, OUTPUT VertexBuffer& output);

	void DrawVertexList(const VertexBuffer& vertexBuffer);
}

softbreeze_namespace_end

#endif


