/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/07
*/
#ifndef __LINEMANAGERCLASS_H_
#define __LINEMANAGERCLASS_H_

#include "ME\mesh\debug\LineClass.h"

namespace MyEngine
{

//System Class
class MyEngineDLL LineManagerClass
{
	LineClass* m_pLine;
	int m_nLines;
	std::vector<vector3> m_v3Start;
	std::vector<vector3> m_v3End;
	std::vector<vector3> m_v3Color;

public:
	static LineManagerClass* GetInstance(); // Singleton accessor
	void ReleaseInstance(void); //Singleton Release

	void ClearLines(void);
	void RenderLines(void);
	void AddLine(vector3 a_v3Start, vector3 a_v3End, vector3 a_v3Color = vector3( 0.0f, 1.0f, 0.0f));
	void CompileOpenGL3X(void);

private:
	LineManagerClass(void); // Constructor
	LineManagerClass(LineManagerClass const& other); //Copy Constructor
	LineManagerClass& operator=(LineManagerClass const& other); // Copy Assignment Operator
	~LineManagerClass(void); // Destructor

	void Release(void); // Release Memory
	void Init(void); // Initialize variables
	
	static LineManagerClass* m_pInstance; // Singleton
};

}
#endif //__LINEMANAGERCLASS_H__