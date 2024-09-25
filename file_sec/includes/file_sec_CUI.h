#ifndef FILE_SEC_CUI_H
#define FILE_SEC_CUI_H

#include "header.h"

class File_sec;

class File_sec_CUI {
public:
	File_sec_CUI (int argc, char** argv);
	~File_sec_CUI ();
public:
	void operator ()();
private:
	File_sec* file_sec;
	std::string act;
};

#endif // FILE_SEC_CUI_H