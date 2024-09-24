#include <iostream>

int ft_gcd (int a, int b) {
	if (a == 0)
		return b;
	return ft_gcd(b % a, a);
}

int main () {
	int a = 18;
	int b = 12;

	std::cout << ft_gcd(a, b) << std::endl;
}