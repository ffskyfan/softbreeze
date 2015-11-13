
#include "../softbreeze.h"
#include "../math/vector3.h"
#include "../math/matrix3.h"
#include "../math/matrix4.h"
#include "../math/utility.h"
#include "camera.h"
//#include "Utilities.h"


softbreeze_namespace_beg


Camera::Camera()
{
	direction = Vector3(0, 0, 1);

	uvn = Matrix4(	1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 0);

	aspectRatio = 1;
}


Camera::~Camera()
{

}


void Camera::SetPos(const Vector3& pos)
{
	this->pos = pos;
}




void Camera::Move(Vector3 offset)
{
	pos += offset;
}


namespace
{

	Matrix4 MakeRotationMatrixAlongVector(const Vector4& vec, float angle)
	{
		float radian = AngleToRadian(angle);
		float cs = cos(radian);
		float sn = sin(radian);

		float x = vec.x, y = vec.y, z = vec.z;

		Matrix4 matrix(	x*x*(1 - cs) + cs,		x*y*(1 - cs) - z*sn,	x*z*(1 - cs) + y*sn,	0,
						x*y*(1 - cs) + z*sn,	y*y*(1 - cs) + cs,		y*z*(1 - cs) - x*sn,	0,
						x*z*(1 - cs) - y*sn,	y*z*(1 - cs) + x*sn,	z*z*(1 - cs) + cs,		0,
						0,						0,						0,						1);

		return matrix;
	}

}




void Camera::Pitch(float angle)
{
	Vector4& u = uvn.data[0];
	Vector4& v = uvn.data[1];
	Vector4& n = uvn.data[2];

	Matrix4 matrix = MakeRotationMatrixAlongVector(u, angle);

	v = v*matrix;
	v.Normalize();
	n = n*matrix;
	n.Normalize();

	direction.x=n.x;
	direction.y=n.y;
	direction.z=n.z;
}

void Camera::Yaw(float angle)
{
	Vector4& u = uvn.data[0];
	Vector4& v = uvn.data[1];
	Vector4& n = uvn.data[2];

	Matrix4 matrix = MakeRotationMatrixAlongVector(v, angle);

	u = u*matrix;
	u.Normalize();
	n = n*matrix;
	n.Normalize();

	direction.x=n.x;
	direction.y=n.y;
	direction.z=n.z;
}

void Camera::Roll(float angle)
{
	Vector4& u = uvn.data[0];
	Vector4& v = uvn.data[1];
	Vector4& n = uvn.data[2];

	Matrix4 matrix = MakeRotationMatrixAlongVector(n, angle);

	u = u*matrix;
	u.Normalize();
	v = v*matrix;
	v.Normalize();
}


Matrix4	Camera::MakeCameraMatrix() const
{
	const Vector4& u = uvn.data[0];
	const Vector4& v = uvn.data[1];
	const Vector4& n = uvn.data[2];
	Vector4 cameraPos(pos.x, pos.y, pos.z, 0);

	Matrix4 matrix( u.x,				v.x,				n.x,				-cameraPos.Dot(u),
					u.y,				v.y,				n.y,				-cameraPos.Dot(v),
					u.z,				v.z,				n.z,				-cameraPos.Dot(n),
					0,					0,					0,								1);

	return matrix;
}



softbreeze_namespace_end