/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef __WIREFRAMECLASS_H_
#define __WIREFRAMECLASS_H_

#include "ME\mesh\shape\ShapeClass.h"

namespace MyEngine
{

class MyEngineDLL PrimitiveWireClass : public ShapeClass
{
	typedef ShapeClass super;

public:
	//Constructor
	PrimitiveWireClass();
	//Copy Constructor
	PrimitiveWireClass(const PrimitiveWireClass& other);
	//Copy Assignment Operator
	virtual PrimitiveWireClass& operator=(const PrimitiveWireClass& other);

	//Destructor
	~PrimitiveWireClass(void);

	//Generates a shape
	void GenerateCube(float a_fSize, vector3 a_vColor);
	void GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor);
	void GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor);
	void GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor);
	void GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_vColor);
	
	//Renders the content of the shape
	virtual void Render(GLenum mode = GL_TRIANGLES);
	virtual void Render(matrix4 a_mModelMatrix, vector3 a_vColor = MEDEFAULT);

private:
	void CompileObject(vector3 a_vColor, String a_sName);
	void AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight);
	void AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTop);
};

EXPIMP_TEMPLATE template class MyEngineDLL std::vector<PrimitiveWireClass>;
EXPIMP_TEMPLATE template class MyEngineDLL std::vector<PrimitiveWireClass*>;

}

#endif //__WIREFRAMCLASS_H_