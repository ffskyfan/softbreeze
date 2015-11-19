
#include "../softbreeze.h"

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>

#include "../math/matrix4.h"
#include "../math/matrix3.h"

#include "../math/vector2.h"
#include "../math/vector3.h"
#include "../math/vector4.h"
#include "../math/utility.h"
#include "../object/vertex.h"
#include "../object/vertex_list.h"
#include "../object/vertex_buffer.h"
#include "../object/camera.h"
#include "../core/graphic.h"

#include "pipe_line.h"

softbreeze_namespace_beg

namespace PipeLine
{

	void Transform(const VertexBuffer& vertexBuffer,const Matrix4& matrix, OUTPUT VertexBuffer& output)
	{
		std::vector<VertexList*>::const_iterator bufferIt = vertexBuffer.lists.begin();
		std::vector<VertexList*>::const_iterator bufferItEnd = vertexBuffer.lists.end();
		for(; bufferIt != bufferItEnd; bufferIt++) {
			const VertexList& vertexList = **bufferIt;
			VertexList* newVertices = new VertexList;

			std::vector<Vertex>::const_iterator it = vertexList.vertices.begin();
			std::vector<Vertex>::const_iterator itEnd = vertexList.vertices.end();
			for(; it != itEnd; it++) {
				const Vertex& vertex = *it;

				Vector4 newXYZ(vertex.xyz.x, vertex.xyz.y, vertex.xyz.z, 1);
				newXYZ = newXYZ*matrix;

				Vertex newVertex = vertex;
				newVertex.xyz = Vector3(newXYZ.x, newXYZ.y, newXYZ.z);

				newVertices->vertices.push_back(newVertex);
			}

			std::vector<int>::const_iterator indexIt = vertexList.indices.begin();
			std::vector<int>::const_iterator indexItEnd = vertexList.indices.end();
			for(; indexIt != indexItEnd; indexIt++) {
				newVertices->indices.push_back(*indexIt);
			}

			newVertices->pos = vertexList.pos;

			output.lists.push_back(newVertices);

		}

	}


	void ToWorld(const VertexBuffer& vertexBuffer, OUTPUT VertexBuffer& output)
	{
		std::vector<VertexList*>::const_iterator bufferIt = vertexBuffer.lists.begin();
		std::vector<VertexList*>::const_iterator bufferItEnd = vertexBuffer.lists.end();
		for(; bufferIt != bufferItEnd; bufferIt++) {
			const VertexList& vertexList = **bufferIt;
			VertexList* newVertices = new VertexList;

			std::vector<Vertex>::const_iterator it = vertexList.vertices.begin();
			std::vector<Vertex>::const_iterator itEnd = vertexList.vertices.end();
			for(; it != itEnd; it++) {
				const Vertex& vertex = *it;

				Vertex newVertex = vertex;
				newVertex.xyz = vertex.xyz + vertexList.pos;

				newVertices->vertices.push_back(newVertex);
			}

			std::vector<int>::const_iterator indexIt = vertexList.indices.begin();
			std::vector<int>::const_iterator indexItEnd = vertexList.indices.end();
			for(; indexIt != indexItEnd; indexIt++) {
				newVertices->indices.push_back(*indexIt);
			}

			newVertices->pos = vertexList.pos;

			output.lists.push_back(newVertices);
		}
	}


