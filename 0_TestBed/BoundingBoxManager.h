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
	std::vector<String> m_vCollidingNames;//List of Names that are currently colliding
public:
	static BoundingBoxManager* GetInstance(); // Singleton accessor
	void ReleaseInstance(void);
	int GetNumberOfBoxes(void);

	void AddBox(String a_sInstanceName);

	void RemoveBox(String a_sInstanceName = "ALL");

	void SetVisible(bool a_bVisible, String a_sInstanceName = "ALL");

	void SetColor(vector3 a_v3Color, String a_sInstanceName = "ALL");

	void SetModelMatrix(matrix4 a_mModelMatrix, String a_sInstanceName = "ALL");

	void Render(String a_sInstanceName = "ALL");

	void Update(void);

private:
	
	BoundingBoxManager(void);
	
	BoundingBoxManager(BoundingBoxManager const& other);
	
	BoundingBoxManager& operator=(BoundingBoxManager const& other);
	
	~BoundingBoxManager(void);
	
	void Release(void);
	
	void Init(void);
	
	static BoundingBoxManager* m_pInstance; 
	
	void CollisionCheck(void);
	
	void CollisionResponse(void);

	bool CheckForNameInList(String a_sName);
};

#endif //__BoundingBoxManagerClass_H__
