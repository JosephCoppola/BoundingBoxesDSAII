/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef __MATERIALCLASS_H_
#define __MATERIALCLASS_H_

#include "ME\system\SystemClass.h"
#include "ME\materials\TextureManagerClass.h"

namespace MyEngine
{

class MyEngineDLL MaterialClass
{
	String m_sName;
	GLuint m_nMapDiffuse;
	GLuint m_nMapNormal;
	String m_sMapDiffuse;
	String m_sMapNormal;
	GLuint m_nMapSpecular;
	String m_sMapSpecular;

	vector3 m_vKd;

	SystemClass* m_pSystem;
	TextureManagerClass* m_pTextureManager;
public:
	MaterialClass(String a_sName);
	MaterialClass(const MaterialClass& other);
	MaterialClass& operator=(const MaterialClass& other);
	~MaterialClass(void);
	
	void Release(void);

	void	SetName(String a_sName);
	String	GetName(void);
	__declspec(property(put = SetName, get = GetName)) String Name;

	void	SetDiffuseMapName(String a_sFileName);
	String	GetDiffuseMapName(void);
	__declspec(property(put = SetDiffuseMapName, get = GetDiffuseMapName)) String DiffuseMapName;

	void	SetNormalMapName(String a_sFileName);
	String	GetNormalMapName(void);
	__declspec(property(put = SetNormalMapName, get = GetNormalMapName)) String NormalMapName;

	void	SetSpecularMapName(String a_sFileName);
	String	GetSpecularMapName(void);
	__declspec(property(put = SetSpecularMapName, get = GetSpecularMapName)) String SpecularMapName;

	GLuint	GetDiffuseMap(void);
	__declspec(property(get = GetDiffuseMap)) GLuint DiffuseMap;

	GLuint	GetNormalMap(void);
	__declspec(property(get = GetNormalMap)) GLuint NormalMap;

	GLuint	GetSpecularMap(void);
	__declspec(property(get = GetSpecularMap)) GLuint SpecularMap;

	void	SetDiffuse(vector3 a_Kd);
	vector3	GetDiffuse(void);
	__declspec(property(put = SetDiffuse, get = GetDiffuse)) vector3 Kd;

	MEErrors LoadDiffuse(String a_sFileName);

	MEErrors LoadNormal(String a_sFileName);

	MEErrors LoadSpecular(String a_sFilename);

	MEErrors LoadMaps(void);
private:
	void Init(void);
};

}
#endif //_EMPTY_H
