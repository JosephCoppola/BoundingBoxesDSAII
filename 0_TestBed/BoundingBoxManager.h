#ifndef __BOUNDINGBOXMANAGER_H_
#define __BOUNDINGBOXMANAGER_H_

#include "BoundingBoxClass.h"

using namespace MyEngine;

//System Class
class BoundingBoxManager
{
	int m_nBoxes; //Number of boxes in the List
	std::vector<BoundingBoxClass*> m_vBoundingBox; //List of boxes in the manager
	ModelManagerClass* m_pModelMngr;//Model manager instance
	std::vector<String> m_vCollidingNamesOBB;//List of Names that are currently colliding at OBB
	std::vector<String> m_vCollidingNamesAABB;//List of Names that are currently colliding at AABB

public:

	static BoundingBoxManager* GetInstance(); // Singleton accessor

	void ReleaseInstance(void);

	int GetNumberOfBoxes(void);

	void AddBox(String a_sInstanceName);

	void RemoveBox(String a_sInstanceName = "ALL");

	void SetVisible(bool a_bVisible, String a_sInstanceName = "ALL");

	void SetColor(vector3 color, String a_sInstanceName = "ALL");

	void SetModelMatrix(matrix4 a_mModelMatrix, String a_sInstanceName = "ALL");

	void Render(String a_sInstanceName = "ALL");

	void Update(void);

private:
	
	//Big Three
	BoundingBoxManager(void);
	
	BoundingBoxManager(BoundingBoxManager const& other);
	
	BoundingBoxManager& operator=(BoundingBoxManager const& other);
	
	//Destructor
	~BoundingBoxManager(void);
	
	void Release(void);
	
	//Intialize 
	void Init(void);
	
	//Singleton
	static BoundingBoxManager* m_pInstance; 
	
	//Will Check collisions
	void CollisionCheck(void);
	
	//Respond to the collision
	void CollisionResponse(void);

	//Lists for checking collisions
	bool CheckForNameInListOBB(String a_sName);

	bool CheckForNameInListAABB(String a_sName);

};

#endif //__BoundingBoxManagerClass_H__
