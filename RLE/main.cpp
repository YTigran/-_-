#include <iostream>
#include <string>
#include <string.h>

using std::string;

class RLE {
public:
	static string encrypt(const string& text) {
		string res;
		int count = 1;

		for (char ch : text) {
			if (isdigit(ch))
				throw std::invalid_argument("The can't contain numbers");
		}

		for (int i = 0; i < text.length(); ++i) {
			if (i + 1 < text.length() && text[i] == text[i + 1])
				++count;
			else if (count != 1) {
				res += std::to_string(count);
				res.push_back(text[i - 1]);
				count = 1;
			}
			else
				res.push_back(text[i]);
		}
		return res;
	}

	static string decrypt(const string& text) {
		string res;
		int num;

		for (int i = 0; i < text.length(); ++i) {
			if (isdigit(text[i])) {
				num = __get_num(text, i);
				__fill_decr_str(res, num, text, i);
			}
			else
				res.push_back(text[i]);
		}
		return res;
	}
private:
	static int	__get_num (const string& text, int& i) {
		int res = 0;

		while (isdigit(text[i])) {
			res = res * 10 + (text[i] - '0');
			++i;
		}

		return res;
	}

	static void __fill_decr_str (string& text, int num, const string& src, int index) {
		while (num) {
			text.push_back(src[index]);
			--num;
		}
	}
};

int main () {
	string test = "Heeellllllllllllllllllloooooooooooo Worlddddd";
	string enc = RLE::encrypt(test);
	string decr = RLE::decrypt(enc);
	std::cout << enc << std::endl;
	std::cout << decr << std::endl;
}