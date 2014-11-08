/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/06
*/
#ifndef __STATECLASS_H_
#define __STATECLASS_H_

#include "ME\system\SystemClass.h"
#include <vector>

namespace MyEngine
{

class MyEngineDLL StateClass
{
	String m_sName;
	int m_nSequence;		//Sequence being played
	int m_nExits;
	bool m_bTransitionState;
	bool m_bRepeatSequence;	//marks
	std::vector<StateClass*> m_vpExit;
	
	void Swap(StateClass& other);
public:
	StateClass();	//Constructor
	StateClass( String a_sName, int a_nSequence = 0, bool a_bTransitionState = false, bool a_bRepeatSequence = false);
	StateClass(const StateClass& other);
	StateClass& operator=(const StateClass& other);
	~StateClass();	//Destructor

	void Init();		//Initialices variable values
	void Release();		//Releases the memory and deallocate space.

	void SetName(String a_sName);
	String GetName(void);
	__declspec(property(put = SetName, get = GetName)) String Name;

	void SetSequence(int a_nSequence);
	int GetSequence(void);
	__declspec(property(put = SetSequence, get = GetSequence)) int Sequence;

	void SetRepeatSequence(bool a_bRepeatSequence);
	bool GetRepeatSequence(void);
	__declspec(property(put = SetRepeatSequence, get = GetRepeatSequence)) bool RepeatSequence;

	int GetNumberOfExits(void);
	__declspec(property(get = GetNumberOfExists)) int Exits;

	int AddExit(StateClass* a_pState);

	int GetExitIndex(StateClass* a_pState);

	bool IsTransitionState(void);

	StateClass* GetAutoExit(void);

	StateClass* GetExit(int a_nIndex);
};

EXPIMP_TEMPLATE template class MyEngineDLL std::vector<StateClass>;
EXPIMP_TEMPLATE template class MyEngineDLL std::vector<StateClass*>;

}

#endif //__STATECLASS_H__