#pragma once

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
		ft::Pair<Key, T>	data;
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

		void	_init_null_node() {
			this->_null_node.color = NON_COLOR;
			this->_null_node.left = NULL;
			this->_null_node.right = NULL;
			this->_null_node.root = NULL;
		}

	public:
		friend class Map<Key, T>;

		typedef ft::Pair<Key, T>				value_type;
		typedef ptrdiff_t 						difference_type;
		typedef ft::Pair<Key, T>*				pointer;
		typedef ft::Pair<Key, T>&				reference;
		typedef std::bidirectional_iterator_tag	iterator_category;

		MapIterator() {
			this->_init_null_node();
		}

		MapIterator(const MapIterator &iter) {
			this->_p_data = iter._p_data;
			this->_init_null_node();
		}


		MapIterator(map_node<Key, T> *node) {
			this->_p_data = node;
			this->_init_null_node();
		}

		MapIterator(map_node<Key, T> &node) {
			this->_p_data = node;
			this->_init_null_node();
		}

		MapIterator&	operator=(const MapIterator &iter) {
			this->_p_data = iter._p_data;
			this->_init_null_node();
			return (*this);
		}

		~MapIterator() {}

		bool			operator==(const MapIterator &iter) {
			if (this->_p_data == iter._p_data)
				return (true);
			else
				return (false);
		}

		bool			operator!=(const MapIterator &iter) {
			if (this->_p_data != iter._p_data)
				return (true);
			else
				return (false);
		}

		reference 		operator*() {
			return (this->_p_data->data);
		}

		pointer			operator->() {
			return (&this->_p_data->data);
		}

		MapIterator				&operator++() {
			map_node<Key, T>	*tmp;
			map_node<Key, T>	*tmp2;

			tmp = this->_p_data;
			if (tmp->right->color != this->_null_node.color) {
				tmp = tmp->right;
				if (tmp->color == TAIL_COLOR) {
					*this = tmp;
					return (*this);
				}
				while (tmp->left->color != this->_null_node.color)
					tmp = tmp->left;
			} else if (tmp->right->color == this->_null_node.color && tmp->root && tmp->data.first > tmp->root->data.first) {
				tmp2 = tmp->root;
				while (tmp->data.first > tmp2->data.first)
					tmp2 = tmp2->root;
				tmp = tmp2;
			} else if (tmp->right->color == this->_null_node.color && tmp->root && tmp->data.first < tmp->root->data.first) {
				tmp = tmp->root;
			} else if (tmp->right->color != this->_null_node.color)
				tmp = tmp->right;
			this->_p_data = tmp;
			return (*this);
		}

		MapIterator				operator++(int) {
			MapIterator	temp(this->_p_data);

			++(*this);
			return (temp);
		}

		MapIterator				&operator--() {
			map_node<Key, T>	*tmp;

			tmp = this->_p_data;
			if (tmp->color == TAIL_COLOR)
				tmp = tmp->root;
			else if (tmp->left->color != this->_null_node.color) {
				tmp = tmp->left;
				while (tmp->right->color != this->_null_node.color)
					tmp = tmp->right;
			}
			else if (tmp->left->color == this->_null_node.color && tmp->root && tmp->data.first > tmp->root->data.first) {
				tmp = tmp->root;
			}
			else if (tmp->left->color == this->_null_node.color && tmp->root && tmp->root->root) {
				while (tmp->root && tmp->data.first < tmp->root->data.first)
					tmp = tmp->root;
				tmp = tmp->root;
			}
			else if (tmp->left->color != this->_null_node.color)
				tmp = tmp->left;
			this->_p_data = tmp;
			return (*this);
		}

		MapIterator				operator--(int) {
			MapIterator	tmp(this->_p_data);
			--(*this);
			return (tmp);
		}
	};

	template <typename Key, typename T>
	class MapConstIterator: public MapIterator<Key, T> {
	public:
		typedef ft::Pair<Key, T>	value_type;
		typedef ptrdiff_t 	difference_type;
		typedef const ft::Pair<Key, T>*			pointer;
		typedef const ft::Pair<Key, T>&			reference;
		typedef std::bidirectional_iterator_tag	iterator_category;

		MapConstIterator(): MapIterator<Key, T>() {}

		MapConstIterator(const MapConstIterator &iter): MapIterator<Key, T>(iter) {}

		MapConstIterator(map_node<Key, T> *node) {
			this->_p_data = node;
			this->_init_null_node();
		}

		MapConstIterator(map_node<Key, T> &node) {
			this->_p_data = node;
			this->_init_null_node();
		}

		MapConstIterator&	operator=(const MapConstIterator &iter) {
			this->_p_data = iter._p_data;
			this->_init_null_node();
			return (*this);
		}

		~MapConstIterator() {}

		reference 		operator*() const {
			return (this->_p_data->data);
		}

		pointer			operator->() const {
			return (&this->_p_data->data);
		}
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

		ReverseIterator(): _curr() {}

		explicit ReverseIterator(iterator_type it): _curr(it) {}

		template <typename Iter>
		ReverseIterator(const ReverseIterator<Iter>& rev_it): _curr(rev_it.base()) {}

		ReverseIterator&	operator=(const ReverseIterator &iter) {
			this->_curr = iter.base();
			return (*this);
		}

		~ReverseIterator() {}

		iterator_type base() const {
			return (this->_curr);
		}

		reference operator*() const {
			Iterator	tmp(this->_curr);
			return (*--tmp);
		}

		ReverseIterator& operator++() {
			--this->_curr;
			return (*this);
		}

		ReverseIterator operator++(int) {
			ReverseIterator tmp(*this);
			--this->_curr;
			return tmp;
		}

		ReverseIterator& operator--() {
			++this->_curr;
			return (*this);
		}

		ReverseIterator operator--(int) {
			ReverseIterator tmp = *this;
			++this->_curr;
			return tmp;
		}

		pointer operator->() const {
			return &(operator*());
		}

		ReverseIterator	operator+ (difference_type n) const {
			return (ReverseIterator(this->_curr - n));
		}

		ReverseIterator&	operator+= (difference_type n) {
			this->_curr -= n;
			return (*this);
		}

		ReverseIterator	operator- (difference_type n) const {
			return (ReverseIterator(this->_curr + n));
		}

		ReverseIterator&	operator-= (difference_type n) {
			this->_curr += n;
			return (*this);
		}

		reference operator[] (difference_type n) const {
			return *(*this + n);
		}
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

#include "MapIterator.ipp"