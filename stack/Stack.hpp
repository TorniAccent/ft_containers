#pragma once
# include <iostream>
# include <deque>

namespace ft {

	template<typename T, typename Container = std::deque <T> >
	class Stack;

	template<typename T, typename Container>
	void swap(Stack<T, Container> &x, Stack<T, Container> &y);
	template<typename T, typename Container>
	bool operator==(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);
	template<typename T, typename Container>
	bool operator!=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);
	template<typename T, typename Container>
	bool operator<(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);
	template<typename T, typename Container>
	bool operator<=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);
	template<typename T, typename Container>
	bool operator>(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);
	template<typename T, typename Container>
	bool operator>=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);

}

namespace ft {

	template<typename T, typename Container>
	class Stack {
	public:
		typedef 		T value_type;
		typedef 		Container container_type;
		typedef 		size_t size_type;

		container_type _container;

	public:
		explicit Stack(const container_type &container = container_type());

		bool empty() const;

		size_type size() const;

		value_type &top();

		const value_type &top() const;

		void push(const value_type &val);

		void pop();

		friend void swap <> (Stack<T, Container> &x, Stack<T, Container> &y);

		friend bool operator== <> (const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);

		friend bool operator!= <> (const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);

		friend bool operator<  <> (const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);

		friend bool operator<= <> (const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);

		friend bool operator>  <> (const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);

		friend bool operator>= <> (const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);

	};

}

# include "Stack.ipp"