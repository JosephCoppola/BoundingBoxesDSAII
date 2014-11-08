/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/07
*/
#ifndef __EXAMPLECLASS_H_
#define __EXAMPLECLASS_H_

#include "ME\system\SystemClass.h"

namespace MyEngine
{

//System Class
class MyEngineDLL ExampleClass
{
	int m_nData;
	std::vector<int> m_vData;

public:
	ExampleClass(void); // Constructor
	ExampleClass(ExampleClass const& other); //Copy Constructor
	ExampleClass& operator=(ExampleClass const& other); // Copy Assignment Operator
	~ExampleClass(void); // Destructor

	void Swap(ExampleClass& other); // Initialize variables

	int GetData(void);
	void SetData( int a_nData = 1);
	__declspec(property(get = GetData, put = SetData)) int Data;

	void SetDataOnVector(int a_nData);
	int& GetDataOnVector(int a_nIndex);
	
private:
	void Release(void); // Release Memory
	void Init(void); // Initialize variables
};

EXPIMP_TEMPLATE template class MyEngineDLL std::vector<ExampleClass>;
EXPIMP_TEMPLATE template class MyEngineDLL std::vector<ExampleClass*>;

}

#endif //__EXAMPLECLASS_H__