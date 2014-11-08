/*
	Adapted from http://www.swiftless.com/tutorials/opengl4/1-opengl-window.html
	into a class
	Date: 2014/05
*/
#ifndef __GLSYSTEMCLASS_H_
#define __GLSYSTEMCLASS_H_

#include "ME\system\WindowClass.h"

#include <GL\glew.h>
#include <GL\wglew.h>

#include "ME\system\MeDefinitions.h"

namespace MyEngine
{

class MyEngineDLL GLSystemClass
{
public:
	//--Methods

	/*
	HRESULT InitGLDevice(HWND g_hWnd);
		Initializes the OpenGL Device Context
	Arguments:
		HWND g_hWnd -> Window Handler
	*/
	HRESULT InitGLDevice(HWND g_hWnd);

	/*
	int DrawOldGLScene(GLvoid);
		Draws a demo scene using OpenGL 2.1 Context, used only if
		failed to initialize 3.x+ in the system
	*/
	int DrawOldGLScene(GLvoid);
	
	/*
	static GLSystemClass* GetInstance(void);
		Singleton Accessor, returns the singleton of this class
	*/
	static GLSystemClass* GetInstance(void);

	
	/*
	void ReleaseInstance(void);
		Releases the singleton of this class
	*/
	void ReleaseInstance(void);
	
	/*
	HDC GetDeviceContext(GLvoid);
		Returns the OpenGL rendering context device
	*/
	HDC GetDeviceContext(GLvoid);

	/*
	float GetGLVersion(void);
		Returns the OpenGL Version the program is running
	*/
	float GetGLVersion(void);

	/*
	bool IsNewOpenGLRunning(void);
		Returns whether OpenGL3.x or newer is running
	*/
	bool IsNewOpenGLRunning(void);

	/*
	void ForceOldOpenGL(bool input = true);
		Forces OpenGL 2.1 to be used for the rendering context
	*/
	void ForceOldOpenGL(bool input = true);

	/*
	void GLSwapBuffers(void);
		SwapsvOpenGL buffer
	*/
	void GLSwapBuffers(void);

private:
	//--Members
	HDC   m_hDC;		// Private GDI Device Context
	HGLRC m_hRC;		// Permanent Rendering Context
	float m_fGLVersion; // OpenGL version
	bool m_bForceOldGL;	// Forces OpenGL 2.1 to be initialized

	//--Methods
	GLSystemClass(void); // Constructor
	GLSystemClass(GLSystemClass const& other); //Copy Constructor
	GLSystemClass& operator=(GLSystemClass const& other); // Copy Assignment Operator
	~GLSystemClass(void); // Destructor

	void Release(void); // Release Memory
	void Init(void); // Initialize variables
	
	static GLSystemClass* m_pInstance; // Singleton
};

}

#include "ShaderCompiler.h"

#endif /*__GLSYSTEMCLASS_H__*/