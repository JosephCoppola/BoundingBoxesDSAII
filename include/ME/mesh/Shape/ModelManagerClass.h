/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef __MODELMANAGERCLASS_H_
#define __MODELMANAGERCLASS_H_

#include <string>
#include "ME\mesh\shape\InstanceClass.h"
#include "ME\mesh\Physics\CollisionSystemClass.h"
#include "ME\mesh\Debug\LineManagerClass.h"

namespace MyEngine
{

class MyEngineDLL ModelManagerClass
{
	//Member variables
	static ModelManagerClass* m_pInstance; //Singleton
	MaterialManagerClass* pMatMngr;
	BoxManagerClass* m_pBoxMngr;
	LineManagerClass* m_pLineMngr;

	std::vector<String> m_vNames;
	int m_nInstances;
	int m_nModels;
	bool m_bShowOBB;
	bool m_bShowAABB;
	bool m_bDebug;

	//Member Methods
	ModelManagerClass(void); //Constructor	
	ModelManagerClass(const ModelManagerClass& other); //Copy Constructor
	ModelManagerClass& operator=(const ModelManagerClass& other);//Copy Assignment Operator
	~ModelManagerClass(void); //Destructor

	void Release(void); //Release the fields in the class
	void Init(void); //Initialize variables

public:
	//Member Variables
	std::vector<ModelClass*> m_vModel; //Vector of Models
	std::vector<InstanceClass*> m_vInstance; //Vetor of Model Instances

	//Member Methods
	static ModelManagerClass* GetInstance(); //Singleton Accessor
	void ReleaseInstance();	//Singleton Destructor
	
	void LoadLevel(String a_sFileName);
	MEErrors LoadModel (	String a_sFileName,
							String a_sInstanceName,
							matrix4 a_Matrix = matrix4(1.0),
							int a_nVisibility = 1,
							int a_nCollidable = 1,
							int a_nState = 0); //Creates an instance of the specified model.

	void DeleteInstance(String a_sInstance = "ALL");

	int GetNumberOfModels(void);
	int GetNumberOfInstances(void);
	
	int IdentifyModel(String a_sFileName);	//Returns the index of a model in the vector
	int IdentifyInstance(String a_sName);	//Returns the index of an intance in the vector

	void SetShaderProgram(String a_sInstanceName, String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName);
	void SetShaderProgram(String a_sInstanceName, String a_sShaderName);
	
	void SetModelMatrix(matrix4 a_mMatrix, String a_sInstance = "All_Models"); //Modify the model matrix of the models
	matrix4 GetModelMatrix(String a_sInstance); //Returns the model matrix for the specified model, the Identity if the model does not exist

	std::vector<vector3> GetVertices(String a_sInstanceName); //Returns the vertices of the first shape of the first group in this model that has vertices, not the whole mesh

	void ModifyMaterial(	String a_sInstance,
							String a_sOldMaterialName,
							String a_sNewMaterialName,
							String a_sDiffuseTexture = "SAME",
							String a_sNormalTexture = "SAME",
							String a_sSpecularTexture = "SAME");

	MEErrors LoadAddOn(String sInstanceName, String sFileName);

	void Update(void);
	void SetDebugMode(bool a_bDebug);

	void SetBoundingSphereVisible(bool a_bVisible, String a_sInstance = "ALL");
	void SetBoundingSphereColor(vector3 a_v3Color, String a_sInstance = "ALL");
	void SetCoordinateSystemVisible(bool m_bVisible, String a_sInstance = "ALL");
	void SetDebug(bool a_bDebug, String a_sInstance = "ALL");

	BSClass* GetBoundingSphere(String a_sInstance);
	void RenderInstance(String a_sInstance = "ALL"); //Renders the specified instance

	String GetInstanceName(int nIndex);//Returns the name of the instance from the list in that index

	void SetNextState(String a_sIntance, int a_nNextState);
	
	void CheckCollission(void);
	String CheckCollission(vector3 a_v3RayOrigin,vector3 a_v3RayDirection);
	void ProcessCollisions(std::vector<String> a_vNames);

	

	void SetShowOBB(bool a_bShow);
	bool GetShowOBB(void);

	void SetShowAABB(bool a_bShow);
	bool GetShowAABB(void);

	void ProcessNames(void);

	String ShootRay(int a_nMouseX, int a_nMouseY, CameraClass* a_pCamera, bool a_bDrawRay = false);
};

}

#endif //_MODELMANAGERCLASS