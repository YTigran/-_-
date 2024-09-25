#ifndef CAESAR_H
#define CAESAR_H

#include <header.h>

class Caesar : public ISecure {
public:
	Caesar (int _offset = 3);
public:
	void set_offset (int _offset);
	int get_offset () const;

	str encrypt (const str& input) const override;
	str decrypt (const str& input) const override;
	void encrypt (str::iterator begin, str::iterator end) const override;
	void decrypt (str::iterator begin, str::iterator end) const override;
private:
	int offset;

	void _form (char_t& ch) const;
	void _deform (char_t& ch) const;
};

#endif // CAESAR_H