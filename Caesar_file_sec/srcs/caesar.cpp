#include <caesar.h>

Caesar::Caesar (int _offset) {
	set_offset(_offset);
}

void Caesar::set_offset (int _offset) {
	if (_offset <= 0 || _offset >= 10)
		throw std::invalid_argument("Invalid offset");
	offset = _offset;
}

int Caesar::get_offset () const {
	return offset;
}

void Caesar::_form (char_t& ch) const {
	if (std::isspace(ch))
		return;

	int a = ch + offset;
	int start = 0;
	int end = 127;

	if (a > end) ch = (start - 1) + a - end;
	else ch += offset;
}

void Caesar::_deform (char_t& ch) const {
	if (std::isspace(ch))
		return;

	int a = ch - offset;
	int start = 0;
	int end = 127;

	if (a < start) ch = (end + 1) - (start - a);
	else ch -= offset;
}


ISecure::str Caesar::encrypt (const str& input) const {
	str res;

	std::for_each(input.begin(), input.end(), [&](char_t ch){
		_form(ch);
		res.push_back(ch);
	});

	return res;
}

ISecure::str Caesar::decrypt (const str& input) const {
	str res;

	std::for_each(input.begin(), input.end(), [&](char_t ch){
		_deform(ch);
		res.push_back(ch);
	});

	return res;
}

void Caesar::encrypt (str::iterator begin, str::iterator end) const {
	std::for_each(begin, end, [&](char_t& ch){
		_form(ch);
	});
}

void Caesar::decrypt (str::iterator begin, str::iterator end) const {
	std::for_each(begin, end, [&](char_t& ch){
		_deform(ch);
	});
}