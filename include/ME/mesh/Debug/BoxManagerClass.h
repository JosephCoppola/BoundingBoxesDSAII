/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/07
*/
#ifndef __BoxManagerClass_H_
#define __BoxManagerClass_H_

#include "ME\mesh\Physics\AABBClass.h"

namespace MyEngine
{

//System Class
class MyEngineDLL BoxManagerClass
{
	AABBClass* m_pAABB;
	int m_nBoxes;
	std::vector<vector3> m_vMin;
	std::vector<vector3> m_vMax;
	std::vector<vector3> m_vColor;
	std::vector<matrix4> m_mToWorld;

public:
	static BoxManagerClass* GetInstance(); // Singleton accessor
	void ReleaseInstance(void); //Singleton Release

	void ClearBoxes(void);
	void RenderBoxes(void);
	void AddBox(AABBClass* AABBClass, vector3 a_vColor = vector3(1.0f,1.0f,1.0f));
	void AddBox(vector3 a_vMin, vector3 a_vMax, vector3 a_vColor = vector3(1.0f,1.0f,1.0f));
	void AddBox(vector3 a_vMin, vector3 a_vMax, matrix4 a_mToWorld, vector3 a_vColor = vector3(1.0f,1.0f,1.0f));
	void CompileOpenGL3X(void);

private:
	BoxManagerClass(void); // Constructor
	BoxManagerClass(BoxManagerClass const& other); //Copy Constructor
	BoxManagerClass& operator=(BoxManagerClass const& other); // Copy Assignment Operator
	~BoxManagerClass(void); // Destructor

	void Release(void); // Release Memory
	void Init(void); // Initialize variables
	
	static BoxManagerClass* m_pInstance; // Singleton
};

}
#endif //__BoxManagerClass_H__