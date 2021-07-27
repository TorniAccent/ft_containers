#include <iostream>
#include "stack/Stack.hpp"
#include "vector/Vector.hpp"
#include <vector>

using namespace ft;

int main() {

	/// stack test
//	{
//		ft::Stack<int> ms0;
//		ft::Stack<int> ms1;
//
//		ms0.push(1);
//		ms0.push(2);
//		ms0.push(3);
//
//		ft::swap(ms0, ms1);
//	}

	/// vector test
	{
#define ORIGINAL std::vector
#define IMPLEMENT ft::Vector
		{
			ORIGINAL<int> originial_vector;
			IMPLEMENT<int> implement_vector;
			originial_vector.push_back(3);
			originial_vector.push_back(4);
			implement_vector.push_back(3);
			implement_vector.push_back(4);
			IMPLEMENT<int>::iterator it_impl = implement_vector.begin();
			ORIGINAL<int>::iterator it_orig = originial_vector.begin();
			ORIGINAL<int>::reverse_iterator it_orig_end = originial_vector.rbegin();
			IMPLEMENT<int>::reverse_iterator it_impl_end = implement_vector.rbegin();
			std::cout << implement_vector.size() << std::endl;
			std::cout << originial_vector.size() << std::endl;

			std::cout << *it_impl_end << std::endl;

			std::cout << *it_impl << std::endl;
			std::cout << *it_orig_end << std::endl;
			std::cout << *it_orig << std::endl;

		}
		{
			std::vector<int> myvector;
			for (int i = 1; i <= 5; i++) myvector.push_back(i);

			std::cout << "myvector contains:";
			for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';

		}
		{
			ORIGINAL<int> foo(3, 100);
			ORIGINAL<int> bar(4, 50);
			std::swap(foo, bar);
			for (std::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
			for (std::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
			foo.swap(bar);
			for (std::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
			for (std::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		{
			std::vector<int> test(10, 11);
			try {
				test[-2143];
			} catch (std::exception &e) {
				std::cout << e.what() << std::endl;

			}

		}
	}
	return 0;
}
