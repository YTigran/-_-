#ifndef OPEN_EXCEPTION_H
#define OPEN_EXCEPTION_H

class Open_exception : public std::exception {
public:
	Open_exception (const std::string& _msg);
public:
	const char* what () const noexcept override;
private:
	std::string msg;
};

#endif // OPEN_EXCEPTION_H
