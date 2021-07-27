#include <iostream>
#include "stack/Stack.hpp"

int main() {
	ft::Stack<int> ms0;
	ft::Stack<int> ms1;

	ms0.push(1);
	ms0.push(2);
	ms0.push(3);
	
	ft::swap(ms0, ms1);

	return 0;
}
