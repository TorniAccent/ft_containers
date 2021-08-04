#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <memory>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include "VectorIterator.hpp"

namespace ft
{

	template <typename T, typename Allocator = std::allocator<T> >
	class vector {
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

		void reallocateData(size_type n);

		size_type iteratorPos(iterator i);

	public :

	/// Coplien's

		explicit vector(const allocator_type &alloc = allocator_type());

		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type());

		template<typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
			   typename std::enable_if<
			           !std::numeric_limits<InputIterator>::is_specialized
			           >::type * = 0);

		vector(const vector &x);

		vector &operator=(const vector &x);

		~vector();

	/// Iterators

		iterator begin();

		const_iterator begin() const;

		iterator end();

		const_iterator end() const;

		reverse_iterator rbegin();

		const_reverse_iterator rbegin() const;

		reverse_iterator rend();

		const_reverse_iterator rend() const;

	/// Capacity

		size_type size() const;

		size_type max_size() const;

		void resize(size_type n, value_type val = value_type());

		size_type capacity() const;

		bool empty() const;

		void reserve(size_type n);

	/// Element access

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

	/// Modifiers

		template<typename InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0);

		void assign(size_type n, const value_type &val);

		void push_back(const value_type &val);

		void pop_back();

		iterator insert(iterator position, const value_type &val);

		void insert(iterator position, size_type n, const value_type &val);

		template<typename InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0);

		iterator erase(iterator position);

		iterator erase(iterator first, iterator last);

		void swap(vector &x);

		void clear();
	};

	/// Non-member function overloads

	template<class T, class Alloc>
	bool operator== (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	template <class T, class Alloc>
	bool operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

	template<typename T, typename Alloc>
	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y);

}

#endif

#include "Vector.ipp"