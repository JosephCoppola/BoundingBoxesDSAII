/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/05
*/
#ifndef __AXISREFERENCECLASS_H_
#define __AXISREFERENCECLASS_H_

#include "ME\mesh\Shape\ShapeClass.h"

namespace MyEngine
{

class MyEngineDLL AxisReferenceClass : public ShapeClass
{
	typedef ShapeClass super;
	bool m_bCompiled;
public:
	//Constructor
	AxisReferenceClass();
	//Copy Constructor
	AxisReferenceClass(const AxisReferenceClass& other);
	//Copy Assignment Operator
	virtual AxisReferenceClass& operator=(const AxisReferenceClass& other);

	//Destructor
	~AxisReferenceClass(void);
		
	//Renders the content of the shape
	virtual void Render(float a_fSize = 1.0f, matrix4 input = matrix4(1.0f));

	void CompileAxis(void);
	void InstanceFrom(AxisReferenceClass* other);
};

EXPIMP_TEMPLATE template class MyEngineDLL std::vector<AxisReferenceClass>;
EXPIMP_TEMPLATE template class MyEngineDLL std::vector<AxisReferenceClass*>;

}
#endif //AXISREFERENCECLASS