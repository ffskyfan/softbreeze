
#include <time.h>

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>

#include <softbreeze/softbreeze.h>
#include <softbreeze/core/graphic.h>
#include <softbreeze/math/vector2.h>
#include <softbreeze/math/vector3.h>
#include <softbreeze/math/matrix4.h>
#include <softbreeze/math/utility.h>
#include <softbreeze/object/vertex.h>
#include <softbreeze/object/vertex_list.h>
#include <softbreeze/object/mesh.h>
#include <softbreeze/object/camera.h>
#include <softbreeze/core/pipe_line.h>

#include "game.h"

breeze::Mesh		mesh;
breeze::VertexList	vertices;
breeze::Vector3		pos;
breeze::Matrix4		matrix = breeze::matrix4_zero;
breeze::Camera		camera;
float				angle;

Game::Game()
{
}

Game::~Game()
{
}


int Game::Init(HWND hWnd)
{
	breeze::Graphic& graphic = breeze::Graphic::Instance();
	HRESULT result = graphic.Init(hWnd);


	breeze::Vertex vertex1;
	vertex1.xyz.x = 0;
	vertex1.xyz.y = 0;
	vertex1.xyz.z = 500;

	breeze::Vertex vertex2;
	vertex2.xyz.x = 90;
	vertex2.xyz.y = 0;
	vertex2.xyz.z = 500;

	breeze::Vertex vertex3;
	vertex3.xyz.x = 45;
	vertex3.xyz.y = 90;
	vertex3.xyz.z = 500;

	vertices.vertices.push_back(vertex1);
	vertices.vertices.push_back(vertex2);
	vertices.vertices.push_back(vertex3);

	for(int j = 0; j<3; j++) {
		vertices.indices.push_back(j);
	}

	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	breeze::Vector3 cameraPos(0, 0, 0);
	camera.SetPos(cameraPos); 

	return result;
}

void Game::Shutdown()
{
	breeze::Graphic& graphic = breeze::Graphic::Instance();
	graphic.Cleanup();
}


void Game::Main()
{
	breeze::Graphic& graphic = breeze::Graphic::Instance();
	graphic.ClearCanvas(0x00000000);

	breeze::BuildXYZRotationMatrix4(angle, 0, 0,  matrix);

	// rotate polygon slowly
	//if(++angle >= 360.0) angle = 0;

	//move ploygon slowly
	if(++pos.z > 100.0f) pos.z = 0;

	for(int i = 0; i < 10000000; i++) {
		int a = i;
	}

	breeze::VertexList TransformVertices;
	breeze::PipeLine::Transform(vertices, matrix, TransformVertices);

	breeze::VertexList WorldVertices;
	breeze::PipeLine::ToWorld(TransformVertices, pos, WorldVertices);


	breeze::VertexList projectionVertices;
	breeze::PipeLine::Projection(WorldVertices, projectionVertices);

	breeze::VertexList ScreenVertices;
	breeze::PipeLine::ToScreen(projectionVertices, graphic.GetWidth(), graphic.GetHeight(), ScreenVertices);

	// render the polygon list
	breeze::PipeLine::DrawVertexList(ScreenVertices);



	graphic.Render();
}

