/*--------------------------------------------------------------------------------------------------
	Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef __MATERIALMANAGERCLASS_H_
#define __MATERIALMANAGERCLASS_H_

#include "ME\system\SystemClass.h"
#include "ME\materials\MaterialClass.h"


namespace MyEngine
{

class MyEngineDLL MaterialManagerClass
{
public:
	SystemClass* m_pSystem;
	std::vector<MaterialClass*> m_vMaterial; //Materials Vector

	static MaterialManagerClass* GetInstance(); // Singleton Accessor
	void ReleaseInstance();	//Singleton Destructor

	int IdentifyMaterial(String a_sName); //Identifies the material, if found return its index -1 otherwise

	//returns the index number of the material if it created a new one, otherwise it returns the index
	int AddMaterial(String a_sName);
	int AddMaterial(MaterialClass input);

	int GetNumberOfMaterials(void); //Return the number of materials in the vector

	void ReloadMaps(void); //Tries to load all the textures for all of the materials

	MaterialClass GetMaterialCopy(String sName);

private:
	MaterialManagerClass(void); // Constructor
	MaterialManagerClass(MaterialManagerClass const& other); //Copy Constructor
	MaterialManagerClass& operator=(MaterialManagerClass const& other); // Copy Assignment Operator
	~MaterialManagerClass(void); // Destructor

	void Release(void); // Release Memory
	void Init(void); // Initialize variables
	
	static MaterialManagerClass* m_pInstance; // Singleton
};

}
#endif