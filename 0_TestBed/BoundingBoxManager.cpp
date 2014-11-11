#include "BoundingBoxManager.h"

BoundingBoxManager* BoundingBoxManager::m_pInstance = nullptr;

BoundingBoxManager* BoundingBoxManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new BoundingBoxManager();
	}
	return m_pInstance;
}

void BoundingBoxManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void BoundingBoxManager::Init(void)
{
	m_pModelMngr = ModelManagerClass::GetInstance();
	m_vCollidingNamesOBB.clear();
	m_vCollidingNamesAABB.clear();
	m_nBoxes = 0;
}

void BoundingBoxManager::Release(void)
{
	RemoveBox("ALL");
	return;
}

//The big 3
BoundingBoxManager::BoundingBoxManager(){Init();}
BoundingBoxManager::BoundingBoxManager(BoundingBoxManager const& other){ }
BoundingBoxManager& BoundingBoxManager::operator=(BoundingBoxManager const& other) { return *this; }
BoundingBoxManager::~BoundingBoxManager(){Release();};

//Accessors
int BoundingBoxManager::GetNumberOfBoxes(void){ return m_nBoxes; }

void BoundingBoxManager::SetVisible(bool a_bVisible, String a_sInstance)
{
	if(a_sInstance == "ALL")
	{
		int nBoxes = GetNumberOfBoxes();
		for(int nBox = 0; nBox < nBoxes; nBox++)
		{
			m_vBoundingBox[nBox]->SetOBBVisible(a_bVisible); //CHANGE LATER
			m_vBoundingBox[nBox]->SetAABBVisible(a_bVisible);
		}
	}
	else
	{
		int nBox = m_pModelMngr->IdentifyInstance(a_sInstance);
		if(nBox < 0 || nBox < m_nBoxes)
		{
			m_vBoundingBox[nBox]->SetOBBVisible(a_bVisible);//CHANGE LATER
			m_vBoundingBox[nBox]->SetAABBVisible(a_bVisible);
		}
	}
}
void BoundingBoxManager::SetColor(vector3 colorAABB, String a_sInstance)
{
	if(a_sInstance == "ALL")
	{
		int nBoxes = GetNumberOfBoxes();

		for(int nBox = 0; nBox < nBoxes; nBox++)
		{
			m_vBoundingBox[nBox]->SetColorAABB(colorAABB);
			m_vBoundingBox[nBox]->SetColorOBB(colorAABB);
		}
	}
	else
	{
		int nBox = m_pModelMngr->IdentifyInstance(a_sInstance);

		if(nBox < 0 || nBox < m_nBoxes)
		{
			m_vBoundingBox[nBox]->SetColorAABB(colorAABB);
			m_vBoundingBox[nBox]->SetColorOBB(colorAABB);
		}
	}
}
void BoundingBoxManager::SetModelMatrix(matrix4 a_mModelMatrix, String a_sInstance)
{
	if(a_sInstance == "ALL")
	{
		int nBoxes = GetNumberOfBoxes();

		for(int nBox = 0; nBox < nBoxes; nBox++)
		{
			m_vBoundingBox[nBox]->SetModelMatrix(a_mModelMatrix);
		}
	}
	else
	{
		int nBox = m_pModelMngr->IdentifyInstance(a_sInstance);

		if(nBox < 0 || nBox < m_nBoxes)
		{
			m_vBoundingBox[nBox]->SetModelMatrix(a_mModelMatrix);
		}
	}
}
void BoundingBoxManager::Render(String a_sInstance)
{
	
	if(a_sInstance == "ALL")
	{
		int nBoxes = GetNumberOfBoxes();

		for(int nBox = 0; nBox < nBoxes; nBox++)
		{
			m_vBoundingBox[nBox]->Render(MEDEFAULT);
		}
	}
	else
	{
		int nBox = m_pModelMngr->IdentifyInstance(a_sInstance);

		if(nBox < 0 || nBox < m_nBoxes)
		{
			m_vBoundingBox[nBox]->Render(MEDEFAULT);
		}
	}
}
void BoundingBoxManager::AddBox(String a_sInstanceName)
{
	BoundingBoxClass* oBox = new BoundingBoxClass(a_sInstanceName);
	m_vBoundingBox.push_back(oBox);
	m_nBoxes++;
}
void BoundingBoxManager::RemoveBox(String a_sInstanceName)
{
	if(a_sInstanceName == "ALL")
	{
		//Clear the vector's element first otherwise there is a memory leak
		for(int nBox = 0; nBox < m_nBoxes; nBox++)
		{
			BoundingBoxClass* pBB = m_vBoundingBox[nBox];
			delete pBB;
		}
		m_vBoundingBox.clear();
		m_nBoxes = 0;
		return;
	}
	std::vector<BoundingBoxClass*> vTemp;
	int nBox = m_pModelMngr->IdentifyInstance(a_sInstanceName);
	if(nBox < 0 || nBox < m_nBoxes)
	{
		for(int nBox = 0; nBox < m_nBoxes; nBox++)
		{
			if(nBox != nBox)
			{
				vTemp.push_back(m_vBoundingBox[nBox]);
			}
			else
			{
				BoundingBoxClass* pBB = m_vBoundingBox[nBox];
				delete pBB;
			}
		}
	}
	m_vBoundingBox = vTemp;
	m_nBoxes++;
}
void BoundingBoxManager::Update(void)
{
	m_vCollidingNamesOBB.clear();
	m_vCollidingNamesAABB.clear();

	for(int nBox = 0; nBox < m_nBoxes; nBox++)
	{
		m_vBoundingBox[nBox]->SetColorOBB(MEWHITE);
		m_vBoundingBox[nBox]->SetColorAABB(MEWHITE);
	}
	
	CollisionCheck();
	CollisionResponse();
}
void BoundingBoxManager::CollisionCheck(void) //Needs working
{
	
}
bool BoundingBoxManager::CheckForNameInListOBB(String a_sName)
{
	int nNames = static_cast<int>(m_vCollidingNamesOBB.size());

	for(int nName = 0; nName < nNames; nName++)
	{
		if(m_vCollidingNamesOBB[nName] == a_sName)
			return true;
	}
	return false;
}
bool BoundingBoxManager::CheckForNameInListAABB(String a_sName)
{
	int nNames = static_cast<int>(m_vCollidingNamesAABB.size());

	for(int nName = 0; nName < nNames; nName++)
	{
		if(m_vCollidingNamesAABB[nName] == a_sName)
			return true;
	}
	return false;
}
void BoundingBoxManager::CollisionResponse(void)
{
	for(int nBox = 0; nBox < m_nBoxes; nBox++)
	{
		if(CheckForNameInListOBB(m_vBoundingBox[nBox]->GetInstanceName()))
			m_vBoundingBox[nBox]->SetColorOBB(MERED);

		if(CheckForNameInListOBB(m_vBoundingBox[nBox]->GetInstanceName()))
			m_vBoundingBox[nBox]->SetColorAABB(MEBLUE);
	}
}
