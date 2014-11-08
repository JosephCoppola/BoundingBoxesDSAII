/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef __MODELCLASS_H_
#define __MODELCLASS_H_

#include <thread>
#include "ME\mesh\shape\ShapeClass.h"
#include "ME\mesh\shape\GroupClass.h"
#include "ME\System\FileReaderClass.h"
#include "ME\mesh\Animation\SequenceClass.h"
#include "ME\mesh\Animation\StateClass.h"

namespace MyEngine
{

class MyEngineDLL ModelClass
{	
	SystemClass* m_pSystem;
	MaterialManagerClass* m_pMaterialManager;

	String m_sModelName;
	bool m_bLoaded;
	bool m_bBinded;
	int m_nMaterials;
	int m_nGroups;
	std::vector<GroupClass> m_vGroup;
	int m_nStates;
	std::vector<StateClass*> m_vpState;
	std::thread* m_Thread;
	int m_nHP;
	bool m_bVisible;
	bool m_bCollidable;
	std::vector<SequenceClass> m_vSecuence;

	AxisReferenceClass* m_pAxis;
	std::vector<AABBClass*> m_vAABB;
public:
	ModelClass(void);
	ModelClass(const ModelClass& other);
	ModelClass& operator=(const ModelClass& other);
	~ModelClass(void);
	
	void Release(void);

	MEErrors LoadOBJ(String a_sFileName);//bool whether the file exists or not

	void Swap(ModelClass& other);

	int GetNumberOfGroups(void); //Returns the number of shapes in the vector of shapes
	String GetName(void); //Return the name of the model
	__declspec(property(get = GetName)) String Name; //Name Property

	GroupClass& ReturnGroup(int a_nIndex);
	int IdentifyGroup( String a_sName);

	bool IsLoaded(void); //Specifies if the model has been read from a file

	bool InstanceGroup(GroupClass* a_Target, int a_nIndex);

	void CompileOpenGL3X(void);

	void SetHP(int a_nHP);
	int GetHP(void);

	void SetCollidable(bool a_bCollidable);
	bool GetCollidable(void);

	void SetVisible(bool a_bVisible);
	bool GetVisible(void);

	std::vector<vector3> GetVertices(int nGroup = 0, int nShape = 0);

	int GetNumberOfFrames(void);

	std::vector<SequenceClass>& GetSequenceVector(void); //returns the vector of sequences

	int GetStates(void);
	StateClass* GetState(int a_nState);
	AxisReferenceClass* GetAxis(void);
	AABBClass* GetAABB(int a_nObject);
		
private:
	void Init(void);
	MEErrors LoadThreadedOBJ(String a_sFileName);
	MEErrors LoadMTL(String a_sFileName);
	MEErrors LoadHIE(String a_sFileName);
	MEErrors LoadANIM(String a_sFileName);
	MEErrors LoadSEQ(String a_sFileName);
	MEErrors LoadSTA(String a_sFileName);

	GroupClass* GetGroup(String a_sName);

	StateClass* GetState(String a_sName);
	void CalculateMaxAndMin(void);
};

EXPIMP_TEMPLATE template class MyEngineDLL std::vector<ModelClass>;
EXPIMP_TEMPLATE template class MyEngineDLL std::vector<ModelClass*>;

}

#endif //_MODEL_H