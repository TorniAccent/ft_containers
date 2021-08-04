#ifndef FT_CONTAINERS_MAPITERATOR_IPP
#define FT_CONTAINERS_MAPITERATOR_IPP

namespace ft {

	/// Coplien's
	template <typename Key, typename T>
	MapIterator<Key, T>::MapIterator() {
		this->_init_null_node();
	}

	template <typename Key, typename T>
	MapIterator<Key, T>::MapIterator(const MapIterator &iter) {
		this->_p_data = iter._p_data;
		this->_init_null_node();
	}

	template <typename Key, typename T>
	MapIterator<Key, T>::MapIterator(map_node<Key, T> *node) {
		this->_p_data = node;
		this->_init_null_node();
	}

	template <typename Key, typename T>
	MapIterator<Key, T>::MapIterator(map_node<Key, T> &node) {
		this->_p_data = node;
		this->_init_null_node();
	}

	template <typename Key, typename T>
	MapIterator<Key, T>&	MapIterator<Key, T>::operator=(const MapIterator &iter) {
		this->_p_data = iter._p_data;
		this->_init_null_node();
		return (*this);
	}

	template <typename Key, typename T>
	MapIterator<Key, T>::~MapIterator() {
	}

	/// Operators
	template <typename Key, typename T>
	bool MapIterator<Key, T>::operator==(const MapIterator &iter) {
		if (this->_p_data == iter._p_data)
			return (true);
		else
			return (false);
	}

	template <typename Key, typename T>
	bool MapIterator<Key, T>::operator!=(const MapIterator &iter) {
		if (this->_p_data != iter._p_data)
			return (true);
		else
			return (false);
	}

	template <typename Key, typename T>
	typename MapIterator<Key, T>::reference MapIterator<Key, T>::operator*() {
		return (this->_p_data->data);
	}

	template <typename Key, typename T>
	typename MapIterator<Key, T>::pointer MapIterator<Key, T>::operator->() {
		return (&this->_p_data->data);
	}

	template <typename Key, typename T>
	MapIterator<Key, T> & MapIterator<Key, T>::operator++() {
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

	template <typename Key, typename T>
	MapIterator<Key, T> MapIterator<Key, T>::operator++(int) {
		MapIterator	temp(this->_p_data);

		++(*this);
		return (temp);
	}

	template <typename Key, typename T>
	MapIterator<Key, T> & MapIterator<Key, T>::operator--() {
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

	template <typename Key, typename T>
	MapIterator<Key, T> MapIterator<Key, T>::operator--(int) {
		MapIterator	tmp(this->_p_data);
		--(*this);
		return (tmp);
	}

	/// private
	template <typename Key, typename T>
	void MapIterator<Key, T>::_init_null_node() {
		this->_null_node.color = NON_COLOR;
		this->_null_node.left = NULL;
		this->_null_node.right = NULL;
		this->_null_node.root = NULL;
	}

}

namespace ft {

	/// Coplien's
	template <typename Key, typename T>
	MapConstIterator<Key, T>::MapConstIterator(): MapIterator<Key, T>() {
	}

	template <typename Key, typename T>
	MapConstIterator<Key, T>::MapConstIterator(const MapConstIterator &iter): MapIterator<Key, T>(iter) {}

	template <typename Key, typename T>
	MapConstIterator<Key, T>::MapConstIterator(map_node<Key, T> *node) {
		this->_p_data = node;
		this->_init_null_node();
	}

	template <typename Key, typename T>
	MapConstIterator<Key, T>::MapConstIterator(map_node<Key, T> &node) {
		this->_p_data = node;
		this->_init_null_node();
	}

	template <typename Key, typename T>
	MapConstIterator<Key, T>& MapConstIterator<Key, T>::operator=(const MapConstIterator &iter) {
		this->_p_data = iter._p_data;
		this->_init_null_node();
		return (*this);
	}

	template <typename Key, typename T>
	MapConstIterator<Key, T>::~MapConstIterator() {}

	/// Operators
	template <typename Key, typename T>
	typename MapConstIterator<Key, T>::reference MapConstIterator<Key, T>::operator*() const {
		return (this->_p_data->data);
	}

	template <typename Key, typename T>
	typename MapConstIterator<Key, T>::pointer MapConstIterator<Key, T>::operator->() const {
		return (&this->_p_data->data);
	}

}

namespace ft {

	/// Coplien's
	template <typename Iterator>
	ReverseIterator<Iterator>::ReverseIterator(): _curr() {
	}

	template <typename Iterator>
	ReverseIterator<Iterator>::ReverseIterator(iterator_type it): _curr(it) {
	}

	template <typename Iterator>
	template <typename Iter>
	ReverseIterator<Iterator>::ReverseIterator(const ReverseIterator<Iter>& rev_it): _curr(rev_it.base()) {
	}

	template <typename Iterator>
	ReverseIterator<Iterator>& ReverseIterator<Iterator>::operator=(const ReverseIterator &iter) {
		this->_curr = iter.base();
		return (*this);
	}

	template <typename Iterator>
	ReverseIterator<Iterator>::~ReverseIterator() {}

	template <typename Iterator>
	typename ReverseIterator<Iterator>::iterator_type ReverseIterator<Iterator>::base() const {
		return (this->_curr);
	}

	template <typename Iterator>
	typename ReverseIterator<Iterator>::reference ReverseIterator<Iterator>::operator*() const {
		Iterator	tmp(this->_curr);
		return (*--tmp);
	}

	template <typename Iterator>
	ReverseIterator<Iterator>& ReverseIterator<Iterator>::operator++() {
		--this->_curr;
		return (*this);
	}

	template <typename Iterator>
	ReverseIterator<Iterator> ReverseIterator<Iterator>::operator++(int) {
		ReverseIterator tmp(*this);
		--this->_curr;
		return tmp;
	}

	template <typename Iterator>
	ReverseIterator<Iterator>& ReverseIterator<Iterator>::operator--() {
		++this->_curr;
		return (*this);
	}

	template <typename Iterator>
	ReverseIterator<Iterator> ReverseIterator<Iterator>::operator--(int) {
		ReverseIterator tmp = *this;
		++this->_curr;
		return tmp;
	}

	template <typename Iterator>
	typename ReverseIterator<Iterator>::pointer ReverseIterator<Iterator>::operator->() const {
		return &(operator*());
	}

	template <typename Iterator>
	ReverseIterator<Iterator> ReverseIterator<Iterator>::operator+ (difference_type n) const {
		return (ReverseIterator(this->_curr - n));
	}

	template <typename Iterator>
	ReverseIterator<Iterator>& ReverseIterator<Iterator>::operator+= (difference_type n) {
		this->_curr -= n;
		return (*this);
	}

	template <typename Iterator>
	ReverseIterator<Iterator> ReverseIterator<Iterator>::operator- (difference_type n) const {
		return (ReverseIterator(this->_curr + n));
	}

	template <typename Iterator>
	ReverseIterator<Iterator>& ReverseIterator<Iterator>::operator-= (difference_type n) {
		this->_curr += n;
		return (*this);
	}

	template <typename Iterator>
	typename ReverseIterator<Iterator>::reference ReverseIterator<Iterator>::operator[] (difference_type n) const {
		return *(*this + n);
	}

}

#endif