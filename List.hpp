#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include <iostream>
//#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class List
	{
	public:
		typedef 			T 								value_type;
		typedef 			Alloc							allocator_type;
		typedef typename 	allocator_type::reference		reference;
		typedef typename 	allocator_type::const_reference	const_reference;
		typedef typename 	allocator_type::pointer			pointer;
		typedef typename 	allocator_type::const_pointer	const_pointer;
		typedef typename 	allocator_type::size_type		size_type;
		typedef 			Iterator<value_type>			iterator;
		typedef 			Iterator<const value_type>		const_iterator;

		explicit	list();
					list(list const &l);
		explicit	list(size_type n, const value_type& val = value_type());
		template < typename InputIterator >
					list(InputIterator first, InputIterator second);
		template < typename U >
					list<U>(U n, U val);
					~list();
		list		&operator=(list const &l);

		iterator	begin();
		iterator	end();
		size_type	size() const;
		size_type	max_size() const;
		bool		empty();
		reference	front();
		reference	back();

		template < typename InputIterator >
		void		assign(InputIterator first, InputIterator second);
		template < typename U >
		void		assign(U n, U val);
		void		assign(size_type n, const value_type& val);
		void		push_back(const value_type &var);
		void		push_front(const value_type &var);
		void		pop_back();
		void		pop_front();
		iterator	insert(iterator position, const value_type& val);
		void		insert(iterator position, size_type n, const value_type& val);
		void		clear();

	private:
		template < typename U >
		class Node;

		template < typename U, typename Pointer = U*, typename Reference = U& >
		class Iterator;

		typedef Node<T> node;
		node	*_bilist;
		node	*_bilist_tail;
		size_t	_bilist_size;
	}
}


#endif //FT_CONTAINERS_LIST_HPP
