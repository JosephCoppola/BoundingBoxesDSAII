/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/05
*/
#ifndef __AABBCLASS_H_
#define __AABBCLASS_H_

#include "ME\mesh\Shape\ShapeClass.h"

namespace MyEngine
{

class MyEngineDLL AABBClass : public ShapeClass
{
	typedef ShapeClass super;
	bool m_bCompiled;
public:
	//Constructor
	AABBClass();
	AABBClass(vector3 a_vMin, vector3 a_vMax);
	//Copy Constructor
	AABBClass(const AABBClass& other);
	//Copy Assignment Operator
	virtual AABBClass& operator=(const AABBClass& other);

	//Destructor
	~AABBClass(void);
		
	//Renders the content of the shape
	void Render(matrix4 a_mToWorld = matrix4(1.0f), vector3 a_vColor = vector3(1.0f,1.0f,1.0f));
	void Render(vector3 a_vMin, vector3 a_vMax, matrix4 a_mToWorld = matrix4(1.0f), vector3 a_vColor = vector3(1.0f,1.0f,1.0f));

	void CompileForColor(void);
};

EXPIMP_TEMPLATE template class MyEngineDLL std::vector<AABBClass>;
EXPIMP_TEMPLATE template class MyEngineDLL std::vector<AABBClass*>;

}

#endif //AABBCLASS