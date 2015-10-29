

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

	void	Pitch(float angle);		//����UVN��X����ת
	void	Yaw(float angle);		//����UVN��Y����ת
	void	Roll(float angle);		//����UVN��Z����ת

	Matrix4	MakeCameraMatrix();

private:
	Vector3 pos;

	Vector3 direction;//��λ��������ʾ��ע�ӵķ���

	Matrix4 uvn;

};

softbreeze_namespace_end

#endif