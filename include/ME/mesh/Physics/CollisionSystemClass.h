/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/07
*/
#ifndef __COLLISIONSYSTEMCLASS_H_
#define __COLLISIONSYSTEMCLASS_H_

#include "ME\system\SystemClass.h"
#include "ME\mesh\physics\AABBClass.h"
#include "ME\mesh\Debug\BoxManagerClass.h"

namespace MyEngine
{

//System Class
class MyEngineDLL CollisionSystemClass
{
public:
	static CollisionSystemClass* GetInstance(); // Singleton accessor
	void ReleaseInstance(void); //Singleton Release

	bool AABBAreColliding(	AABBClass* a_AABB1, AABBClass* a_AABB2);

	bool AABBAreColliding(	vector3 a_v3Min1, vector3 a_v3Max1, matrix4 a_mModelToWorld1,
							vector3 a_v3Min2, vector3 a_v3Max2, matrix4 a_mModelToWorld2);

	bool AABBAreColliding(AABBClass* a_AABB, vector3 a_v3RayOrigin, vector3 a_v3RayDirection, float& a_fDistance);

private:
	CollisionSystemClass(void); // Constructor
	CollisionSystemClass(CollisionSystemClass const& other); //Copy Constructor
	CollisionSystemClass& operator=(CollisionSystemClass const& other); // Copy Assignment Operator
	~CollisionSystemClass(void); // Destructor

	void Release(void); // Release Memory
	void Init(void); // Initialize variables
	
	static CollisionSystemClass* m_pInstance; // Singleton
};

}

#endif //__COLLISIONSYSTEMCLASS_H__