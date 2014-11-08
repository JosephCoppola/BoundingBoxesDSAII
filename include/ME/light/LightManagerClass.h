/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/05
*/
#ifndef __LIGHTMANAGERCLASS_H_
#define __LIGHTMANAGERCLASS_H_

#include "ME\light\LightClass.h"
#include <vector>
#include <assert.h>

namespace MyEngine
{

//System Class
class MyEngineDLL LightManagerClass
{
	int m_nLights; //Number of Lights
	std::vector<LightClass> m_vLight; //vector of lights
	float m_fAmbient;
public:
	static LightManagerClass* GetInstance(); // Singleton accessor
	void ReleaseInstance(void); //Singleton Release
	void AddLight(	vector3 a_vPosition = vector3(1,1,1),
					vector3 a_vColor = vector3(1,1,1),
					float a_vIntensity = 10.0f); //Adds a light to the vector
	LightClass GetLight(int a_nIndex = 1);

	void SetPosition(vector3 a_vPosition, int a_nLight = 1);
	vector3 GetPosition( int a_nLight = 1);

	void SetColor(vector3 a_vColor, int a_nLight = 1);
	vector3 GetColor(int a_nLight = 1);

	void SetIntensity(float a_fIntensity, int a_nLight = 1);
	float GetIntensity(int a_nLight = 1);

private:
	LightManagerClass(void); // Constructor
	LightManagerClass(LightManagerClass const& other); //Copy Constructor
	LightManagerClass& operator=(LightManagerClass const& other); // Copy Assignment Operator
	~LightManagerClass(void); // Destructor

	void Release(void); // Release Memory
	void Init(void); // Initialize variables
	
	static LightManagerClass* m_pInstance; // Singleton
};

}
#endif //__LIGHTMANAGERCLASS_H__