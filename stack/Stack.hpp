#pragma once
# include <iostream>
# include <deque>

namespace ft {

	template<typename T, typename Container = std::deque <T> >
	class stack;

	template<typename T, typename Container>
	void swap(stack<T, Container> &x, stack<T, Container> &y);
	template<typename T, typename Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs);
	template<typename T, typename Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs);
	template<typename T, typename Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs);
	template<typename T, typename Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs);
	template<typename T, typename Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs);
	template<typename T, typename Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs);

}

namespace ft {

	template<typename T, typename Container>
	class stack {
	public:
		typedef 		T value_type;
		typedef 		Container container_type;
		typedef 		size_t size_type;

		container_type _container;

	public:
		explicit stack(const container_type &container = container_type());

		bool empty() const;

		size_type size() const;

		value_type &top();

		const value_type &top() const;

		void push(const value_type &val);

		void pop();

		friend void swap <> (stack<T, Container> &x, stack<T, Container> &y);

		friend bool operator== <> (const stack<T, Container> &lhs, const stack<T, Container> &rhs);

		friend bool operator!= <> (const stack<T, Container> &lhs, const stack<T, Container> &rhs);

		friend bool operator<  <> (const stack<T, Container> &lhs, const stack<T, Container> &rhs);

		friend bool operator<= <> (const stack<T, Container> &lhs, const stack<T, Container> &rhs);

		friend bool operator>  <> (const stack<T, Container> &lhs, const stack<T, Container> &rhs);

		friend bool operator>= <> (const stack<T, Container> &lhs, const stack<T, Container> &rhs);

	};

}

# include "Stack.ipp"