/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef __TEXTUREMANAGERCLASS_H_
#define __TEXTUREMANAGERCLASS_H_

#include "ME\materials\TextureClass.h"
#include <vector>

namespace MyEngine
{

class MyEngineDLL TextureManagerClass
{
public:
	std::vector<TextureClass*> m_vTextures; //Vector of Textures

	static TextureManagerClass* GetInstance(); //Singleton Accessor
	void ReleaseInstance();	//Singleton Destructor
	
	int IdentifyTexure(String sName); //Returns the ID number of the texture, -1 if it does not exist.
	int LoadTexture(String sName);	//Loads a texture and returns the ID of where its stored in the vector

	int GetNumberOfTextures(void); //Returns the number of texures in the vector
	GLuint ReturnGLIndex(int a_nIndex); //Returns the OpenGL Buffer ID in the vector location of the provided Index
private:
	static TextureManagerClass* m_pInstance; //Singleton
	TextureManagerClass(void); //Constructor	
	TextureManagerClass(const TextureManagerClass& other); //Copy Constructor
	TextureManagerClass& operator=(const TextureManagerClass& other);//Copy Assignment Operator
	~TextureManagerClass(void); //Destructor

	void Release(void); //Release the fields in the class
	void Init(void); //Initialize variables
};

}
#endif //_EMPTYSINGLETONCLASS_H