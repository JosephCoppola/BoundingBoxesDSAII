/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/05
*/
#ifndef __SHADERMANAGERCLASS_H_
#define __SHADERMANAGERCLASS_H_

#include "ME\system\ShaderClass.h"
#include <vector>
#include <assert.h>

namespace MyEngine
{

//System Class
class MyEngineDLL ShaderManagerClass
{
	int m_nShaders; //Number of Lights
	std::vector<ShaderClass> m_vShader; //vector of lights
public:
	static ShaderManagerClass* GetInstance(); // Singleton accessor
	void ReleaseInstance(void); //Singleton Release
	GLuint CompileShader(String a_sVertexShader, String a_sFragmentShader, String a_sName = "");
	GLuint GetShader(String a_sName);
private:
	ShaderManagerClass(void); // Constructor
	ShaderManagerClass(ShaderManagerClass const& other); //Copy Constructor
	ShaderManagerClass& operator=(ShaderManagerClass const& other); // Copy Assignment Operator
	~ShaderManagerClass(void); // Destructor

	void Release(void); // Release Memory
	void Init(void); // Initialize variables
	
	static ShaderManagerClass* m_pInstance; // Singleton
	int IdentifyShader(String a_sName);
};

}
#endif //__SHADERMANAGERCLASS_H__