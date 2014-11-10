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
	float m_fRadius;//Radius of the Box
	vector3 OBBCentroid;//Centroid of the OBB
	vector3 AABBCentroid;//Centroid of the AABB
	vector3 OBBColor;//Color of the Box
	vector3 AABBColor;
	matrix4 m_mModelToWorld;//Model matrix of the Box
	PrimitiveWireClass* m_pMeshOBB;//OBB Mesh
	PrimitiveWireClass* m_pMeshAABB;//AABB Mesh
	ModelManagerClass* m_pModelMngr;//ModelManager instance
	vector3 minOBB;
	vector3 maxOBB;
	vector3 minAABB;
	vector3 maxAABB;
	vector3 scaleOBB;
	vector3 scaleAABB;

public:
	BoundingBoxClass(String a_sInstanceName);
	
	BoundingBoxClass(BoundingBoxClass const& other);
	
	BoundingBoxClass& operator=(BoundingBoxClass const& other);

	~BoundingBoxClass(void);

	bool GetOBBVisible(void);

	void SetOBBVisible(bool a_bVisible);
	
	bool GetAABBVisible(void);

	void SetAABBVisible(bool a_bVisisble);

	__declspec(property(get = GetVisible, put = SetVisible)) bool Visible;

	String GetInstanceName(void);

	__declspec(property(get = GetInstanceName)) String InstanceName;

	vector3 GetCentroid(void);

	__declspec(property(get = GetCentroid)) vector3 Centroid;

	
	float GetRadius(void);

	__declspec(property(get = GetRadius)) float Radius;

	matrix4 GetModelMatrix(void);
	
	void SetModelMatrix(matrix4 a_ModelMatrix);

	__declspec(property(get = GetModelMatrix, put = SetModelMatrix)) matrix4 ModelMatrix;

	vector3 GetColor(void);

	void SetColor(vector3 a_v3Color);

	__declspec(property(get = GetColor, put = SetColor)) vector3 Color;

	void Render( vector3 a_vColor = MEDEFAULT);

private:
	
	void Release(void);
	
	void CalculateAABB(String a_sInstance);
	void CalculateOBB(String a_sInstance);
};


#endif //__BoundingBoxClass_H__

