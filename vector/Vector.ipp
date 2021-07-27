#pragma once

namespace ft {

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

	template <typename T, class Allocator>
	typename Vector<T, Allocator>::size_type
		Vector<T, Allocator>::size() const {
			return (this->_size);
		}

	template <typename T, class Allocator>
	typename Vector<T, Allocator>::size_type
		Vector<T, Allocator>::max_size() const {
			return (std::numeric_limits<size_type>::max() / sizeof(value_type));
		}

	template <typename T, class Allocator>
	void
	    Vector<T, Allocator>::resize(size_type n,
										  value_type val) {
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

	template <typename T, class Allocator>
	typename Vector<T, Allocator>::size_type
	    Vector<T, Allocator>::capacity() const {
			return (this->_capacity);
		}

	template <typename T, class Allocator>
	bool
	    Vector<T, Allocator>::empty() const {
			return (!this->_size);
		}

	template <typename T, class Allocator>
	void
	    Vector<T, Allocator>::reserve(size_type n) {
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

	/// Modifiers

	template <typename T, class Allocator>
	template <typename InputIterator>
	void
		Vector<T, Allocator>::assign(InputIterator first, InputIterator last,
					typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type *) {
			clear();
			size_type n = 0;
			while (first != last) {
				n++;
				first++;
			}
			if (n > this->_capacity)
				reallocateData(n);
			this->_size = n;
			n = 0;
			while (first != last) {
				this->_alloc.construct(this->_data + n, *first);
				n++;
				first++;
			}
		}

	template <typename T, class Allocator>
	void
		Vector<T, Allocator>::assign(size_type n, const value_type &val) {
			clear();
			if (n > this->_capacity)
				reallocateData(n);
			this->_size = n;
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(this->_data + i, val);
		}

	template <typename T, class Allocator>
	void
		Vector<T, Allocator>::push_back(const value_type &val) {
			if (this->_capacity < this->_size + 1)
				reserve(this->_capacity * 2 == 0 ? 1 : this->_capacity * 2);
			this->_alloc.construct(this->_data + this->_size, val);
			this->_size++;
		}

	template <typename T, class Allocator>
	void
		Vector<T, Allocator>::pop_back() {
			if (!this->_size)
				return ;
			this->_alloc.destroy(this->_data + this->_size - 1);
			this->_size--;
		}

	template <typename T, class Allocator>
	typename Vector<T, Allocator>::iterator
		Vector<T, Allocator>::insert(iterator position, const value_type &val) {
			size_type pos = iteratorPos(position);
			if (this->_capacity < this->_size + 1)
				reserve(this->_capacity * 2 == 0 ? 1 : this->_capacity * 2);
			for (size_type i = this->_size - 1; i >= pos; i--) {
				if (i == (size_type) (0 - 1))
					break;
				value_type tmp = this->_data[i];
				this->_alloc.destroy(this->_data + i);
				this->_alloc.construct(this->_data + i + 1, tmp);
			}
			this->_alloc.construct(this->_data + pos, val);
			this->_size++;
			return (iterator(this->_data + pos));
		}

	template <typename T, class Allocator>
	void
		Vector<T, Allocator>::insert(iterator position, size_type n, const value_type &val) {
			size_type pos = iteratorPos(position);
			if (this->_capacity < this->_size + n)
				reserve(this->_capacity * 2 == 0 ? 1 : this->_capacity * 2);
			for (size_type i = this->_size - 1; i >= pos; i--) {
				if (i == (size_type) (0 - 1))
					break;
				value_type tmp = this->_data[i];
				this->_alloc.destroy(this->_data + i);
				this->_alloc.construct(this->_data + i + n, tmp);
			}
			for (size_type i = pos; i < pos + n; i++)
				this->_alloc.construct(this->_data + i, val);
			this->_size += n;
		}

	template <typename T, class Allocator>
	template <typename InputIterator>
	void
		Vector<T, Allocator>::insert(iterator position, InputIterator first, InputIterator last,
					typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type *) {
			size_type pos = iteratorPos(position);
			size_type n = 0;
			while (first != last) {
				n++;
				first++;
			}
			if (this->_capacity < this->_size + n)
				reserve(this->_capacity * 2 == 0 ? 1 : this->_capacity * 2);
			for (size_type i = this->_size - 1; i >= pos; i--) {
				if (i == (size_type) (0 - 1))
					break;
				value_type tmp = this->_data[i];
				this->_alloc.destroy(this->_data + i);
				this->_alloc.construct(this->_data + i + n, tmp);
			}
			n = 0;
			while (first != last) {
				this->_alloc.construct(this->_data + pos + n, *first);
				n++;
				first++;
			}
			this->_size += n;
		}

	template <typename T, class Allocator>
	typename Vector<T, Allocator>::iterator
		Vector<T, Allocator>::erase(iterator position) {
			size_type pos = iteratorPos(position);
			if (pos == this->_size)
				return (end());
			for (size_type i = pos; i < this->_size - 1; i++) {
				this->_alloc.destroy(this->_data + i);
				this->_alloc.construct(this->_data + i, this->_data[i + 1]);
			}
			this->_size--;
			return (iterator(this->_data + pos));
		}

	template <typename T, class Allocator>
	typename Vector<T, Allocator>::iterator
		Vector<T, Allocator>::erase(iterator first, iterator last) {
			size_type pos = iteratorPos(first);
			size_type n = 0;
			while (first != last) {
				n++;
				first++;
			}
			if (pos == this->_size)
				return (end());
			for (size_type i = pos; i < pos + n + 1; i++) {
				this->_alloc.destroy(this->_data + i);
				this->_alloc.construct(this->_data + i, this->_data[i + pos]);
			}
			this->_size -= n;
			return (iterator(this->_data + pos));
		}

	template <typename T, class Allocator>
	void
		Vector<T, Allocator>::swap(Vector &x) {
			T tmp = this->_data;
			this->_data = x._data;
			x._data = tmp;

			T tmp2 = this->_size;
			this->_size = x._size;
			x._size = tmp;

			T tmp3 = this->_capacity;
			this->_capacity = x._capacity;
			x._capacity = tmp;
		}

	template <typename T, class Allocator>
	void
		Vector<T, Allocator>::clear() {
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.destroy(this->_data + i);
			this->_size = 0;
		}

	/// Non-member function overloads

	template<class T, class Alloc>
	bool operator== (const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		for (size_t i = 0; i < lhs.size(); i++) {
			if (lhs[i] != rhs[i])
				return (false);
		}
		return (true);
	}

	template <class T, class Alloc>
	bool operator!= (const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs) {
		const Vector<T, Alloc> first1 = lhs.begin();
		const Vector<T, Alloc> last1 = lhs.end();
		const Vector<T, Alloc> first2 = rhs.begin();
		const Vector<T, Alloc> last2 = rhs.end();
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class T, class Alloc>
	bool operator<= (const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs) {
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs) {
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs) {
		return (!(lhs < rhs));
	}

	template<typename T, typename Alloc>
	void swap(Vector<T, Alloc>& x, Vector<T, Alloc>& y) {
		x.swap(y);
	}

}
