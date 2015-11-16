
#ifndef SOFTBREEZE_PIPE_LINE_H
#define SOFTBREEZE_PIPE_LINE_H

softbreeze_namespace_beg

namespace PipeLine
{
	void Transform(const VertexList& vertexList, const Matrix4& matrix, OUTPUT VertexList& output);

	void ToWorld(const VertexList& vertexList, const Vector3& pos, OUTPUT VertexList& output);

	void RemoveBackface(const VertexList& vertexList, const Camera& camera, OUTPUT VertexList& output);


	void ToCamera(const VertexList& vertexList, const Camera& camera, OUTPUT VertexList& output);

	void Projection(const VertexList& vertexList,const Camera& camera, OUTPUT VertexList& output);

	void ToScreen(const VertexList& vertexList, int width, int height, OUTPUT VertexList& output);

	void DrawVertexList(const VertexList& vertexList);
}

softbreeze_namespace_end

#endif


