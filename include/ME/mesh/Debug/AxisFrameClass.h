/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef __AXISFRAMECLASS_H_
#define __AXISFRAMECLASS_H_

#include "ME\system\SystemClass.h"
#include "ME\mesh\CameraClass.h"
#include "ME\mesh\Shape\ShapeClass.h"

namespace MyEngine
{

class MyEngineDLL AxisFrameClass : public ShapeClass
{
public:
	enum MyEnum
	{
		XY = 1,
		XZ = 2,
		YZ = 4
	};
protected:
	typedef ShapeClass super;
public:
	//Constructor
	AxisFrameClass();
	//Copy Constructor
	AxisFrameClass(const AxisFrameClass& other);
	//Copy Assignment Operator
	virtual AxisFrameClass& operator=(const AxisFrameClass& other);

	//Destructor
	~AxisFrameClass(void);
	
	//Renders the content of the shape
	virtual void Render(GLenum mode = GL_LINES);

	//Renders a grid in the planes
	void RenderGrid(int a_nOptions, float a_fSpacing = 1.0f);

protected:
	//Generate Points
	void GeneratePoints(void);
};

EXPIMP_TEMPLATE template class MyEngineDLL std::vector<AxisFrameClass>;
EXPIMP_TEMPLATE template class MyEngineDLL std::vector<AxisFrameClass*>;

}
#endif //__AXISFRAMECLASS_H_