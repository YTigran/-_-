#ifndef ISECURE_H
#define ISECURE_H

#include <string>

class ISecure {
public:
	using char_t = char;
	using str = std::basic_string<char_t>;

	virtual str encrypt (const str& input) const = 0;
	virtual str decrypt (const str& input) const = 0;
	virtual void encrypt (str::iterator begin, str::iterator end) const = 0;
	virtual void decrypt (str::iterator begin, str::iterator end) const = 0;
	virtual ~ISecure() = default;
};

#endif // ISECURE_H