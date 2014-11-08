/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef __CAMERACLASS_H_
#define __CAMERACLASS_H_

#include "ME\system\SystemClass.h"

namespace MyEngine
{

class MyEngineDLL CameraClass
{
public:
	static CameraClass* GetInstance(); // Singleton Accessor
	void ReleaseInstance(void); //Singleton Release

	//Rotate
	void Rotate(float a_fAngX, float a_fAngY);

	//Translate
	void MoveSideways(float a_fDistance = 0.1f);
	void MoveVertical(float a_fDistance = 0.1f);
	void MoveForward(float a_fDistance = 0.1f);
	
	//Projection
	void CalculateProjection();
	void SetProjection(matrix4 a_mProjection);
	matrix4 GetProjection();
	__declspec(property(put = SetProjection, get = GetProjection)) matrix4 Projection;

	//View
	void SetPosition(vector3 a_Position);
	void SetDirection(vector3 a_vDirection);
	void SetUp(vector3 a_vDirection);
	void CalculateView();
	void SetView(matrix4 a_mView);
	matrix4 GetView(void);
	__declspec(property(put = SetView, get = GetView)) matrix4 View;
	vector3 GetPosition(void);
	vector3 GetViewVector(void);
	vector3 GetUpVector(void);

	//MVP
	matrix4 GetMVP(matrix4 a_mModel);
	matrix4 GetMVP();
	__declspec(property(get = GetMVP)) matrix4 VMP;

	void SetView(vector3 a_Target);
	float GetFieldOfView(void);
	float GetNear(void);
	float GetFar(void);

private:
	static CameraClass* m_pInstance;//Singleton
	SystemClass* m_pSystem;

	matrix4 m_mProjection; //Projection
	matrix4 m_mView; //View
	matrix4 m_mMVP; //MVP

	vector3 m_vPosition; //CameraPosition
	vector3 m_vForward; //Camera view vector
	vector3 m_vUp; //Camera up vector

	float m_fFieldOfView;
	float m_fAspectRatio;
	float m_fNear;
	float m_fFar;

	CameraClass(void); // Constructor
	CameraClass(CameraClass const& other); //Copy Constructor
	CameraClass& operator=(CameraClass const& other); // Copy Assignment Operator
	~CameraClass(void); //Destructor

	void Release(void);// Releases the memory
	void Init(void); //Init the values
};

}
#endif //_CAMERA_H