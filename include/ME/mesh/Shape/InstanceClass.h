/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef __INSTANCECLASS_H_
#define __INSTANCECLASS_H_

#include "ME\mesh\shape\ModelClass.h"
#include "ME\mesh\Physics\CollisionSystemClass.h"
#include "ME\mesh\Debug\BoxManagerClass.h"
#include "ME\mesh\Physics\BSClass.h"

namespace MyEngine
{

class MyEngineDLL InstanceClass
{
	SystemClass* m_pSystem;
	MaterialManagerClass* m_pMaterialManager;
	BoxManagerClass* m_pBoxMngr;

	bool m_bInstanciated;
	String m_sName;
	glm::mat4 m_mToWorld; //GLM Model Matrix
	ModelClass* m_pModel;
	
	int m_nGroups;
	std::vector<GroupClass> m_vGroup;

	int m_nStates;
	std::vector<StateClass*> m_vpState;

	std::vector<String> m_vCollidingNames;

	int m_nStateLast;
	int m_nStateCurrent;
	int m_nStateNext;
	
	int m_nHP;
	bool m_bVisible;
	bool m_bCollidable;
	
	DWORD m_dLastRenderCall;
	float m_fLastFrameDrawn;

	bool m_bDebug;
	bool m_bCoordinateSystemVisible;
	AxisReferenceClass* m_pAxis;
	std::vector<AABBClass*> m_vAABB;
	int m_nSector;

	bool m_bOBB;
	AABBClass* m_pOBB;
	BSClass* m_pBS;

	bool m_bFirstRender;
public:
	InstanceClass(void); //Constructor
	InstanceClass(const InstanceClass& other); //Copy Constructor
	InstanceClass& operator=(const InstanceClass& other); //Copy Assignment Operator
	~InstanceClass(void); //Destructor

	void InstanceModel(ModelClass& a_Model); //Create an Instance of a previously loaded model

	void SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName);
	void SetShaderProgram(String a_sShaderName);
	
	void Render(void);//Render all groups

	void ResetOBB(void);
	void CalculateOBB(void);
	AABBClass* GetOBB(void);
	void AddOBBToBoxList (vector3 a_v3Color = MEGREEN, String sIncludeGroup = "ALL");
	void AddAABBToBoxList (vector3 a_v3Color = MEGREEN, String sIncludeGroup = "ALL");
	void SetBSColor(vector3 a_vColor);
	void SetBSVisible(bool a_bVisible);
	BSClass* GetBoundingSphere(void);

//Accessors
	bool IsInstanced(void);

	int IdentifyGroup( String a_sName);

	void SetModelMatrix(const glm::mat4 a_mModel = glm::mat4(1.0f));
	glm::mat4& GetModelMatrix(void);
	__declspec(property(put = SetModelMatrix, get = GetModelMatrix)) glm::mat4 ModelMatrix;

	void SetName(String a_sName); //Sets Variable
	String GetName(int nGroup = -1);//Gets Variable

	void SwapMaterials( String sOldMaterialName, String sNewMaterialName);

	ModelClass* GetModelInstanced(void);

	void SetHP(int a_nHP);
	int GetHP(void);

	void SetCollidable(bool a_bCollidable);
	bool GetCollidable(void);

	void SetVisible(bool a_bVisible);
	bool GetVisible(void);

	void SetNextState(int a_nNext);
	void SetCurrentSate(int a_nState);

	void SetGroupShader(String sProgramName, String sGroupName = "ALL");
	void SetGroupMaterial(String sMaterialName, String sGroupName = "ALL");

	void SetDebug(bool a_bDebug, String sIncludeGroup = "ALL");
	void SetCoordinateSystemVisible(bool a_bVisible);

	void SetSector(int a_nSector);
	int GetSector(void);

	AABBClass* GetAABB(int a_nObject);
	
	int GetLastFrameDrawn(void);

	void ClearColliderInfo(void);
	void AddCollisionName(String a_sInstanceName);
	std::vector<String> GetCollisionNames(int nGroup = -1);
	int GetNumberOfGroups(void);

	bool NameIsInCollisionList(String a_sName);

	bool CheckCollision(InstanceClass* a_pInstance);
	String CheckCollision(vector3 a_v3RayStart, vector3 a_vRayDirection);

	int GetNumberOfFrames(void);

private:
	void Init(void); //Initializes the variables

	void Release(void); //Release the fields in the class

	void Swap(InstanceClass& other); //Swaps Content with other Instance class

	GroupClass* GetGroup(String a_sName);

	int IdentifyState(StateClass* a_pState);

	void CalculateMaxAndMin(void);
};

EXPIMP_TEMPLATE template class MyEngineDLL std::vector<InstanceClass>;
EXPIMP_TEMPLATE template class MyEngineDLL std::vector<InstanceClass*>;

}

#endif //_INSTANCECLASS_H
