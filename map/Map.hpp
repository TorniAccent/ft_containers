#pragma once

# include <iostream>
# include <memory>

namespace ft {

	template  < typename Key,
				typename T,
				typename Compare = std::less<Key>,
				typename Allocator = std::allocator<ft::Pair<const Key, T> >
				>
	class Map;

	template <typename T1, typename T2>
	struct Pair;
}

# include "../iterator/MapIterator.hpp"

namespace ft {

	template < typename Key, typename T, typename Compare, typename Allocator>
	class Map {
	public:
		typedef 		 Key												key_type;
		typedef 		 T													mapped_type;
		typedef 		 ft::Pair<const key_type, mapped_type>				value_type;
		typedef 		 Compare											key_compare;
		typedef 		 Allocator											allocator_type;
		typedef	typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef typename ft::MapIterator<key_type, mapped_type>				iterator;
		typedef typename ft::MapConstIterator<key_type, mapped_type>		const_iterator;
		typedef typename ft::ReverseIterator<iterator>						reverse_iterator;
		typedef typename ft::ReverseIterator<const_iterator>				const_reverse_iterator;
		typedef 		 ptrdiff_t											difference_type;
		typedef 		 size_t												size_type;

		class value_compare;

	private:
		allocator_type						_my_alloc;
		key_compare							_my_comp;
		map_node<key_type, mapped_type>		*_root;
		map_node<key_type, mapped_type>		_null_node;
		map_node<key_type, mapped_type>		*_begin_node;
		map_node<key_type, mapped_type>		*_end_node;
		size_type							_size;

		map_node<key_type, mapped_type>	*_get_begin_node();
		map_node<key_type, mapped_type>	*_get_end_node();
		void	_null_node_with_color(map_node<key_type, mapped_type> *node, Colors color);
		void	_init(const key_compare& comp, const allocator_type& alloc);
		void	_insertFix(map_node<key_type, mapped_type> *k);
		void	leftRotate(map_node<key_type, mapped_type> *x);
		void	rootRotate(map_node<key_type, mapped_type> *x);
		void	_linked_outside_nodes();
		map_node<key_type, mapped_type>	*_minimum(map_node<key_type, mapped_type> *node);
		void	_rbTransplant(map_node<key_type, mapped_type> *u, map_node<key_type, mapped_type> *v);
		void	_deleteFix(map_node<key_type, mapped_type> *x);
		void	_delete_node(key_type data);

	public:

		/// Coplien's

		explicit Map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		template <typename InputIterator>
			Map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		Map(const Map& x);
		~Map();
		Map& operator=(const Map& x);

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

		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		/// Element access

		mapped_type& operator[] (const key_type& k);

		/// Modifiers

		ft::Pair<iterator, bool> insert(const value_type& val);
		iterator insert(iterator position, const value_type& val);
		template <typename InputIterator>
		void insert(InputIterator first, InputIterator last);
		void erase(iterator position);
		size_type erase(const key_type& k);
		void erase(iterator first, iterator last);
		void swap (Map& x);
		void clear();

		/// Observers
		
		key_compare key_comp() const;
		value_compare value_comp() const;

		/// Operations
		
		iterator find(const key_type& k);
		const_iterator find(const key_type& k) const;
		size_type count(const key_type& k) const;
		iterator lower_bound(const key_type& k);
		const_iterator lower_bound(const key_type& k) const;
		iterator upper_bound(const key_type& k);
		const_iterator upper_bound(const key_type& k) const;
		ft::Pair<iterator,iterator> equal_range(const key_type& k);
		ft::Pair<const_iterator,const_iterator> equal_range(const key_type& k) const;
		allocator_type get_allocator() const;

	};

	/// class value_compare

	template <typename Key, typename T, typename Compare, typename Allocator>
	class Map<Key, T, Compare, Allocator>::value_compare {
		friend class Map;
	protected:
		Compare comp;
		value_compare (Compare c) : comp(c) {}
	public:
		typedef bool 			result_type;
		typedef value_type 		first_argument_type;
		typedef value_type 		second_argument_type;
		bool operator() (const value_type& x, const value_type& y) const {
			return comp(x.first, y.first);
		}
	};
}

namespace ft {

	template <typename T1, typename T2>
	struct Pair {
		T1 first;
		T2 second;

		typename T1 first_type;
		typename T2 second_type;

		Pair() {
		}
		template <class T1, class T2>
		Pair(Pair<T1, T2> const & copy) : first(copy.first), second(copy.second) {
		}
		Pair(first_type const & a, second_type const & b) : first(a), second(b) {
		}
		~Pair {
		}
		Pair &operator=(Pair const & copy) {
			first = copy.first;
			second = copy.second;
			return *this;
		}

		template <typename T1, typename T2>
		bool operator== (Pair<T1,T2> const & lhs, Pair<T1,T2> const & rhs)
		{ return lhs.first==rhs.first && lhs.second==rhs.second; }

		template <typename T1, typename T2>
		bool operator!= (Pair<T1,T2> const & lhs, Pair<T1,T2> const & rhs)
		{ return !(lhs == rhs); }

		template <typename T1, typename T2>
		bool operator<  (Pair<T1,T2> const & lhs, Pair<T1,T2> const & rhs)
		{ return lhs.first < rhs.first || (!(lhs.first > rhs.first) && lhs.second < rhs.second); }

		template <typename T1, typename T2>
		bool operator<= (Pair<T1,T2> const & lhs, Pair<T1,T2> const & rhs)
		{ return !(rhs < lhs); }

		template <typename T1, typename T2>
		bool operator>  (Pair<T1,T2> const & lhs, Pair<T1,T2> const & rhs)
		{ return rhs < lhs; }

		template <typename T1, typename T2>
		bool operator>= (Pair<T1,T2> const & lhs, Pair<T1,T2> const & rhs)
		{ return !(lhs < rhs); }
	};

	template <class T1,class T2>
	Pair<T1,T2> make_pair(T1 x, T2 y) {
		return ( Pair<T1,T2>(x,y) );
	}

}

#include "Map.ipp"