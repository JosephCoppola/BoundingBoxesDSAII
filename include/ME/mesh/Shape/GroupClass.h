/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/05
*/
#ifndef __GROUP_H_
#define __GROUP_H_

#include "ME\mesh\shape\ShapeClass.h"
#include "ME\materials\MaterialManagerClass.h"
#include "ME\mesh\Animation\FrameClass.h"
#include "ME\mesh\Animation\AnimationClass.h"
#include "ME\mesh\Debug\AxisReferenceClass.h"
#include "ME\mesh\Physics\AABBClass.h"
#include "ME\mesh\Debug\BoxManagerClass.h"

namespace MyEngine
{

class MyEngineDLL GroupClass
{	
	SystemClass* m_pSystem;
	MaterialManagerClass* m_pMaterialManager;
	GroupClass* m_pParent;
	FrameClass* m_pFrame;
	AxisReferenceClass* m_pAxis;
	AABBClass* m_pAABB;

	int m_nShapes;
	int m_nHP;
	int m_nFrames;

	bool m_bVisible;
	bool m_bCollidable;
	bool m_bGlobalized;
	bool m_bDebug;

	String m_sName;
	String m_sParent;
	vector3 m_v3Pivot;
	vector3 m_v3Max;
	vector3 m_v3Min;
	matrix4 m_mToWorld;
	std::vector<ShapeClass> m_vShape;
	std::vector<String> m_vCollidingNames; //Tell with what other groups this group is colliding

	bool m_bOBB;
	AABBClass* m_pOBB;
		
public:
	GroupClass(void);
	GroupClass(const GroupClass& other);
	GroupClass& operator=(const GroupClass& other);
	~GroupClass(void);
	
	void Release(void);
	void ReleaseBoxes(void);

	void Swap(GroupClass& other);

	int GetNumberOfShapes(void); //Returns the number of shapes in the vector of shapes
	String GetName(void); //Return the name of the group
	void SetName(String a_sName);
	__declspec(property(get = GetName, put = SetName)) String Name; //Name Property

	ShapeClass& ReturnShape(int a_nIndex);//Returns the shape in the given index

	void AddShape(String a_sName);

	void CompileOpenGL3X( void );

	int IdentifyShapeByMaterial( String a_sName);

	bool CloneFromGroup(const GroupClass& other);

	void Render(int nFrame = 0, matrix4 a_mToWorld = matrix4(1.0f));//Render all shapes

	void ReleaseOpenGL(); //DeleteOpenGL

	void CompleteMissingShapeInfo(bool a_bAverageNormals = false);

	void SwapMaterial( String sOldMaterialName, String sNewMaterialName);

	void SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName);
	void SetShaderProgram(String a_sShaderName);

	void SetMaterial(String a_sMaterialName);

	void SetPivot(vector3 a_v3Pivot);

	void SetParent(GroupClass* a_pParent);

	void SetHP(int a_nHP);
	int GetHP(void);

	void SetCollidable(bool a_bCollidable);
	bool GetCollidable(void);

	void SetVisible(bool a_bVisible);
	bool GetVisible(void);

	String GetParentName(void);
	void SetParentName(String a_sParent);

	void SetGlobalized(bool a_bGlobalized);

	int GetNumberOfFrames(void);

	void GenerateFrames(int a_nFrames);

	void ReleaseFrames(void);

	void SetFrame(int nFrame, vector3 a_v3Translation, vector3 a_v3Rotation, vector3 a_v3Scale, bool a_bVisible, bool a_bKeyframe);

	void SetPosX( float fValue, int nFrame);
	void SetPosY( float fValue, int nFrame);
	void SetPosZ( float fValue, int nFrame);

	void SetAngX( float fValue, int nFrame);
	void SetAngY( float fValue, int nFrame);
	void SetAngZ( float fValue, int nFrame);

	void SetSizeX( float fValue, int nFrame);
	void SetSizeY( float fValue, int nFrame);
	void SetSizeZ( float fValue, int nFrame);

	void SetVisible( bool bValue, int nFrame);
	void SetKeyframe( bool bValue, int nFrame);
	void SetDebug(bool a_bDebug);

	void ComputeMatrix(void);

	void Interpolate(int a_nFrames);

	AxisReferenceClass* GetAxis(void);
	AABBClass* GetAABB(void);

	vector3 GetMin(void);
	vector3 GetMax(void);
	vector3 GetGlobalMin(int a_nFrame);
	vector3 GetGlobalMax(int a_nFrame);

	void ComputeAABB(void);

	void ClearColliderInfo(void);
	void AddCollisionName(String a_sInstanceName, String a_sGroupName);
	std::vector<String> GetCollisionNames(void);

	glm::mat4& GetModelMatrix(void);

	void ResetOBB(void);
	void CalculateOBB(matrix4 a_mModelToWorld);
	AABBClass* GetOBB(void);
	matrix4 TranverseHierarchy(GroupClass* group, int nFrame = 0);

	std::vector<vector3> GetVertices(int nShape = 0);
private:
	void Init(void);
	
	void CalculateMaxAndMin(void);
};

EXPIMP_TEMPLATE template class MyEngineDLL std::vector<GroupClass>;
EXPIMP_TEMPLATE template class MyEngineDLL std::vector<GroupClass*>;

}
#endif //__GROUP_H__