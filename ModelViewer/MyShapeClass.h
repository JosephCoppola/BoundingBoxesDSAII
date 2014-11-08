/*
Programmer: Include your name here
Date: 2014/10
*/
#ifndef __ASSIGMNENTCLASS_H__
#define __ASSIGNMENTCLASS_H__

#include "ME\MyEngine.h"

using namespace MyEngine; //Using the MyEngine

class MyShapeClass : public ShapeClass
{
	typedef ShapeClass super; //To call ShapeClass

public:
	/*
		To compile objects inside MyEngine, it takes the vertices and bind the buffers
	*/
	void CompileObject(vector3 a_vColor, String a_sName);

	void GenerateCube(float a_fSize, vector3 a_Color);//Cube
	
	void GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor);//Cone

	void GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor);//Cylinder

	void GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor);//Tube

	void GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_vColor);//Sphere

	virtual void Render();// NEW! as originally posted it was trying to render everything using triangle strips instead of triangles

private:
	void AddQuad(vector3 a_vA, vector3 a_vB, vector3 a_vC, vector3 a_cD);
};


#endif //__3DSHAPECLASS_H__