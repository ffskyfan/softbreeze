
#include "../softbreeze.h"
#include "../math/vector3.h"
#include "camera.h"
//#include "Utilities.h"


softbreeze_namespace_beg


void Camera::SetMoveSpeed(float speed)
{
	moveSpeed = speed;
}

void Camera::Move(Vector3 offset)
{
	pos += offset;
}


void Camera::Rotate(Vector3 offset)
{
	angle += offset;
}




softbreeze_namespace_end