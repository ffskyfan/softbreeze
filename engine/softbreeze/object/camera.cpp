
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

	Matrix3 MakeRotationMatrixAlongVector(const Vector3& vec, float angle)
	{
		float radian = AngleToRadian(angle);
		float cs = cos(radian);
		float sn = sin(radian);

		float x = vec.x, y = vec.y, z = vec.z;

		Matrix3 matrix(	x*x*(1 - cs) + sn,		x*y*(1 - cs) + x*sn,	x*z*(1 - cs) - y*sn,
						x*y*(1 - cs) - z*sn,	y*y*(1 - cs) + cs,		y*z*(1 - cs) + x*sn,
						x*z*(1 - cs) - y*sn,	y*z*(1 - cs) - x*sn,	z*z*(1 - cs) + cs);

		return matrix;
	}

}



void Camera::Roll(float angle)
{
	float cs=cos(AngleToRadian(angle));  
    float sn=sin(AngleToRadian(angle));  

    Vector3 t(u);  
    Vector3 s(v);  

    u.x() = cs*t.x()-sn*s.x();  
    u.y() = cs*t.y()-sn*s.y();  
    u.z() = cs*t.z()-sn*s.z();  
  
    v.x() = sn*t.x()+cs*s.x();  
    v.y() = sn*t.y()+cs*s.y();  
    v.z() = sn*t.z()+cs*s.z();  

}

void Camera::Pitch(float angle)
{
	float cs = cos(angle*3.14159265 / 180);
	float sn = sin(angle*3.14159265 / 180);
	Vector3d t(v);
	Vector3d s(n);

	v.x() = cs*t.x() - sn*s.x();
	v.y() = cs*t.y() - sn*s.y();
	v.z() = cs*t.z() - sn*s.z();

	n.x() = sn*t.x() + cs*s.x();
	n.y() = sn*t.y() + cs*s.y();
	n.z() = sn*t.z() + cs*s.z();


}

void Camera::Yaw(float angle)
{
	float cs = cos(angle*3.14159265 / 180);
	float sn = sin(angle*3.14159265 / 180);
	Vector3d t(n);
	Vector3d s(u);

	n.x() = cs*t.x() - sn*s.x();
	n.y() = cs*t.y() - sn*s.y();
	n.z() = cs*t.z() - sn*s.z();

	u.x() = sn*t.x() + cs*s.x();
	u.y() = sn*t.y() + cs*s.y();
	u.z() = sn*t.z() + cs*s.z();


}





softbreeze_namespace_end