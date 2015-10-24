
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
#include "../core/graphic.h"

#include "pipe_line.h"

softbreeze_namespace_beg

namespace PipeLine
{

	void Mat_Mul_VECTOR4D_4X3(const Vector3&  va,
		const Matrix4& mb,
		Vector3&  vprod)
	{
		// this function multiplies a VECTOR4D against a 
		// 4x3 matrix - ma*mb and stores the result in mprod
		// the function assumes that the last column of
		// mb is [0 0 0 1]t , thus w just gets replicated
		// from the vector [x y z w]

		for(int col = 0; col < 3; col++) {
			// compute dot product from row of ma 
			// and column of mb
			float sum = 0; // used to hold result

			for(int row = 0; row < 4; row++) {
				// add in next product pair
				sum += (va[row] * mb[row][col]);
			} // end for index

			// insert resulting col element
			vprod[col] = sum;

		} // end for col

		// copy back w element
		//vprod[3] = va[3];

	} // end Mat_Mul_VECTOR4D_4X3

	void Transform(const VertexList& vertexList,const Matrix4& matrix, OUTPUT VertexList& output)
	{
		std::vector<Vertex>::const_iterator it = vertexList.vertices.begin();
		std::vector<Vertex>::const_iterator itEnd = vertexList.vertices.end();
		for(; it != itEnd; it++) {
			const Vertex& vertex = *it;

			Vertex newVertex = vertex;
			newVertex.xyz = vertex.xyz*matrix;

			output.vertices.push_back(newVertex);
		}

		std::vector<int>::const_iterator indexIt = vertexList.indices.begin();
		std::vector<int>::const_iterator indexItEnd = vertexList.indices.end();
		for(; indexIt != indexItEnd; indexIt++) {
			output.indices.push_back(*indexIt);
		}
	}



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


	void DrawVertexList(const VertexList& vertexList)
	{
		Graphic& graphic = Graphic::Instance();
		int indexCount = (int)vertexList.indices.size();
		for(int i = 0; ((i+1)*3) <= indexCount; i++) {

			Vector2 pos0( vertexList.vertices[i].xyz.x, vertexList.vertices[i].xyz.y);
			Vector2 pos1( vertexList.vertices[i+1].xyz.x, vertexList.vertices[i+1].xyz.y);
			Vector2 pos2( vertexList.vertices[i+2].xyz.x, vertexList.vertices[i+2].xyz.y);

			graphic.DrawLine(pos0,pos1,0xFF0000FF);
			graphic.DrawLine(pos1,pos2,0xFF0000FF);
			graphic.DrawLine(pos2,pos0,0xFF0000FF);
		}

	}


}


softbreeze_namespace_end



