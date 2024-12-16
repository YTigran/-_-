#include <thread>
#include <iostream>
#include <mutex>
#include <atomic>

const int size = 10;
int arr[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void sum_of_elements (int start, int end, std::atomic<int>& res) {
	if (end > size || start < 0)
		throw std::out_of_range("Out range");
	while (start < end) {
		res += arr[start];
		++start;
	}
}


int main () {
	std::atomic<int> res{0};
	std::thread th(sum_of_elements, 0, 5, std::ref(res));
	std::thread th2(sum_of_elements, 5, size, std::ref(res));
	th.join();
	th2.join();
	std::cout << res.load() << std::endl;
}