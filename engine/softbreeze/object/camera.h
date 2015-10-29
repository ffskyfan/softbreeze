

#ifndef SOFTBREEZE_CAMERA_H
#define SOFTBREEZE_CAMERA_H


softbreeze_namespace_beg

class Vector3;
class Matrix4;

class Camera
{
public:
	Camera();
	~Camera();


	void	SetPos(const Vector3& pos);

	void	Move(Vector3 offset);

	void	Pitch(float angle);		//沿着UVN的X轴旋转
	void	Yaw(float angle);		//沿着UVN的Y轴旋转
	void	Roll(float angle);		//沿着UVN的Z轴旋转

	Matrix4	MakeCameraMatrix();

private:
	Vector3 pos;

	Vector3 direction;//单位向量，表示所注视的方向

	Matrix4 uvn;

};

softbreeze_namespace_end

#endif