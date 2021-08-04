#ifndef FT_CONTAINERS_MAPITERATOR_HPP
#define FT_CONTAINERS_MAPITERATOR_HPP

# include <iostream>
# include <memory>

namespace ft {

	enum Colors {
		RED,
		BLACK,
		NON_COLOR,
		TAIL_COLOR,
		};
	
	template <typename Key, typename T>
	struct map_node;
	
	template <typename Key, typename T>
	class MapIterator;

	template <typename Key, typename T>
	class MapConstIterator;

	template <typename Iterator>
	class ReverseIterator;

}

namespace ft {

	template <typename Key, typename T>
	struct map_node {
		ft::pair<Key, T>	data;
		Colors				color;
		map_node			*left;
		map_node			*right;
		map_node			*root;
	};

	template <typename Key, typename T>
	class MapIterator {
	protected:
		map_node<Key, T>	*_p_data;
		map_node<Key, T>	_null_node;

		void	_init_null_node();

	public:
		friend class map<Key, T>;

		typedef ft::pair<Key, T>				value_type;
		typedef ptrdiff_t 						difference_type;
		typedef ft::pair<Key, T>*				pointer;
		typedef ft::pair<Key, T>&				reference;
		typedef std::bidirectional_iterator_tag	iterator_category;

		MapIterator();
		MapIterator(const MapIterator &iter);
		MapIterator(map_node<Key, T> *node);
		MapIterator(map_node<Key, T> &node);
		MapIterator&	operator=(const MapIterator &iter);
		~MapIterator();

		bool			operator==(const MapIterator &iter);
		bool			operator!=(const MapIterator &iter);
		reference 		operator*();
		pointer			operator->();
		MapIterator				&operator++();
		MapIterator				operator++(int);
		MapIterator				&operator--();
		MapIterator				operator--(int);
	};

	template <typename Key, typename T>
	class MapConstIterator: public MapIterator<Key, T> {
	public:
		typedef ft::pair<Key, T>	value_type;
		typedef ptrdiff_t 	difference_type;
		typedef const ft::pair<Key, T>*			pointer;
		typedef const ft::pair<Key, T>&			reference;
		typedef std::bidirectional_iterator_tag	iterator_category;

		MapConstIterator();
		MapConstIterator(const MapConstIterator &iter);
		MapConstIterator(map_node<Key, T> *node);
		MapConstIterator(map_node<Key, T> &node);
		MapConstIterator&	operator=(const MapConstIterator &iter);
		~MapConstIterator();

		reference 		operator*() const;
		pointer			operator->() const;
	};

	template <typename Iterator>
	class ReverseIterator {
	protected:
		Iterator	_curr;

	public:
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef 		 Iterator						iterator_type;
		typedef typename Iterator::iterator_category	iterator_category;

		ReverseIterator();
		explicit ReverseIterator(iterator_type it);
		template <typename Iter>
		explicit ReverseIterator(const ReverseIterator<Iter>& rev_it);
		ReverseIterator&	operator=(const ReverseIterator &iter);
		~ReverseIterator();

		iterator_type base() const;
		reference operator*() const;
		ReverseIterator& operator++();
		ReverseIterator operator++(int);
		ReverseIterator& operator--();
		ReverseIterator operator--(int);
		pointer operator->() const;
		ReverseIterator	operator+ (difference_type n) const;
		ReverseIterator&	operator+= (difference_type n);
		ReverseIterator	operator- (difference_type n) const;
		ReverseIterator&	operator-= (difference_type n);
		reference operator[] (difference_type n) const;
	};

	template <typename Iterator>
	bool operator==(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator>
	bool operator!= (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename Iterator>
	bool operator<  (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template <typename Iterator>
	bool operator<= (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <typename Iterator>
	bool operator>  (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template <typename Iterator>
	bool operator>= (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <typename Iterator>
	ReverseIterator<Iterator>	operator+(typename ReverseIterator<Iterator>::difference_type n,
		const ReverseIterator<Iterator>& rev_it) {
		return ReverseIterator<Iterator>(rev_it.base() - n);
	}

	template <typename Iterator>
	typename ReverseIterator<Iterator>::difference_type operator- (const ReverseIterator<Iterator>& lhs,
		const ReverseIterator<Iterator>& rhs) {
		return (rhs.base() - lhs.base());
	}
}

#endif

#include "MapIterator.ipp"