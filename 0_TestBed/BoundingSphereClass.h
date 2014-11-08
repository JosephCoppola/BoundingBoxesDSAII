/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/10
*/
#ifndef __BOUNDINGSPHERECLASS_H_
#define __BOUNDINGSPHERECLASS_H_

#include "ME\Mesh\shape\PrimitiveWireClass.h"
#include "ME\Mesh\shape\ModelManagerClass.h"
using namespace MyEngine;
//System Class
class BoundingSphereClass 
{
	String m_sInstance;//The name of the instance related to this sphere
	bool m_bVisible;//Flag for rendering or not
	float m_fRadius;//Radius of the Sphere
	vector3 m_v3Centroid;//Centroid of the Sphere
	vector3 m_v3Color;//Color of the Sphere
	matrix4 m_mModelToWorld;//Model matrix of the sphere
	PrimitiveWireClass* m_pMesh;//Sphere Mesh
	ModelManagerClass* m_pModelMngr;//ModelManager instance

public:
	/* Constructor 	*/
	BoundingSphereClass(String a_sInstanceName);
	/* Copy Constructor */
	BoundingSphereClass(BoundingSphereClass const& other);
	/* Copy Assignment Operator	*/
	BoundingSphereClass& operator=(BoundingSphereClass const& other);
	/*	Destructor	*/
	~BoundingSphereClass(void);

	/* Gets the visibility of the Sphere (whether or not it is going to be drawn in render) */
	bool GetVisible(void);
	/*Sets the visibility of the Sphere (whether or not it is going to be drawn in render)
	Args:
		bool a_bVisible -> true for draw false for not draw*/
	void SetVisible(bool a_bVisible);
	/* Property:
	GetVisible() or GetVisible()*/
	__declspec(property(get = GetVisible, put = SetVisible)) bool Visible;

	/* Gets the name of the model associated with this bounding sphere from model manager */
	String GetInstanceName(void);
	/* Property:
	GetInstanceName()*/
	__declspec(property(get = GetInstanceName)) String InstanceName;

	/* Gets the centroid the bounding sphere */
	vector3 GetCentroid(void);
	/* Property:
	GetCentroid()*/
	__declspec(property(get = GetCentroid)) vector3 Centroid;

	/* Get the radius of the bounding sphere */
	float GetRadius(void);
	/* Property:
	GetRadius()	*/
	__declspec(property(get = GetRadius)) float Radius;

	/* Gets the "ModelToWorld" matrix associated with the bounding sphere */
	matrix4 GetModelMatrix(void);
	/* Sets the "ModelToWorld" matrix associated with the bounding sphere */
	void SetModelMatrix(matrix4 a_ModelMatrix);
	/* "ModelToWorld"
	GetModelMatrix() or SetModelMatrix() */
	__declspec(property(get = GetModelMatrix, put = SetModelMatrix)) matrix4 ModelMatrix;

	/* Gets the color vector of this bounding sphere (the default color in which is going to be rendered) */
	vector3 GetColor(void);
	/* Sets the color vector of this bounding sphere (the default color in which is going to be rendered) */
	void SetColor(vector3 a_v3Color);
	/* Property:
	GetColor() or SetColor() */
	__declspec(property(get = GetColor, put = SetColor)) vector3 Color;

	/* Renders the bounding sphere
		Args:
			a_vColor -> determinate the color of the sphere to be rendered, if MEDEFAULT
			it will render the shape in the constructed color (white) */
	void Render( vector3 a_vColor = MEDEFAULT);

private:
	/* Released Memory and objects allocated. */
	void Release(void);
	/* Calculates the sphere from the instance
	Args:
		a_sInstance: The name of the instance for which the bounding sphere is going to be calculated */
	void CalculateSphere(String a_sInstance);
};


#endif //__BoundingSphereClass_H__