

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
	inline const Vector3&	GetPos() const { return pos; }

	inline void				SetFov(float _fov) { fov = _fov; }
	inline float			GetFov() const { return fov; }

	inline void				SetNearClipZ(float _nearClipZ) { nearClipZ = _nearClipZ; }
	inline float			GetNearClipZ() const { return nearClipZ; }

	inline void				SetFarClipZ(float _farClipZ) { farClipZ = _farClipZ; }
	inline float			GetFarClipZ() const { return farClipZ; }

	inline void				SetAspectRatio(float ratio) { if(ratio > 0) { aspectRatio = ratio; } }
	inline float			GetAspectRatio() const  { return aspectRatio;  }


	inline const Vector3&	GetDirection() const  { return direction;  }

	void					Move(Vector3 offset);

	void					Pitch(float angle);		//沿着UVN的X轴旋转
	void					Yaw(float angle);		//沿着UVN的Y轴旋转
	void					Roll(float angle);		//沿着UVN的Z轴旋转

	Matrix4					MakeCameraMatrix() const;

private:
	Vector3 pos;

	Vector3 direction;//单位向量，表示所注视的方向

	Matrix4 uvn;

	float	aspectRatio;	//宽高比
	float	fov;			//纵方向视角

	float	nearClipZ;		//近裁剪面
	float	farClipZ;		//远裁剪面
};

softbreeze_namespace_end

#endif