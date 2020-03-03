#include "Camera.h"


#include <iostream>
#include <cmath>
#include "Debug.h"
#include "Math.h"


Camera::Camera()
{
	//set these vector need change mat view
	localPosition =Vector3(0, 0, 10);
	worldPosition = Vector3(localPosition);
	upVector = Vector3(0, 1, 0);
	P_ref = Vector3(0, 0, 0);

	//set these variables need change mat perspective
	FOV = PI / 2;
	//aspect = 9 / 16;
	//aspect = 1 / 1;
	aspect = 640./480.;
	nearClippingPlane = ClippingPlane(1.f);
	farClippingPlane = ClippingPlane(1000.f);

	ComputeMatView();
	ComputeMatPers();

	//testing
	//std::cout << "init camera" << std::endl;
	//std::cout <<"Vector: "<< ObjectName(N) << std::endl;
	//N->Print();
	//std::cout << "Vector: "<<ObjectName(U) << std::endl;
	//U->Print();
	//std::cout << "Vector: "<<ObjectName(V) << std::endl;
	//V->Print();
	//std::cout << "Matrix: " << ObjectName(M_view)<< std::endl;
	//M_view->Print();
}

Camera::~Camera(){
	//delete localPosition;
	//delete upVector;
}

Vector3 Camera::GetLocalPosition() const
{
	return localPosition;
}

Vector3 Camera::GetUpVector() const
{
	return upVector;
}

Vector3 Camera::GetPosition() const
{
	return worldPosition;
}

Matrix4 Camera::GetMatView() const
{
	return M_view;
}

Matrix4 Camera::GetMatPers() const
{
	return M_pers;
}

void Camera::SetPosition(Vector3& position)
{
	worldPosition = Vector3(position);
	ComputeMatView();
}

void Camera::SetFOV(float fov)
{
	this->FOV = fov;
	ComputeMatPers();
}

void Camera::SetLookAt(Vector3& position)
{
	P_ref = Vector3(position);
	ComputeMatView();
}

void Camera::SetAspect(float aspect)
{
	this->aspect = aspect;
	ComputeMatPers();
}

void Camera::SetAspect(float weight, float height)
{
	this->aspect = weight / height;
	ComputeMatPers();
}

//to do 
void Camera::LocalToWorld(Matrix4& m_localToWorld)
{
	worldPosition = Vector3(localPosition);
}


void Camera::ComputeMatView(void)
{
	N = Vector3(P_ref - worldPosition);
	N.Normalize();
	U = Vector3(Vector3::Cross(N, upVector));
	U.Normalize();
	V = Vector3(Vector3::Cross(U, N));
	V.Normalize();
	Matrix4 temp_R = Matrix4(U.GetX(), U.GetY(), U.GetZ(), 0,
		V.GetX(), V.GetY(), V.GetZ(), 0,
		N.GetX(), N.GetY(), N.GetZ(), 0,
		0, 0, 0, 1);
	Matrix4 temp_T = Matrix4(1, 0, 0, -worldPosition.GetX(),
		0, 1, 0, -worldPosition.GetY(),
		0, 0, 1, -worldPosition.GetZ(),
		0, 0, 0, 1);

	M_view = Matrix4(temp_R * temp_T);

	//std::cout << "On Mat view change" << std::endl;
	//M_view->Print();
}

void Camera::ComputeMatPers(void)
{

	float d = nearClippingPlane.GetDistance();
	float f = farClippingPlane.GetDistance();
	float r = 1 / std::tan(this->FOV/2);
	M_pers = Matrix4(	r/aspect, 0, 0, 0,
							0, r, 0, 0,
							0, 0, -(f+d) / (f - d), -2*d * f / (f - d),
							0, 0, 1, 0);

	//std::cout << "On Mat pers change" << std::endl;
	//M_pers->Print();
}
