#pragma once

namespace ft {

	typedef typename Vector<T, Allocator>::

	/// Coplien's

	template <typename T, typename Allocator>
	Vector<T, Allocator>::Vector(const allocator_type &alloc)
		: _data(NULL), _alloc(alloc), _size(0), _capacity(0) {
	}

	template <typename T, class Allocator>
	Vector<T, Allocator>::Vector(size_type n, const value_type &val,
	const allocator_type &alloc)
	: _data(NULL), _alloc(alloc), _size(0), _capacity(0) {assign(n, val); }

	template <typename T, class Allocator>
	template <typename InputIterator>
	Vector<T, Allocator>::Vector(InputIterator first, InputIterator last,
			const allocator_type &alloc,
			typename std::enable_if
		    <!std::numeric_limits<InputIterator>::is_specialized>::type *)
	: _data(NULL), _alloc(alloc), _size(0), _capacity(0) {
		assign(first, last);
	}

	template <typename T, class Allocator>
	Vector<T, Allocator>::Vector(const Vector &x)
	: _data(NULL), _alloc(x._alloc), _size(0), _capacity(0) {
		assign(x.begin(), x.end());
	}

	template <typename T, class Allocator>
	Vector<T, Allocator> &Vector<T, Allocator>::operator=(const Vector &x) {
		assign(x.begin(), x.end());
		return (*this);
	}

	template <typename T, class Allocator>
	Vector<T, Allocator>::~Vector() {
		clear();
		this->_alloc.deallocate(this->_data, this->_capacity);
	}

	/// Iterators

	template <typename T, class Allocator>
	typename Vector<T, Allocator>::iterator
	    Vector<T, Allocator>::begin() {
	    	return (iterator(this->_data));
	    }

	template <typename T, class Allocator>
	typename Vector<T, Allocator>::const_iterator
	    Vector<T, Allocator>::begin() const {
	    	return (const_iterator(this->_data));
	    }

	template <typename T, class Allocator>
	typename Vector<T, Allocator>::iterator
	    Vector<T, Allocator>::end() {
	    	return (iterator(this->_data + this->_size));
	    }

	template <typename T, class Allocator>
	typename Vector<T, Allocator>::const_iterator
	    Vector<T, Allocator>::end() const {
	    	return (const_iterator(this->_data + this->_size));
	    }

	template <typename T, class Allocator>
	typename Vector<T, Allocator>::reverse_iterator
	    Vector<T, Allocator>::rbegin() {
	    	return (reverse_iterator(this->_data + this->_size - 1));
	    }

	template <typename T, class Allocator>
	typename Vector<T, Allocator>::const_reverse_iterator
	    Vector<T, Allocator>::rbegin() const {
	    	return (const_reverse_iterator(this->_data + this->_size - 1));
	    }

	template <typename T, class Allocator>
	typename Vector<T, Allocator>::reverse_iterator
	    Vector<T, Allocator>::rend() {
	    	return (reverse_iterator(this->_data - 1));
	    }

	template <typename T, class Allocator>
	typename Vector<T, Allocator>::const_reverse_iterator
	    Vector<T, Allocator>::rend() const {
	    	return (const_reverse_iterator(this->_data - 1));
	    }

	/// Capacity

	size_type size() const {return (this->_size); }

	size_type max_size() const {return (std::numeric_limits<size_type>::max() / sizeof(value_type)); }

	void resize(size_type n, value_type val = value_type()) {
		if (n <= this->_size) {
			for (size_type i = n; i < this->_size; i++)
				this->_alloc.destroy(this->_data + i);
		}
		else {
			if (n > this->_capacity)
				reserve((n > this->_capacity * 2) ? n : this->_capacity * 2);
			for (size_type i = this->_size; i < n; i++)
				this->_alloc.construct(this->_data + i, val);
		}
		this->_size = n;
	}

	size_type capacity() const {return (this->_capacity); }

	bool empty() const {return (!this->_size); }

	void reserve(size_type n) {
		if (n <= this->_capacity)
			return ;
		pointer newData = this->_alloc.allocate(n);
		for (size_type i = 0; i < this->_size; i++)
			this->_alloc.construct(newData + i, this->_data[i]);
		for (size_type i = 0; i < this->_size; i++)
			this->_alloc.destroy(this->_data + i);
		if (this->_capacity)
			this->_alloc.deallocate(this->_data, this->_capacity);
		this->_capacity = n;
		this->_data = newData;
	}

}