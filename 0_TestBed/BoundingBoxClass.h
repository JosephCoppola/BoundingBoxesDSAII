#pragma once

#ifndef __BOUNDINGBOXCLASS_H_
#define __BOUNDINGBOXCLASS_H_

#include "ME\Mesh\shape\PrimitiveWireClass.h"
#include "ME\Mesh\shape\ModelManagerClass.h"
using namespace MyEngine;

class BoundingBoxClass
{
public:

	String m_sInstance;//The name of the instance related to this sphere
	bool m_obVisible;//Flag for rendering or not for OBB
	bool m_abVisible;//Flag for rendering or not for AABB
	vector3 OBBCentroid;//Centroid of the OBB
	vector3 AABBCentroid;//Centroid of the AABB
	vector3 OBBColor;//Color of the OBB
	vector3 AABBColor; //Color of AABB
	//Mins and Maxs for oBB and AABB
	vector3 minOBB;
	vector3 maxOBB;
	vector3 minAABB;
	vector3 maxAABB;
	//Scale Vectors
	vector3 scaleOBB;
	vector3 scaleAABB;
	matrix4 m_mModelToWorld;//Model matrix of the Box
	PrimitiveWireClass* m_pMeshOBB;//OBB Mesh
	PrimitiveWireClass* m_pMeshAABB;//AABB Mesh
	ModelManagerClass* m_pModelMngr;//ModelManager instance

public:
	//Big three
	BoundingBoxClass(String a_sInstanceName);
	
	BoundingBoxClass(BoundingBoxClass const& other);
	
	BoundingBoxClass& operator=(BoundingBoxClass const& other);

	//Destructor
	~BoundingBoxClass(void);

	//Get and set the visibility of OBB and AABB
	bool GetOBBVisible(void);

	void SetOBBVisible(bool a_bVisible);
	
	bool GetAABBVisible(void);

	void SetAABBVisible(bool a_bVisisble);

	__declspec(property(get = GetVisible, put = SetVisible)) bool Visible;

	String GetInstanceName(void);

	__declspec(property(get = GetInstanceName)) String InstanceName;

	//Get centroids of OBB and AABB
	vector3 GetCentroidOBB(void);
	
	__declspec(property(get = GetCentroidOBB)) vector3 OBBCentroid;

	vector3 GetCentroidAABB(void);

	__declspec(property(get = GetCentroidAABB)) vector3 AABBCentroid;
	
	//Get and set the model matrix of the box
	matrix4 GetModelMatrix(void);
	
	void SetModelMatrix(matrix4 a_ModelMatrix);

	__declspec(property(get = GetModelMatrix, put = SetModelMatrix)) matrix4 ModelMatrix;

	vector3 GetColorAABB(void);

	void SetColorAABB(vector3 p_Color);

	vector3 GetColorOBB(void);

	void SetColorOBB(vector3 p_Color);

	//__declspec(property(get = GetColor, put = SetColor)) vector3 Color;

	void Render( vector3 a_vColor = MEDEFAULT);

	//Get the size of the obb and aabb boxes
	vector3 GetSizeOBB(void);

	vector3 GetSizeAABB(void);

	void SetSizeOBB(vector3 p_sizeVector);

	void SetSizeAABB(vector3 p_sizeVector);

	//Accessor mins and max
	vector3 GetMinOBB(void);
	vector3 GetMaxOBB(void);
	vector3 GetMinAABB(void);
	vector3 GetMaxAABB(void);

private:
	
	void Release(void);
	
	void CalculateBoundingBox(String a_sInstance);
};


#endif //__BoundingBoxClass_H__

