

#ifndef SOFTBREEZE_CAMERA_H
#define SOFTBREEZE_CAMERA_H


softbreeze_namespace_beg

class Vector3;

class Camera
{
public:
	Camera();
	~Camera();

	void Init(const Vector3& pos, const Vector3& direction);

	void SetPos(const Vector3& pos);
	void LookAt(const Vector3& direction);

	void Move(Vector3 offset);
	void Rotate(Vector3 offset);

private:
	Vector3 pos;

	Vector3 look;//单位向量，表示所注视的方向


};

softbreeze_namespace_end

#endif