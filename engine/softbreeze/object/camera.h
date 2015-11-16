

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


	void					SetPos(const Vector3& pos);

	inline void				SetAspectRatio(float ratio) { if(ratio > 0) { aspectRatio = ratio; } }
	inline float			GetAspectRatio() const  { return aspectRatio;  }


	inline const Vector3&	GetDirection() const  { return direction;  }

	void					Move(Vector3 offset);

	void					Pitch(float angle);		//����UVN��X����ת
	void					Yaw(float angle);		//����UVN��Y����ת
	void					Roll(float angle);		//����UVN��Z����ת

	Matrix4					MakeCameraMatrix() const;

private:
	Vector3 pos;

	Vector3 direction;//��λ��������ʾ��ע�ӵķ���

	Matrix4 uvn;

	float	aspectRatio;//��߱�
};

softbreeze_namespace_end

#endif