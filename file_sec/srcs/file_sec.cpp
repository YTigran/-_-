#include "file_sec.h"

void File_sec::_err (const char* msg) {
	remove(dfile_name.c_str());
	sfile.close();
	delete sec;
	throw std::invalid_argument(msg);
}

File_sec::File_sec (const char* _sfile_name, const ISecure::char_t* _begin, const ISecure::char_t* _end) : 
	file_permissions{0664},
	sfile(_sfile_name),
	sec{new Caesar(3)},
	sfile_name{_sfile_name}
{
	if (!sfile.is_open())
		_err("Can't open file");

	while (std::getline(sfile, tmp))
		ibuffer += tmp + '\n';

	if (_begin == nullptr || _end == nullptr) {
		begin = 0;
		end = ibuffer.length();
	}
	else {
		begin = ibuffer.find(_begin);
		end = ibuffer.find(_end) + strlen(_end);
	}
	
	if (begin == ISecure::str::npos || end == ISecure::str::npos)
		_err("Can't find the needed section");
}

File_sec::~File_sec () {
	sfile.close();
	delete sec;
}

void File_sec::encrypt () {
	std::ofstream dfile(dfile_name.c_str());
	chmod(dfile_name.c_str(), file_permissions);

	sec->encrypt(ibuffer.begin() + begin, ibuffer.begin() + end);

	remove(sfile_name.c_str());
	rename(dfile_name.c_str(), sfile_name.c_str());

	dfile << ibuffer;
}

void File_sec::decrypt () {
	std::ofstream dfile(dfile_name.c_str());
	chmod(dfile_name.c_str(), file_permissions);

	sec->decrypt(ibuffer.begin() + begin, ibuffer.begin() + end);

	remove(sfile_name.c_str());
	rename(dfile_name.c_str(), sfile_name.c_str());

	dfile << ibuffer;
}