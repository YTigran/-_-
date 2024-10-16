#include <file_sec_CUI.h>

File_sec_CUI::File_sec_CUI (int argc, char** argv) {
	if (argc != 3 && argc != 5)
		throw std::invalid_argument("The input is invalid");

	ISecure::str begin;
	ISecure::str end;

	act = argv[2];
	ISecure* sec = new Caesar(3);

	if (act != "encrypt" && act != "decrypt")
		std::invalid_argument("The command is not right");

	if (argc == 5) {
		begin = argv[3];
		end = argv[4];

		if (act == "decrypt") {
			begin = sec->encrypt(begin);
			end = sec->encrypt(end);
		}	
		file_sec = new File_sec(argv[1], begin.c_str(), end.c_str());
	}
	else
		file_sec = new File_sec(argv[1]);
}

File_sec_CUI::~File_sec_CUI () {
	delete file_sec;
}

void File_sec_CUI::operator() () {
	if (act == "encrypt")
		file_sec->encrypt();
	else if (act == "decrypt")
		file_sec->decrypt();
}