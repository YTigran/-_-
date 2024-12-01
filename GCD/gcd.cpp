#include <iostream>

int gcd (int a, int b) {
	if (a == 0)
		return b;
	return gcd(b % a, a);
}

int main () {
	int a, b;
	std::cout << "Input first operand: ";
	std::cin >> a;
	std::cout << "Input second operand: ";
	std::cin >> b;

	std::cout << "GCD(" << a << ", " << b << "): " << gcd(a, b) << std::endl;
}