	void RemoveBackface(const VertexBuffer& vertexBuffer, const Camera& camera, OUTPUT VertexBuffer& output)
	{
		std::vector<VertexList*>::const_iterator bufferIt = vertexBuffer.lists.begin();
		std::vector<VertexList*>::const_iterator bufferItEnd = vertexBuffer.lists.end();
		for(; bufferIt != bufferItEnd; bufferIt++) {
			const VertexList& vertexList = **bufferIt;
			VertexList* newVertices = new VertexList;

			std::vector<Vertex>::const_iterator it = vertexList.vertices.begin();
			std::vector<Vertex>::const_iterator itEnd = vertexList.vertices.end();
			for(; it != itEnd; it++) {
				const Vertex& vertex = *it;
				newVertices->vertices.push_back(vertex);
			}

			size_t count = vertexList.indices.size();
			for(size_t i = 0; ((i + 1) * 3) <= count; i++) {
				int idx0 = vertexList.indices[i * 3];
				int idx1 = vertexList.indices[(i * 3) + 1];
				int idx2 = vertexList.indices[(i * 3) + 2];

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
					newVertices->indices.push_back(idx0);
					newVertices->indices.push_back(idx1);
					newVertices->indices.push_back(idx2);
				}
			}

			newVertices->pos = vertexList.pos;

			output.lists.push_back(newVertices);
		}

	}


	void ToCamera(const VertexBuffer& vertexBuffer, const Camera& camera, OUTPUT VertexBuffer& output)
	{
		const Matrix4& matrix = camera.MakeCameraMatrix();

		Transform(vertexBuffer, matrix, output);
	}


	void Clipping(const VertexBuffer& vertexBuffer, const Camera& camera,  OUTPUT VertexBuffer& output)
	{
		std::vector<VertexList*>::const_iterator bufferIt = vertexBuffer.lists.begin();
		std::vector<VertexList*>::const_iterator bufferItEnd = vertexBuffer.lists.end();
		for(; bufferIt != bufferItEnd; bufferIt++) {
			const VertexList& vertexList = **bufferIt;

			bool isInFrustum = false;
			std::vector<Vertex>::const_iterator it = vertexList.vertices.begin();
			std::vector<Vertex>::const_iterator itEnd = vertexList.vertices.end();
			for(; it != itEnd; it++) {
				const Vertex& vertex = *it;

				float xTest = tan(AngleToRadian(camera.GetFov()/2*camera.GetAspectRatio()))*vertex.xyz.z;
				float yTest = tan(AngleToRadian(camera.GetFov()/2))*vertex.xyz.z;

				if(	vertex.xyz.x > -xTest && vertex.xyz.x < xTest &&
					vertex.xyz.y > -yTest && vertex.xyz.y < yTest &&
					vertex.xyz.z > camera.GetNearClipZ() && vertex.xyz.z < camera.GetFarClipZ()
				   ) {
					isInFrustum = true;
					break;
				}
			}


			if(isInFrustum) {
				VertexList* newVertices = new VertexList;

				std::vector<Vertex>::const_iterator it = vertexList.vertices.begin();
				std::vector<Vertex>::const_iterator itEnd = vertexList.vertices.end();
				for(; it != itEnd; it++) {
					const Vertex& vertex = *it;
					newVertices->vertices.push_back(vertex);
				}

				std::vector<int>::const_iterator indexIt = vertexList.indices.begin();
				std::vector<int>::const_iterator indexItEnd = vertexList.indices.end();
				for(; indexIt != indexItEnd; indexIt++) {
					newVertices->indices.push_back(*indexIt);
				}

				newVertices->pos = vertexList.pos;

				output.lists.push_back(newVertices);
			}

		}
	}


	const Matrix4 ProjectionMatrix = Matrix4(1,0,0,0,
											 0,1,0,0,
											 0,0,1,1,
											 0,0,0,0);

	void Projection(const VertexBuffer& vertexBuffer,const Camera& camera, OUTPUT VertexBuffer& output)
	{
		float aspectRatio = camera.GetAspectRatio();

		std::vector<VertexList*>::const_iterator bufferIt = vertexBuffer.lists.begin();
		std::vector<VertexList*>::const_iterator bufferItEnd = vertexBuffer.lists.end();
		for(; bufferIt != bufferItEnd; bufferIt++) {
			const VertexList& vertexList = **bufferIt;
			VertexList* newVertices = new VertexList;

			std::vector<Vertex>::const_iterator it = vertexList.vertices.begin();
			std::vector<Vertex>::const_iterator itEnd = vertexList.vertices.end();
			for(; it != itEnd; it++) {
				const Vertex vertex = *it;
				float z = vertex.xyz.z;

				Vector3 projectionVector;
				projectionVector.x = vertex.xyz.x / z;
				projectionVector.y = vertex.xyz.y*aspectRatio / z;
				projectionVector.z = z;

				Vertex projectionVertex;
				projectionVertex.xyz = projectionVector;
				for(int i = 0; i < 3; i++) {
					projectionVertex.color[i] = vertex.color[i];
				}
				projectionVertex.normal = vertex.normal;
				projectionVertex.textureCoord = vertex.textureCoord;

				newVertices->vertices.push_back(projectionVertex);
			}

			std::vector<int>::const_iterator indexIt = vertexList.indices.begin();
			std::vector<int>::const_iterator indexItEnd = vertexList.indices.end();
			for(; indexIt != indexItEnd; indexIt++) {
				newVertices->indices.push_back(*indexIt);
			}

			newVertices->pos = vertexList.pos;

			output.lists.push_back(newVertices);
		}
	}


	void ToScreen(const VertexBuffer& vertexBuffer, int width, int height, OUTPUT VertexBuffer& output)
	{
		std::vector<VertexList*>::const_iterator bufferIt = vertexBuffer.lists.begin();
		std::vector<VertexList*>::const_iterator bufferItEnd = vertexBuffer.lists.end();
		for(; bufferIt != bufferItEnd; bufferIt++) {
			const VertexList& vertexList = **bufferIt;
			VertexList* newVertices = new VertexList;

			std::vector<Vertex>::const_iterator it = vertexList.vertices.begin();
			std::vector<Vertex>::const_iterator itEnd = vertexList.vertices.end();
			for(; it != itEnd; it++) {
				const Vertex vertex = *it;

				Vector3 screenVector;
				screenVector.x = (vertex.xyz.x + 1) * (0.5f * width - 0.5f);
				screenVector.y = (height - 1) - (vertex.xyz.y + 1)*(0.5f * height - 0.5f);

				Vertex screenVertex;
				screenVertex.xyz = screenVector;
				for(int i = 0; i < 3; i++) {
					screenVertex.color[i] = vertex.color[i];
				}
				screenVertex.normal = vertex.normal;
				screenVertex.textureCoord = vertex.textureCoord;

				newVertices->vertices.push_back(screenVertex);
			}

			std::vector<int>::const_iterator indexIt = vertexList.indices.begin();
			std::vector<int>::const_iterator indexItEnd = vertexList.indices.end();
			for(; indexIt != indexItEnd; indexIt++) {
				newVertices->indices.push_back(*indexIt);
			}

			newVertices->pos = vertexList.pos;

			output.lists.push_back(newVertices);

		}


	}


	void DrawVertexList(const VertexBuffer& vertexBuffer)
	{
		std::vector<VertexList*>::const_iterator bufferIt = vertexBuffer.lists.begin();
		std::vector<VertexList*>::const_iterator bufferItEnd = vertexBuffer.lists.end();
		for(; bufferIt != bufferItEnd; bufferIt++) {
			const VertexList& vertexList = **bufferIt;

			Graphic& graphic = Graphic::Instance();
			int indexCount = (int)vertexList.indices.size();
			for(int i = 0; ((i + 1) * 3) <= indexCount; i++) {

				int idx0 = vertexList.indices[i * 3];
				int idx1 = vertexList.indices[(i * 3) + 1];
				int idx2 = vertexList.indices[(i * 3) + 2];

				Vector2 pos0(vertexList.vertices[idx0].xyz.x, vertexList.vertices[idx0].xyz.y);
				Vector2 pos1(vertexList.vertices[idx1].xyz.x, vertexList.vertices[idx1].xyz.y);
				Vector2 pos2(vertexList.vertices[idx2].xyz.x, vertexList.vertices[idx2].xyz.y);

				graphic.DrawLine(pos0, pos1, 0xFF0000FF);
				graphic.DrawLine(pos1, pos2, 0xFF0000FF);
				graphic.DrawLine(pos2, pos0, 0xFF0000FF);
			}
		}

	}


}


softbreeze_namespace_end



