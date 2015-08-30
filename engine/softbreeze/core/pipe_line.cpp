
#include "../softbreeze.h"

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>

#include "../math/matrix4.h"

#include "../math/vector2.h"
#include "../math/vector3.h"
#include "../math/vector4.h"
#include "../object/vertex.h"
#include "../object/vertex_list.h"
#include "../core/graphic.h"

#include "pipe_line.h"

softbreeze_namespace_beg

namespace PipeLine
{


	const Matrix4 ProjectionMatrix = Matrix4(1,0,0,0,
											 0,1,0,0,
											 0,0,1,1,
											 0,0,0,0);

	void Projection(const VertexList& vertexList, OUTPUT VertexList& output)
	{
		std::vector<Vertex>::const_iterator it = vertexList.vertices.begin();
		std::vector<Vertex>::const_iterator itEnd = vertexList.vertices.end();
		for(; it != itEnd; it++) {
			const Vertex vertex = *it;
			float z = vertex.xyz.z;

			Vector3 projectionVector;
			projectionVector.x = vertex.xyz.x / z;
			projectionVector.y = vertex.xyz.y / z; //这样的投影是个方形，将来有了镜头后，可以设置镜头宽高比，之后用y乘以宽高比，计算出y的坐标
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


	void DrawVertexList(const VertexList& vertexList, UCHAR* video_buffer, int lpitch)
	{
		int indexCount = (int)vertexList.indices.size();
		for(int i = 0; ((i+1)*3) <= indexCount; i++) {

			/*Draw_Clip_Line(vertexList.vertices[i].xyz.x,
				vertexList.vertices[i].xyz.y,
				vertexList.vertices[i+1].xyz.x,
				vertexList.vertices[i+1].xyz.y,
				0xFF0000FF,
				video_buffer, lpitch);

			Draw_Clip_Line(vertexList.vertices[i+1].xyz.x,
				vertexList.vertices[i+1].xyz.y,
				vertexList.vertices[i+2].xyz.x,
				vertexList.vertices[i+2].xyz.y,
				0xFF0000FF,
				video_buffer, lpitch);

			Draw_Clip_Line(vertexList.vertices[i+2].xyz.x,
				vertexList.vertices[i+2].xyz.y,
				vertexList.vertices[i].xyz.x,
				vertexList.vertices[i].xyz.y,
				0xFF0000FF,
				video_buffer, lpitch);*/

		}

	}


}


softbreeze_namespace_end



