/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/05
*/
#ifndef __LIGHTCLASS_H_
#define __LIGHTCLASS_H_

#include "ME\system\SystemClass.h"

namespace MyEngine
{

class MyEngineDLL LightClass
{
	vector3 m_vPosition;
	vector3 m_vColor;
	float m_fIntensity;
public:
	LightClass(void);
	LightClass(const LightClass& other);
	LightClass& operator=(const LightClass& other);
	~LightClass(void);
	
	void Swap(LightClass& other);

	void SetPosition(vector3 a_vPosition);
	vector3 GetPosition(void);
	__declspec(property(put = SetPosition, get = GetPosition)) vector3 Position;

	void SetColor(vector3 a_vColor);
	vector3 GetColor(void);
	__declspec(property(put = SetColor, get = GetColor)) vector3 Color;

	void SetIntensity(float a_fIntensity);
	float GetIntensity(void);
	__declspec(property(put = SetIntensity, get = GetIntensity)) float Intensity;

protected:
	void Init(void);
	void Release(void);
};

EXPIMP_TEMPLATE template class MyEngineDLL std::vector<LightClass>;
EXPIMP_TEMPLATE template class MyEngineDLL std::vector<LightClass*>;

}
#endif //__LIGHT_H__