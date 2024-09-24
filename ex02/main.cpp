#include <iostream>
#include <unordered_map>
#include <random>
#include <string>
#include <algorithm>

using std::unordered_map;
using std::string;

class Simple_swap_method {
public:
	Simple_swap_method() : alphabet{"abcdefghijklmnopqrstuvwxyz"}, key{alphabet} {
		std::random_device rd;
		std::mt19937 rand(rd());

		std::shuffle(key.begin(), key.end(), rand);

		for (int i = 0; i < alphabet.length(); ++i) {
			encr.insert({alphabet[i], key[i]});
			decr.insert({key[i], alphabet[i]});
		}
	}

	string encrypt (const string& input) {
		string res(input.length(), 0);

		for (int i = 0; i < input.length(); ++i) {
			res[i] = encr[input[i]];
		}

		return res;
	}

	string decrypt (const string& input) {
		string res(input.length(), 0);

		for (int i = 0; i < input.length(); ++i) {
			res[i] = decr[input[i]];
		}

		return res;
	}
private:
	std::unordered_map<char, char> encr;
	std::unordered_map<char, char> decr;
	std::string alphabet;
	std::string key;
};

int main () {
	Simple_swap_method secure;

	std::string input = "hello";
	std::string res1 = secure.encrypt(input);
	std::string res2 = secure.decrypt(res1);

	std::cout << "input: " << input << std::endl;
	std::cout << "encryped: " << res1 << std::endl;
	std::cout << "decryped: " << res2 << std::endl;
}
