
#include "../softbreeze.h"

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>

#include "../math/matrix4.h"
#include "../math/matrix3.h"

#include "../math/vector2.h"
#include "../math/vector3.h"
#include "../math/vector4.h"
#include "../object/vertex.h"
#include "../object/vertex_list.h"
#include "../object/camera.h"
#include "../core/graphic.h"

#include "pipe_line.h"

softbreeze_namespace_beg

namespace PipeLine
{

	void Transform(const VertexList& vertexList,const Matrix4& matrix, OUTPUT VertexList& output)
	{
		std::vector<Vertex>::const_iterator it = vertexList.vertices.begin();
		std::vector<Vertex>::const_iterator itEnd = vertexList.vertices.end();
		for(; it != itEnd; it++) {
			const Vertex& vertex = *it;

			Vector4 newXYZ(vertex.xyz.x, vertex.xyz.y, vertex.xyz.z, 1);
			newXYZ = newXYZ*matrix;

			Vertex newVertex = vertex;
			newVertex.xyz = Vector3(newXYZ.x, newXYZ.y, newXYZ.z);

			output.vertices.push_back(newVertex);
		}

		std::vector<int>::const_iterator indexIt = vertexList.indices.begin();
		std::vector<int>::const_iterator indexItEnd = vertexList.indices.end();
		for(; indexIt != indexItEnd; indexIt++) {
			output.indices.push_back(*indexIt);
		}
	}


	void ToWorld(const VertexList& vertexList, const Vector3& pos, OUTPUT VertexList& output)
	{
		std::vector<Vertex>::const_iterator it = vertexList.vertices.begin();
		std::vector<Vertex>::const_iterator itEnd = vertexList.vertices.end();
		for(; it != itEnd; it++) {
			const Vertex& vertex = *it;

			Vertex newVertex = vertex;
			newVertex.xyz = vertex.xyz+pos;

			output.vertices.push_back(newVertex);
		}

		std::vector<int>::const_iterator indexIt = vertexList.indices.begin();
		std::vector<int>::const_iterator indexItEnd = vertexList.indices.end();
		for(; indexIt != indexItEnd; indexIt++) {
			output.indices.push_back(*indexIt);
		}
	}


	void RemoveBackface(const VertexList& vertexList, const Camera& camera, OUTPUT VertexList& output)
	{

		std::vector<Vertex>::const_iterator it = vertexList.vertices.begin();
		std::vector<Vertex>::const_iterator itEnd = vertexList.vertices.end();
		for(; it != itEnd; it++) {
			const Vertex& vertex = *it;
			output.vertices.push_back(vertex);
		}

		size_t count = vertexList.indices.size();
		for(size_t i = 0; ((i+1)*3)<=count; i++) {
			int idx0 = vertexList.indices[i * 3];
			int idx1 = vertexList.indices[(i * 3)+1];
			int idx2 = vertexList.indices[(i * 3)+2];

			const Vector3& vec0 = vertexList.vertices[idx0].xyz;
			const Vector3& vec1 = vertexList.vertices[idx1].xyz;
			const Vector3& vec2 = vertexList.vertices[idx2].xyz;

			Vector3 u = vec1 - vec0;
			Vector3 v = vec2 - vec0;
			Vector3 n = v.Cross(u);

			const Vector3& cameraPos = camera.GetPos();
			Vector3 viewVector = vec1 - cameraPos;
			float dp = n*viewVector;
			if(dp > 0) {
				output.indices.push_back(idx0);
				output.indices.push_back(idx1);
				output.indices.push_back(idx2);
			}
		}

	}


	void ToCamera(const VertexList& vertexList, const Camera& camera, OUTPUT VertexList& output)
	{
		const Matrix4& matrix = camera.MakeCameraMatrix();

		Transform(vertexList, matrix, output);
	}


	const Matrix4 ProjectionMatrix = Matrix4(1,0,0,0,
											 0,1,0,0,
											 0,0,1,1,
											 0,0,0,0);

	void Projection(const VertexList& vertexList,const Camera& camera, OUTPUT VertexList& output)
	{
		float aspectRatio = camera.GetAspectRatio();
		
		std::vector<Vertex>::const_iterator it = vertexList.vertices.begin();
		std::vector<Vertex>::const_iterator itEnd = vertexList.vertices.end();
		for(; it != itEnd; it++) {
			const Vertex vertex = *it;
			float z = vertex.xyz.z;

			Vector3 projectionVector;
			projectionVector.x = vertex.xyz.x / z;
			projectionVector.y = vertex.xyz.y*aspectRatio / z; //这样的投影是个方形，将来有了镜头后，可以设置镜头宽高比，之后用y乘以宽高比，计算出y的坐标
			projectionVector.z = z;

			Vertex projectionVertex;
			projectionVertex.xyz = projectionVector;
			for(int i = 0; i < 3; i++) {
				projectionVertex.color[i] = vertex.color[i];
			}
			projectionVertex.normal = vertex.normal;
			projectionVertex.textureCoord = vertex.textureCoord;

			output.vertices.push_back(projectionVertex);
		}

		std::vector<int>::const_iterator indexIt = vertexList.indices.begin();
		std::vector<int>::const_iterator indexItEnd = vertexList.indices.end();
		for(; indexIt != indexItEnd; indexIt++) {
			output.indices.push_back(*indexIt);
		}
	}


	void ToScreen(const VertexList& vertexList, int width, int height, OUTPUT VertexList& output)
	{
		std::vector<Vertex>::const_iterator it = vertexList.vertices.begin();
		std::vector<Vertex>::const_iterator itEnd = vertexList.vertices.end();
		for(; it != itEnd; it++) {
			const Vertex vertex = *it;

			Vector3 screenVector;
			screenVector.x = (vertex.xyz.x + 1) * (0.5f * width -0.5f);
			screenVector.y = (height - 1) - (vertex.xyz.y + 1)*(0.5f * height -0.5f);

			Vertex screenVertex;
			screenVertex.xyz = screenVector;
			for(int i = 0; i < 3; i++) {
				screenVertex.color[i] = vertex.color[i];
			}
			screenVertex.normal = vertex.normal;
			screenVertex.textureCoord = vertex.textureCoord;

			output.vertices.push_back(screenVertex);
		}

		std::vector<int>::const_iterator indexIt = vertexList.indices.begin();
		std::vector<int>::const_iterator indexItEnd = vertexList.indices.end();
		for(; indexIt != indexItEnd; indexIt++) {
			output.indices.push_back(*indexIt);
		}


	}


	void DrawVertexList(const VertexList& vertexList)
	{
		Graphic& graphic = Graphic::Instance();
		int indexCount = (int)vertexList.indices.size();
		for(int i = 0; ((i+1)*3) <= indexCount; i++) {

			int idx0 = vertexList.indices[i * 3];
			int idx1 = vertexList.indices[(i * 3)+1];
			int idx2 = vertexList.indices[(i * 3)+2];

			Vector2 pos0( vertexList.vertices[idx0].xyz.x, vertexList.vertices[idx0].xyz.y);
			Vector2 pos1( vertexList.vertices[idx1].xyz.x, vertexList.vertices[idx1].xyz.y);
			Vector2 pos2( vertexList.vertices[idx2].xyz.x, vertexList.vertices[idx2].xyz.y);

			graphic.DrawLine(pos0,pos1,0xFF0000FF);
			graphic.DrawLine(pos1,pos2,0xFF0000FF);
			graphic.DrawLine(pos2,pos0,0xFF0000FF);
		}

	}


}


softbreeze_namespace_end



