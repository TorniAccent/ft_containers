#pragma once

namespace ft {

	template<typename T, typename Container>
	Stack<T, Container>::Stack(const Container &container) {
		this->_container = container;
	}

	template<typename T, typename Container>
	bool Stack<T, Container>::empty() const {
		return _container.empty();
	}

	template<typename T, typename Container>
	size_t Stack<T, Container>::size() const {
		return _container.size();
	}

	template<typename T, typename Container>
	T &Stack<T, Container>::top() {
		return _container.back();
	}

	template<typename T, typename Container>
	const T &Stack<T, Container>::top() const {
		return _container.back();
	}

	template<typename T, typename Container>
	void Stack<T, Container>::push(const value_type &val) {
		_container.push_back(val);
	}

	template<typename T, typename Container>
	void Stack<T, Container>::pop() {
		_container.pop_back();
	}

	template<typename T, typename Container>
	void swap(Stack<T, Container> &x, Stack<T, Container> &y) {
		x._container.swap(y._container);
	}

	template<typename T, typename Container>
	bool operator==(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
		return lhs._container == rhs._container;
	}

	template<typename T, typename Container>
	bool operator!=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
		return lhs._container != rhs._container;
	}

	template<typename T, typename Container>
	bool operator<(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
		return lhs._container < rhs._container;
	}

	template<typename T, typename Container>
	bool operator>(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
		return lhs._container > rhs._container;
	}

	template<typename T, typename Container>
	bool operator<=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
		return lhs._container <= rhs._container;
	}

	template<typename T, typename Container>
	bool operator>=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
		return lhs._container >= rhs._container;
	}

}