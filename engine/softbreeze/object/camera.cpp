
#include "../math/vector3.h"
#include "camera.h"
//#include "Utilities.h"



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


