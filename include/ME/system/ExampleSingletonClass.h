/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/07
*/
#ifndef __EXAMPLESINGLETONCLASS_H_
#define __EXAMPLESINGLETONCLASS_H_

#include "ME\system\SystemClass.h"

namespace MyEngine
{

//System Class
class MyEngineDLL ExampleSingletonClass
{
	int m_nData;
	std::vector<int> m_vData;
public:
	static ExampleSingletonClass* GetInstance(); // Singleton accessor
	void ReleaseInstance(void); //Singleton Release

	int GetData(void);
	void SetData( int a_nData = 1);
	__declspec(property(get = GetData, put = SetData)) int Data;

	void SetDataOnVector(int a_nData);
	int& GetDataOnVector(int a_nIndex);

private:
	ExampleSingletonClass(void); // Constructor
	ExampleSingletonClass(ExampleSingletonClass const& other); //Copy Constructor
	ExampleSingletonClass& operator=(ExampleSingletonClass const& other); // Copy Assignment Operator
	~ExampleSingletonClass(void); // Destructor

	void Release(void); // Release Memory
	void Init(void); // Initialize variables
	
	static ExampleSingletonClass* m_pInstance; // Singleton
};

}

#endif //__EXAMPLECLASS_H__