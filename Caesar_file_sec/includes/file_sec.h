#ifndef FILE_SEC_H
#define FILE_SEC_H

#include "header.h"

class File_sec {
public:
	File_sec (const char* _sfile_name, const ISecure::char_t* _begin = nullptr, const ISecure::char_t* _end = nullptr);
	void encrypt();
	void decrypt();
	~File_sec ();
private:
	int file_permissions;
	std::string dfile_name{"out.txt"};
	std::string sfile_name;
	std::ifstream sfile;
	ISecure* sec;
	ISecure::str ibuffer;
	ISecure::str tmp;
	std::size_t begin;
	std::size_t end;

	void _err (const char* msg);
};

#endif // FILE_SEC_H
