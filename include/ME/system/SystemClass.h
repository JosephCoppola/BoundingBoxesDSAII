/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/05
*/
#ifndef __SYSTEMCLASS_H_
#define __SYSTEMCLASS_H_

#include "ME\system\MeDefinitions.h"

// Include standard headers
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <assert.h>
#include <vector>

// Include GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>

#include "ME\System\FolderClass.h"

namespace MyEngine
{

typedef std::string String;
typedef glm::vec2 vector2;
typedef glm::vec3 vector3;
typedef glm::vec4 vector4;
typedef glm::mat4 matrix4;

#define MEWHITE vector3(1.0f, 1.0f, 1.0f)
#define MERED vector3(1.0f, 0.0f, 0.0f)
#define MEGREEN vector3(0.0f, 1.0f, 0.0f)
#define MEBLUE vector3(0.0f, 0.0f, 1.0f)
#define MEBLACK vector3(0.0f, 0.0f, 0.0f)
#define MEYELLOW vector3(1.0f, 1.0f, 0.0f)
#define MEMAGENTA vector3(1.0f, 0.0f, 1.0f)
#define MEDEFAULT vector3(-1.0f, -1.0f, -1.0f)

//System Class
class MyEngineDLL SystemClass
{
public:
	static SystemClass* GetInstance(); // Singleton accessor
	void ReleaseInstance(void); //Singleton Release

	// Application Name Property
	String GetAppName(void);
	__declspec(property(get = GetAppName)) String ApplicationName;

	// Window Borderless Property
	__declspec(property(get = IsWindowBorderless, put = SetWindowBorderless)) bool WindowBorderless;
	void SetWindowBorderless(bool bBorderless = true);
	bool IsWindowBorderless(void);

	// Window Fullscreen Property
	__declspec(property(get = IsWindowFullscreen, put = SetWindowFullscreen)) bool WindowFullscreen;
	void SetWindowFullscreen(bool bFullscreen = true);
	bool IsWindowFullscreen(void);
	
	// Window Width Property
	__declspec(property(get = GetWindowWidth, put = SetWindowWidth)) int WindowWidth;
	void SetWindowWidth(int nWidth);
	int GetWindowWidth(void);

	// Window Height Property
	__declspec(property(get = GetWindowHeight, put = SetWindowHeight)) int WindowHeight;
	void SetWindowHeight(int nHeight);
	int GetWindowHeight(void);

	// WindowX Property
	__declspec(property(get = GetWindowX, put = SetWindowX)) int WindowX;
	void SetWindowX(int nX);
	int GetWindowX(void);

	// WindowY Property
	__declspec(property(get = GetWindowY, put = SetWindowY)) int WindowY;
	void SetWindowY(int nY);
	int GetWindowY(void);
	
	// Window Name Property
	__declspec(property(get = GetWindowName, put = SetWindowName)) String WindowName;
	void SetWindowName(String sWindowName);
	String GetWindowName(void);

	// WindowX Property
	__declspec(property(get = GetFPS)) int FPS;
	int GetFPS(void);

	void UpdateTime(void);//Updates the current time
	void StartClock(void);//Starts a time count
	float StopClock(void);//Stops the time count and returns the number of seconds passed
	float LapClock(void);//Checks the time difference between startclock and current call

	FolderClass* m_pFolder;
	MEOptions m_RenderingContext;

private:
	SystemClass(void); // Constructor
	SystemClass(SystemClass const& other); //Copy Constructor
	SystemClass& operator=(SystemClass const& other); // Copy Assignment Operator
	~SystemClass(void); // Destructor

	void Release(void); // Release Memory
	void Init(void); // Initialize variables
	
	static SystemClass* m_pInstance; // Singleton

	bool m_bWindowFullscreen; // Window Fullscreen
	bool m_bWindowBorderless; // Window Borderless

	int m_nWindowWidth; // Window width
	int m_nWindowHeight; // Window height
	int m_nWindowX; // Window Position X
	int m_nWindowY; // Window Position Y
	String m_sWindowName; // Window Name

	String m_sAppName;

	DWORD m_dTimerStart; //Start time of the program
	DWORD m_dStartingTime; //Start time of the program
	DWORD m_dLastFPS; //Last time the time was called
	int m_nFPS; //Frames per Second
	int m_nFrames; //Frames Passed
};

}
#include "ME\system\WindowClass.h"
#include "ME\System\GLSystemClass.h"

#endif //__SYSTEMCLASS_H__