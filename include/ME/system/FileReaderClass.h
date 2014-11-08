/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef __FILEREADERCLASS_H_
#define __FILEREADERCLASS_H_

#include "ME\system\SystemClass.h"

namespace MyEngine
{

class MyEngineDLL FileReaderClass
{
	SystemClass* m_pSystem;
	FILE* m_pFile;
public:
	String m_sLine;
private:
	void Init(void);
public:
	FileReaderClass(void);
	
	FileReaderClass(const FileReaderClass& other);
	FileReaderClass& operator=(const FileReaderClass& other);
	~FileReaderClass(void);
	
	void Release(void);

	void Rewind(void) const;

	MEErrors ReadFile(String a_sFileName);
	void CloseFile(void);
	MEErrors ReadNextLine(bool bSkipComments = true);
	MEErrors RemoveBlanks(char** szInput) const; //Modified by AndrewWilkinson88@gmail.com
	String GetFirstWord(bool a_bToUpper = false);

	String RetriveFileNameFromExplorer(LPCWSTR mFilter = L"Plain Text Files (*.txt)\0*.txt\0 All Files (*.*)\0*.*\0", LPCWSTR mDefaultExt = L"txt") const;
	char* IndicateFileNameOnExplorer(LPWSTR mSuggested = NULL, LPCWSTR mFilter = L"Plain Text Files (*.txt)\0*.txt\0 All Files (*.*)\0*.*\0", LPCWSTR mDefaultExt = L"txt") const;

	String GetFileNameAndExtension(String aFileName);
};

EXPIMP_TEMPLATE template class MyEngineDLL std::vector<FileReaderClass>;
EXPIMP_TEMPLATE template class MyEngineDLL std::vector<FileReaderClass*>;

}
#endif //_EMPTY_H
