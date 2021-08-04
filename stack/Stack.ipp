#pragma once

namespace ft {

	template<typename T, typename Container>
	stack<T, Container>::stack(const Container &container) {
		this->_container = container;
	}

	template<typename T, typename Container>
	bool stack<T, Container>::empty() const {
		return _container.empty();
	}

	template<typename T, typename Container>
	size_t stack<T, Container>::size() const {
		return _container.size();
	}

	template<typename T, typename Container>
	T &stack<T, Container>::top() {
		return _container.back();
	}

	template<typename T, typename Container>
	const T &stack<T, Container>::top() const {
		return _container.back();
	}

	template<typename T, typename Container>
	void stack<T, Container>::push(const value_type &val) {
		_container.push_back(val);
	}

	template<typename T, typename Container>
	void stack<T, Container>::pop() {
		_container.pop_back();
	}

	template<typename T, typename Container>
	void swap(stack<T, Container> &x, stack<T, Container> &y) {
		x._container.swap(y._container);
	}

	template<typename T, typename Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs._container == rhs._container;
	}

	template<typename T, typename Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs._container != rhs._container;
	}

	template<typename T, typename Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs._container < rhs._container;
	}

	template<typename T, typename Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs._container > rhs._container;
	}

	template<typename T, typename Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs._container <= rhs._container;
	}

	template<typename T, typename Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs._container >= rhs._container;
	}

}