#include <header.h>

Open_exception::Open_exception (const std::string& _msg) : msg(_msg) {}

const char* Open_exception::what () const noexcept {
	return msg.c_str();
}