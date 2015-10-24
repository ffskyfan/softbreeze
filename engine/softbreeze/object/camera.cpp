
#include "../softbreeze.h"
#include "../math/vector3.h"
#include "camera.h"
//#include "Utilities.h"


softbreeze_namespace_beg


Camera::Camera()
{

}


Camera::~Camera()
{

}

void Camera::Init(const Vector3& pos, const Vector3& direction)
{

}

void Camera::SetPos(const Vector3& pos)
{

}


void Camera::LookAt(const Vector3& direction)
{

}


void Camera::Move(Vector3 offset)
{
	pos += offset;
}


void Camera::Rotate(Vector3 offset)
{
}




softbreeze_namespace_end