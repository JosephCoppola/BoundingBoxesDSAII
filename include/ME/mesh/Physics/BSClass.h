/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/10
*/
#ifndef __BSCLASS_H_
#define __BSCLASS_H_

#include "ME\mesh\Shape\PrimitiveClass.h"

namespace MyEngine
{

//System Class
class MyEngineDLL BSClass
{
	typedef ShapeClass super;
	
	PrimitiveClass* m_pMesh;
	matrix4 m_mModelToWorld;

	vector3 m_v3Centroid;
	float m_fRadius;

	bool m_bVisible;
	
public:
	BSClass(void); // Constructor
	BSClass(BSClass const& other); //Copy Constructor
	BSClass& operator=(BSClass const& other); // Copy Assignment Operator
	~BSClass(void); // Destructor

	void Swap(BSClass& other); // Initialize variables

	matrix4 GetModelMatrix(void);
	void SetModelMatrix(matrix4 a_mModelMatrix);

	void Init(std::vector<vector3> a_vVertices, matrix4 a_mModelMatrix);

	void SetColor(vector3 a_v3Color = MERED);

	void SetVisible(bool a_bVisible);
	bool GetVisible(void);

	void Render(void);
private:
	void Release(void); // Release Memory
	void Init(void); // Initialize variables

	
	float CalculateRadius(std::vector<vector3> a_vVertices);
	vector3 CalculateCentroid(std::vector<vector3> a_vVertices);
	vector3 CalculateMinimum(std::vector<vector3> a_vVertices);
	vector3 CalculateMaximum(std::vector<vector3> a_vVertices);
};

EXPIMP_TEMPLATE template class MyEngineDLL std::vector<BSClass>;
EXPIMP_TEMPLATE template class MyEngineDLL std::vector<BSClass*>;

}

#endif //__BSCLASS_H__