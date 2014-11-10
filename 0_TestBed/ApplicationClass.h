/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/10
*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_
#pragma warning(disable:4251)

#include "ME\MyEngine.h"
#include "BoundingSphereManager.h"
#include "BoundingBoxManager.h"

#include <SFML\Graphics.hpp>
#include <chrono>

using namespace MyEngine;

class ApplicationClass
{
public: //This Application
	//Public for main to use
	static ApplicationClass* GetInstance( HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);//Singleton accessor 
	void ReleaseInstance();	//Singleton Destructor
	void Run (void); //Main Loop

protected://General
	bool m_bFPC;
	String m_sSelectedObject;
	bool m_bArcBall;
	
	BoundingSphereManager* m_pBSMngr;
	
	BoundingBoxManager* m_pBBMngr;

	void Update (void);
	void Display2X (void);
	void Display3X (void);
	void DisplayDX (void);
	void Idle (void);
	void Reshape(int a_nWidth, int a_nHeight);
	void InitAppSystem(void);
	void InitAppInternalVariables(void);
	void InitAppVariables(void);
	void ProcessKeyboard(void);
	void ProcessMouse(void);
	void CreateAxisFrame(void);
	void ProcessJoystick(void);


private://General
	static ApplicationClass* m_pInstance;
	SystemClass* m_pSystem;
	GLSystemClass* m_pGLSystem;
	WindowClass* m_pWindow;
	ModelManagerClass* m_pModelManager;
	LightManagerClass* m_pLightMngr;
	MaterialManagerClass* pMatMngr;

	CameraClass* m_pCamera0;
	bool m_bForceNewConfig;
	
	void Init( HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);
	void Release(void);
	void ArcBall(float a_fSensitivity = 0.1f);
	void CameraRotation(float a_fSpeed = 0.001f);
	void ReadConfig(void);
	void WriteConfig(void);

	ApplicationClass();
	ApplicationClass(ApplicationClass const& input);
	ApplicationClass& operator=(ApplicationClass const& input);
	~ApplicationClass();
};
#endif //__APPLICATION_H_