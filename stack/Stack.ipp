#ifndef FT_CONTAINERS_STACK_IPP
#define FT_CONTAINERS_STACK_IPP

namespace ft {

	template<typename T, typename Container>
	stack<T, Container>::stack(const Container &container) {
		this->c = container;
	}

	template<typename T, typename Container>
	bool stack<T, Container>::empty() const {
		return c.empty();
	}

	template<typename T, typename Container>
	size_t stack<T, Container>::size() const {
		return c.size();
	}

	template<typename T, typename Container>
	T &stack<T, Container>::top() {
		return c.back();
	}

	template<typename T, typename Container>
	const T &stack<T, Container>::top() const {
		return c.back();
	}

	template<typename T, typename Container>
	void stack<T, Container>::push(const value_type &val) {
		c.push_back(val);
	}

	template<typename T, typename Container>
	void stack<T, Container>::pop() {
		c.pop_back();
	}

	template<typename T, typename Container>
	void swap(stack<T, Container> &x, stack<T, Container> &y) {
		x.c.swap(y.c);
	}

	template<typename T, typename Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.c == rhs.c;
	}

	template<typename T, typename Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.c != rhs.c;
	}

	template<typename T, typename Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.c < rhs.c;
	}

	template<typename T, typename Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.c > rhs.c;
	}

	template<typename T, typename Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.c <= rhs.c;
	}

	template<typename T, typename Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs.c >= rhs.c;
	}

}

#endif