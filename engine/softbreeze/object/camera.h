

#ifndef SOFTBREEZE_CAMERA_H
#define SOFTBREEZE_CAMERA_H


softbreeze_namespace_beg

class Vector3;

class Camera
{
public:
	Vector3 pos;
	Vector3 angle;
	
	float moveSpeed;
	float rotateSpeed;


public:

	void SetMoveSpeed(float speed);
	void SetRotateSpeed();

	void Move(Vector3 offset);
	void Rotate(Vector3 offset);


};

softbreeze_namespace_end

#endif