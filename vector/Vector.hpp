#pragma once

#include <memory>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include "VectorIterator.hpp"

namespace ft
{

	template <typename T, class Allocator = std::allocator<T> >
	class Vector {
	public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef std::size_t									size_type;
		typedef std::ptrdiff_t								difference_type;
		typedef value_type &								reference;
		typedef const value_type &							const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef VectorIterator<value_type>					iterator;
		typedef VectorReverseIterator<value_type>			reverse_iterator;
		typedef VectorConstIterator<value_type>				const_iterator;
		typedef VectorConstReverseIterator<value_type>		const_reverse_iterator;
	private :
		pointer			_data;
		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;

		void reallocateData(size_type n) {
			if (this->_capacity)
				this->_alloc.deallocate(this->_data, this->_capacity);
			this->_capacity = n;
			this->_data = this->_alloc.allocate(this->_capacity);
		}

		size_type iteratorPos(iterator i) {
			if (i == iterator(NULL))
				return (0);
			size_type pos = 0;
			iterator it = begin();
			while (it != end()) {
				if (it == i)
					return (pos);
				pos++;
				it++;
			}
			return (pos);
		}

	public :


		explicit Vector(const allocator_type &alloc = allocator_type())
				: _data(NULL), _alloc(alloc), _size(0), _capacity(0) {}

		explicit Vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
				: _data(NULL), _alloc(alloc), _size(0), _capacity(0) {assign(n, val); }

		template<typename InputIterator>
		Vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
			   typename std::enable_if<
			           !std::numeric_limits<InputIterator>::is_specialized
			           >::type * = 0)
				: _data(NULL), _alloc(alloc), _size(0), _capacity(0) {assign(first, last); }

		Vector(const Vector &x)
				: _data(NULL), _alloc(x._alloc), _size(0), _capacity(0) {assign(x.begin(), x.end()); }

		Vector &operator=(const Vector &x) {
			assign(x.begin(), x.end());
			return (*this);
		}

		~Vector() {
			clear();
			this->_alloc.deallocate(this->_data, this->_capacity);
		}

		iterator begin() {return (iterator(this->_data)); }

		const_iterator begin() const {return (const_iterator(this->_data)); }

		iterator end() {return (iterator(this->_data + this->_size)); }

		const_iterator end() const {return (const_iterator(this->_data + this->_size)); }

		reverse_iterator rbegin() {return (reverse_iterator(this->_data + this->_size - 1)); }

		const_reverse_iterator rbegin() const {return (const_reverse_iterator(this->_data + this->_size - 1)); }

		reverse_iterator rend() {return (reverse_iterator(this->_data - 1)); }

		const_reverse_iterator rend() const {return (const_reverse_iterator(this->_data - 1)); }

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

		reference operator[] (size_type n) { return (this->_data[n]); }

		const_reference operator[] (size_type n) const { return (this->_data[n]); }

		reference at(size_type n) {
			if (n > this->_size - 1)
				throw std::out_of_range("Vector");
			return (this->_data[n]);
		}

		const_reference at(size_type n) const {
			if (n > this->_size - 1)
				throw std::out_of_range("Vector");
			return (this->_data[n]);
		}

		reference front() { return (this->_data[0]); }

		const_reference front() const {return (this->_data[0]); }

		reference back() {return (this->_data[this->_size - 1]); }

		const_reference back() const {return (this->_data[this->_size - 1]); }

		template<typename InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0) {
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

		void assign(size_type n, const value_type &val) {
			clear();
			if (n > this->_capacity)
				reallocateData(n);
			this->_size = n;
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(this->_data + i, val);
		}

		void push_back(const value_type &val) {
			if (this->_capacity < this->_size + 1)
				reserve(this->_capacity * 2 == 0 ? 1 : this->_capacity * 2);
			this->_alloc.construct(this->_data + this->_size, val);
			this->_size++;
		}

		void pop_back() {
			if (!this->_size)
				return ;
			this->_alloc.destroy(this->_data + this->_size - 1);
			this->_size--;
		}

		iterator insert(iterator position, const value_type &val) {
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

		void insert(iterator position, size_type n, const value_type &val) {
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

		template<typename InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0) {
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

		iterator erase(iterator position) {
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

		iterator erase(iterator first, iterator last) {
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

		void swap(Vector &x) {
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

		void clear() {
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.destroy(this->_data + i);
			this->_size = 0;
		}
	};

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
	bool operator!= (const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)
	{ return (!(lhs == rhs)); }

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
	bool operator<= (const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)
	{ return (!(rhs < lhs)); }

	template <class T, class Alloc>
	bool operator>  (const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)
	{ return (rhs < lhs); }

	template <class T, class Alloc>
	bool operator>= (const Vector<T, Alloc>& lhs, const Vector<T, Alloc>& rhs)
	{ return (!(lhs < rhs)); }

	template<typename T, typename Alloc>
	void swap(Vector<T, Alloc>& x, Vector<T, Alloc>& y)
	{ x.swap(y); }

}
