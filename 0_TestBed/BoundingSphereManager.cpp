#include "BoundingSphereManager.h"
//  BoundingSphereManager
BoundingSphereManager* BoundingSphereManager::m_pInstance = nullptr;

BoundingSphereManager* BoundingSphereManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new BoundingSphereManager();
	}
	return m_pInstance;
}
void BoundingSphereManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
void BoundingSphereManager::Init(void)
{
	m_pModelMngr = ModelManagerClass::GetInstance();
	m_vCollidingNames.clear();
	m_nSpheres = 0;
}
void BoundingSphereManager::Release(void)
{
	RemoveSphere("ALL");
	return;
}
//The big 3
BoundingSphereManager::BoundingSphereManager(){Init();}
BoundingSphereManager::BoundingSphereManager(BoundingSphereManager const& other){ }
BoundingSphereManager& BoundingSphereManager::operator=(BoundingSphereManager const& other) { return *this; }
BoundingSphereManager::~BoundingSphereManager(){Release();};
//Accessors
int BoundingSphereManager::GetNumberOfSpheres(void){ return m_nSpheres; }
//--- Non Standard Singleton Methods
void BoundingSphereManager::SetVisible(bool a_bVisible, String a_sInstance)
{
	if(a_sInstance == "ALL")
	{
		int nSpheres = GetNumberOfSpheres();
		for(int nSphere = 0; nSphere < nSpheres; nSphere++)
		{
			m_vBoundingSphere[nSphere]->SetVisible(a_bVisible);
		}
	}
	else
	{
		int nSphere = m_pModelMngr->IdentifyInstance(a_sInstance);
		if(nSphere < 0 || nSphere < m_nSpheres)
			m_vBoundingSphere[nSphere]->SetVisible(a_bVisible);
	}
}
void BoundingSphereManager::SetColor(vector3 a_v3Color, String a_sInstance)
{
	if(a_sInstance == "ALL")
	{
		int nSpheres = GetNumberOfSpheres();
		for(int nSphere = 0; nSphere < nSpheres; nSphere++)
		{
			m_vBoundingSphere[nSphere]->SetColor(a_v3Color);
		}
	}
	else
	{
		int nSphere = m_pModelMngr->IdentifyInstance(a_sInstance);
		if(nSphere < 0 || nSphere < m_nSpheres)
			m_vBoundingSphere[nSphere]->SetColor(a_v3Color);
	}
}
void BoundingSphereManager::SetModelMatrix(matrix4 a_mModelMatrix, String a_sInstance)
{
	if(a_sInstance == "ALL")
	{
		int nSpheres = GetNumberOfSpheres();
		for(int nSphere = 0; nSphere < nSpheres; nSphere++)
		{
			m_vBoundingSphere[nSphere]->SetModelMatrix(a_mModelMatrix);
		}
	}
	else
	{
		int nSphere = m_pModelMngr->IdentifyInstance(a_sInstance);
		if(nSphere < 0 || nSphere < m_nSpheres)
			m_vBoundingSphere[nSphere]->SetModelMatrix(a_mModelMatrix);
	}
}
void BoundingSphereManager::Render(String a_sInstance)
{
	
	if(a_sInstance == "ALL")
	{
		int nSpheres = GetNumberOfSpheres();
		for(int nSphere = 0; nSphere < nSpheres; nSphere++)
		{
			m_vBoundingSphere[nSphere]->Render(MEDEFAULT);
		}
	}
	else
	{
		int nSphere = m_pModelMngr->IdentifyInstance(a_sInstance);
		if(nSphere < 0 || nSphere < m_nSpheres)
			m_vBoundingSphere[nSphere]->Render(MEDEFAULT);
	}
}
void BoundingSphereManager::AddSphere(String a_sInstanceName)
{
	BoundingSphereClass* oSphere = new BoundingSphereClass(a_sInstanceName);
	m_vBoundingSphere.push_back(oSphere);
	m_nSpheres ++;
}
void BoundingSphereManager::RemoveSphere(String a_sInstanceName)
{
	if(a_sInstanceName == "ALL")
	{
		//Clear the vector's element first otherwise there is a memory leak
		for(int nSphere = 0; nSphere < m_nSpheres; nSphere++)
		{
			BoundingSphereClass* pBS = m_vBoundingSphere[nSphere];
			delete pBS;
		}
		m_vBoundingSphere.clear();
		m_nSpheres = 0;
		return;
	}
	std::vector<BoundingSphereClass*> vTemp;
	int nSphere = m_pModelMngr->IdentifyInstance(a_sInstanceName);
	if(nSphere < 0 || nSphere < m_nSpheres)
	{
		for(int nSphere = 0; nSphere < m_nSpheres; nSphere++)
		{
			if(nSphere != nSphere)
			{
				vTemp.push_back(m_vBoundingSphere[nSphere]);
			}
			else
			{
				BoundingSphereClass* pBS = m_vBoundingSphere[nSphere];
				delete pBS;
			}
		}
	}
	m_vBoundingSphere = vTemp;
	m_nSpheres++;
}
void BoundingSphereManager::Update(void)
{
	m_vCollidingNames.clear();
	for(int nSphere = 0; nSphere < m_nSpheres; nSphere++)
	{
		m_vBoundingSphere[nSphere]->SetColor(MEWHITE);
	}
	CollisionCheck();
	CollisionResponse();
}
void BoundingSphereManager::CollisionCheck(void)
{
	for(int nSphere2 = 0; nSphere2 < m_nSpheres; nSphere2++)
	{
		for(int nSphere1 = 0; nSphere1 < m_nSpheres; nSphere1++)
		{
			if(nSphere1 != nSphere2)
			{
				//Get Radius of sphere1
				float fRadius1 = m_vBoundingSphere[nSphere1]->GetRadius();
				
				//Get Radius of sphere2
				float fRadius2 = m_vBoundingSphere[nSphere2]->GetRadius();
				
				//Get origin of sphere1
				matrix4 mMatrix1 = m_vBoundingSphere[nSphere1]->GetModelMatrix();
				vector3 vCentroid1 = m_vBoundingSphere[nSphere1]->GetCentroid();
				vector3 fOrigin1 = static_cast<vector3>(glm::translate(mMatrix1, vCentroid1) * vector4(0.0f, 0.0f, 0.0f, 1.0f));
				
				//Get origin of sphere2
				matrix4 mMatrix2 = m_vBoundingSphere[nSphere2]->GetModelMatrix();
				vector3 vCentroid2 = m_vBoundingSphere[nSphere2]->GetCentroid();
				vector3 fOrigin2 = static_cast<vector3>(glm::translate(mMatrix2, vCentroid2) * vector4(0.0f, 0.0f, 0.0f, 1.0f));
				
				float fDistance = glm::distance(fOrigin1,fOrigin2);
				float fRadiusSum = fRadius1 + fRadius2;
				if(fDistance < fRadiusSum)
				{
					m_vCollidingNames.push_back(m_vBoundingSphere[nSphere1]->GetInstanceName());
					m_vCollidingNames.push_back(m_vBoundingSphere[nSphere2]->GetInstanceName());
				}
			}
		}
	}
}
bool BoundingSphereManager::CheckForNameInList(String a_sName)
{
	int nNames = static_cast<int>(m_vCollidingNames.size());
	for(int nName = 0; nName < nNames; nName++)
	{
		if(m_vCollidingNames[nName] == a_sName)
			return true;
	}
	return false;
}
void BoundingSphereManager::CollisionResponse(void)
{
	for(int nSphere = 0; nSphere < m_nSpheres; nSphere++)
	{
		if(CheckForNameInList(m_vBoundingSphere[nSphere]->GetInstanceName()))
			m_vBoundingSphere[nSphere]->SetColor(MERED);
	}
}