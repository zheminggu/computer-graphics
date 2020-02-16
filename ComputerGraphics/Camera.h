#pragma once
#ifndef CAMERA_H
#define CAMERA_H

class Vector3;
class Matrix4;
class ClippingPlane;

class Camera
{

public:
	Camera();
	~Camera();
	Vector3 GetLocalPosition() const;
	Vector3 GetUpVector() const;
	Vector3 GetPosition() const;
	Matrix4 GetMatView() const;
	Matrix4 GetMatPers() const;
	//change world position
	void SetPosition(Vector3& position);
	//change P ref
	void SetLookAt(Vector3& position);
	//change fov
	void SetFOV(float fov);
	//change aspect
	void SetAspect(float aspect);
	// set camera aspect input height and weight
	void SetAspect(float weight, float height);
	void LocalToWorld(Matrix4& m_localToWorld);// to do 
private: 
	void ComputeMatView(void);
	void ComputeMatPers(void);

private:
	Vector3* localPosition;
	Vector3* worldPosition;
	Vector3* upVector;
	Vector3* P_ref;

	//Vector3* N;
	//Vector3* U;
	//Vector3* V;

	Matrix4* M_view;
	Matrix4* M_pers;

	float FOV;
	float aspect;
	ClippingPlane* nearClippingPlane;
	ClippingPlane* farClippingPlane;


};



#endif // 
