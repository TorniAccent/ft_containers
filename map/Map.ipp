#pragma once

#include "Map.hpp"

/// private
namespace ft {

	/// Algorithms
	template < typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::map_node<key_type, mapped_type> *
	Map<Key, T, Compare, Allocator>::_get_begin_node() {
		map_node<key_type, mapped_type>	*tmp;

		tmp = this->_root;
		while (tmp->left->color != TAIL_COLOR && tmp->left->color != this->_null_node.color)
			tmp = tmp->left;
		return (tmp);
	}


	template < typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::map_node<key_type, mapped_type>	*
	Map<Key, T, Compare, Allocator>::_get_end_node() {
		map_node<key_type, mapped_type>	*tmp;

		tmp = this->_root;
		while (tmp->right->color != this->_null_node.color && tmp->right->color != TAIL_COLOR)
			tmp = tmp->right;
		return (tmp);
	}


	template < typename Key, typename T, typename Compare, typename Allocator>
	void
	Map<Key, T, Compare, Allocator>::_null_node_with_color(map_node<key_type, mapped_type> *node, Colors color) {
		node->color = color;
		node->left = NULL;
		node->right = NULL;
		node->root = NULL;
	}


	template < typename Key, typename T, typename Compare, typename Allocator>
	void
	Map<Key, T, Compare, Allocator>::_init(const key_compare& comp, const allocator_type& alloc) {
		this->_my_comp = comp;
		this->_my_alloc = alloc;
		this->_size = 0;
		this->_null_node_with_color(&this->_null_node, NON_COLOR);
		this->_root = &this->_null_node;
		this->_begin_node = new map_node<key_type, mapped_type>;
		this->_null_node_with_color(this->_begin_node, TAIL_COLOR);
		this->_end_node = new map_node<key_type, mapped_type>;
		this->_null_node_with_color(this->_end_node, TAIL_COLOR);
	}


	template < typename Key, typename T, typename Compare, typename Allocator>
	void
	Map<Key, T, Compare, Allocator>::_insertFix(map_node<key_type, mapped_type> *k) {
		map_node<key_type, mapped_type>	*tmp;

		while (k->root->color == RED) {
			if (k->root == k->root->root->right) {
				tmp = k->root->root->left;
				if (tmp->color == RED) {
					tmp->color = BLACK;
					k->root->color = BLACK;
					k->root->root->color = RED;
					k = k->root->root;
				}
				else {
					if (k == k->root->left) {
						k = k->root;
						this->rootRotate(k);
					}
					k->root->color = BLACK;
					k->root->root->color = RED;
					this->leftRotate(k->root->root);
				}
			}
			else {
				tmp = k->root->root->right;
				if (tmp->color == RED) {
					tmp->color = BLACK;
					k->root->color = BLACK;
					k->root->root->color = RED;
					k = k->root->root;
				}
				else {
					if (k == k->root->right) {
						k = k->root;
						this->leftRotate(k);
					}
					k->root->color = BLACK;
					k->root->root->color = RED;
					this->rootRotate(k->root->root);
				}
			}
			if (k == this->_root)
				break;
		}
		this->_root->color = BLACK;
	}


	template < typename Key, typename T, typename Compare, typename Allocator>
	void
	Map<Key, T, Compare, Allocator>::leftRotate(map_node<key_type, mapped_type> *x) {
		map_node<key_type, mapped_type> *y = x->right;

		x->right = y->left;
		if (y->left->color != this->_null_node.color)
			y->left->root = x;
		y->root = x->root;
		if (x->root == NULL)
			this->_root = y;
		else if (x == x->root->left)
			x->root->left = y;
		else
			x->root->right = y;
		y->left = x;
		x->root = y;
	}


	template < typename Key, typename T, typename Compare, typename Allocator>
	void
	Map<Key, T, Compare, Allocator>::rootRotate(map_node<key_type, mapped_type> *x) {
		map_node<key_type, mapped_type> *y = x->left;
		x->left = y->right;
		if (y->right->color != this->_null_node.color)
			y->right->root = x;
		y->root = x->root;
		if (x->root == NULL)
			this->_root = y;
		else if (x == x->root->right)
			x->root->right = y;
		else
			x->root->left = y;
		y->right = x;
		x->root = y;
	}


	template < typename Key, typename T, typename Compare, typename Allocator>
	void
	Map<Key, T, Compare, Allocator>::_linked_outside_nodes() {
		this->_begin_node->root = this->_get_begin_node();
		this->_begin_node->root->left = this->_begin_node;
		this->_end_node->root = this->_get_end_node();
		this->_end_node->root->right = this->_end_node;
	}


	template < typename Key, typename T, typename Compare, typename Allocator>
	map_node<key_type, mapped_type>	*
	Map<Key, T, Compare, Allocator>::_minimum(map_node<key_type, mapped_type> *node) {
		while (node->left->color != this->_null_node.color)
			node = node->left;
		return (node);
	}


	template < typename Key, typename T, typename Compare, typename Allocator>
	void
	Map<Key, T, Compare, Allocator>::_rbTransplant(map_node<key_type, mapped_type> *u, map_node<key_type, mapped_type> *v) {
		if (u->root == NULL)
			this->_root = v;
		else if (u == u->root->left)
			u->root->left = v;
		else
			u->root->right = v;
		v->root = u->root;
	}


	template < typename Key, typename T, typename Compare, typename Allocator>
	void
	Map<Key, T, Compare, Allocator>::_deleteFix(map_node<key_type, mapped_type> *x) {
		map_node<key_type, mapped_type>	*s;
		while (x != this->_root && (x->color == BLACK || x->color == this->_null_node.color || x->color == TAIL_COLOR) ) {
			if (x == x->root->left) {
				s = x->root->right;
				if (s->color == RED) {
					s->color = BLACK;
					x->root->color = RED;
					this->leftRotate(x->root);
					s = x->root->right;
				}
				if ( (s->left->color == BLACK || s->left->color == this->_null_node.color || s->left->color == TAIL_COLOR) &&
				(s->right->color == BLACK || s->right->color == this->_null_node.color || s->right->color == TAIL_COLOR) ) {
					s->color = RED;
					x = x->root;
				} else {
					if (s->right->color == BLACK || s->right->color == this->_null_node.color) {
						s->left->color = BLACK;
						s->color = RED;
						this->rootRotate(s);
						s = x->root->right;
					}
					s->color = x->root->color;
					x->root->color = BLACK;
					s->right->color = BLACK;
					this->leftRotate(x->root);
					x = this->_root;
				}
			} else {
				s = x->root->left;
				if (s->color == RED) {
					s->color = BLACK;
					x->root->color = RED;
					this->rootRotate(x->root);
					s = x->root->left;
				}
				if ( (s->left->color == BLACK || s->left->color == this->_null_node.color || s->left->color == TAIL_COLOR)
				&& (s->right->color == BLACK || s->right->color == this->_null_node.color) ) {
					s->color = RED;
					x = x->root;
				}
				else {
					if (s->left->color == BLACK || s->left->color == this->_null_node.color) {
						s->right->color = BLACK;
						s->color = RED;
						this->leftRotate(s);
						s = x->root->left;
					}

					s->color = x->root->color;
					x->root->color = BLACK;
					s->left->color = BLACK;
					this->rootRotate(x->root);
					x = this->_root;
				}
			}
		}
		x->color = BLACK;
	}


	template < typename Key, typename T, typename Compare, typename Allocator>
	void
	Map<Key, T, Compare, Allocator>::_delete_node(key_type data) {
		map_node<key_type, mapped_type>	*z;
		map_node<key_type, mapped_type>	*x, *y;
		int	y_orig_color;

		z = this->find(data)._p_data;
		if (z->color == TAIL_COLOR)
			return ;
		y = z;
		y_orig_color = y->color;
		if (z->left->color == this->_null_node.color || z->left->color == TAIL_COLOR) {
			x = z->right;
			this->_rbTransplant(z, z->right);
		}
		else if (z->right->color == this->_null_node.color || z->right->color == TAIL_COLOR) {
			x = z->left;
			this->_rbTransplant(z, z->left);
		}
		else {
			y = this->_minimum(z->right);
			y_orig_color = y->color;
			x = y->right;
			if (y->root == z)
				x->root = y;
			else {
				this->_rbTransplant(y, y->right);
				y->right = z->right;
				y->right->root = y;

			}
			this->_rbTransplant(z, y);
			y->left = z->left;
			y->left->root = y;
			y->color = z->color;
		}
		delete z;
		this->_size--;
		if (y_orig_color == BLACK && this->_size != 0)
			this->_deleteFix(x);
		if (this->_null_node.root != NULL)
			this->_null_node.root = NULL;
	}
}

/// public
namespace ft {

	/// Coplien's

	template <typename Key, typename T, typename Compare, typename Allocator>
	Map<Key, T, Compare, Allocator>::Map(const key_compare& comp, const allocator_type& alloc) {
		this->_init(comp, alloc);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	template <typename InputIterator>
	Map<Key, T, Compare, Allocator>::Map(InputIterator first, InputIterator last, const key_compare& comp, const allocator_type& alloc) {
		this->_init(comp, alloc);
		this->insert(first, last);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	Map<Key, T, Compare, Allocator>::Map(const Map& x) {
		this->_init(x._my_comp, x._my_alloc);
		this->_size = 0;
		if (this != &x)
			*this = x;
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	Map<Key, T, Compare, Allocator>::~Map() {
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	Map<Key, T, Compare, Allocator> & Map<Key, T, Compare, Allocator>::operator=(const Map& x) {
		this->clear();
		this->_my_comp = x._my_comp;
		this->_my_alloc = x._my_alloc;
		this->insert(x.begin(), x.end());
		return (*this);
	}

	/// Iterators

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::iterator
	Map<Key, T, Compare, Allocator>::begin() {
		return(iterator(this->_begin_node->root));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::const_iterator
	Map<Key, T, Compare, Allocator>::begin() const {
		return (const_iterator(this->_begin_node->root));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::iterator
	Map<Key, T, Compare, Allocator>::end() {
		return (iterator(this->_end_node));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::const_iterator
	Map<Key, T, Compare, Allocator>::end() const {
		return (const_iterator(this->_end_node));
	}
	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::reverse_iterator
	Map<Key, T, Compare, Allocator>::rbegin() {
		return (reverse_iterator(this->end()));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::const_reverse_iterator
	Map<Key, T, Compare, Allocator>::rbegin() const {
		return (reverse_iterator(this->end()));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::reverse_iterator
	Map<Key, T, Compare, Allocator>::rend() {
		return (reverse_iterator(this->begin()));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::const_reverse_iterator
	Map<Key, T, Compare, Allocator>::rend() const {
		return (reverse_iterator(this->begin()));
	}

	/// Capacity

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool
	Map<Key, T, Compare, Allocator>::empty() const {
		return (this->_size == 0);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::size_type
	Map<Key, T, Compare, Allocator>::size() const {
		return (this->_size);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::size_type
	Map<Key, T, Compare, Allocator>::max_size() const {
		return (std::numeric_limits<size_t>::max() / sizeof(map_node<key_type, mapped_type>));
	}

	/// Element access

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::mapped_type &
	Map<Key, T, Compare, Allocator>::operator[](const key_type& k) {
		iterator	res;

		if (this->_size == 0)
			res = this->insert(this->begin(), std::pair<key_type, mapped_type>(k, mapped_type()));
		res = this->find(k);
		if (res == this->end())
			res = this->insert(res, std::pair<key_type, mapped_type>(k, mapped_type()));

		return res->second;
	}

	/// Modifiers

	template <typename Key, typename T, typename Compare, typename Allocator>
	std::pair<iterator, bool>
	Map<Key, T, Compare, Allocator>::insert(const value_type& val) {
		map_node<key_type, mapped_type>	*x;
		map_node<key_type, mapped_type>	*y;

		x = this->_root;
		y = NULL;
		while (x->color != this->_null_node.color && x->color != TAIL_COLOR) {
			y = x;
			if (this->_my_comp(x->data.first, val.first))
				x = x->right;
			else if (this->_my_comp(val.first, x->data.first))
				x = x->left;
			else
				return (std::pair<iterator, bool>(iterator(x), false));
		}
		map_node<key_type, mapped_type>	*new_el = new map_node<key_type, mapped_type>;
		new_el->root = y;
		new_el->right = &this->_null_node;
		new_el->left = &this->_null_node;
		new_el->data = val;
		new_el->color = RED;

		this->_size++;

		if (y == NULL)
			this->_root = new_el;
		else if (this->_my_comp(new_el->data.first, y->data.first))
			y->left = new_el;
		else if (this->_my_comp(x->data.first, new_el->data.first))
			y->right = new_el;

		if (new_el->root == NULL) {
			new_el->color = BLACK;
			this->_linked_outside_nodes();
			return (std::pair<iterator, bool>(iterator(new_el), true));
		}
		if (new_el->root->root == NULL) {
			this->_linked_outside_nodes();
			return (std::pair<iterator, bool>(iterator(new_el), true));
		}
		this->_insertFix(new_el);
		this->_linked_outside_nodes();
		return (std::pair<iterator, bool>(iterator(new_el), true));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::iterator
	Map<Key, T, Compare, Allocator>::insert(iterator position, const value_type& val) {
		position = insert(val).first;
		return (position);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	template <typename InputIterator>
	void
	Map<Key, T, Compare, Allocator>::insert(InputIterator first, InputIterator last) {
		for (; first != last; first++)
			insert(*first);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	void
	Map<Key, T, Compare, Allocator>::erase(iterator position) {
		if (position != this->end())
			this->_delete_node(position->first);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::size_type
	Map<Key, T, Compare, Allocator>::erase(const key_type& k) {
		this->_delete_node(k);
		return (this->_size);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	void
	Map<Key, T, Compare, Allocator>::erase(iterator first, iterator last) {
		if (first == this->end())
			return ;
		iterator	next;

		next = ++first;
		first--;
		for (; first != last;) {
			this->_delete_node(first->first);
			first = next;
			next = ++first;
			first--;
		}
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	void
	Map<Key, T, Compare, Allocator>::swap (Map& x) {
		map_node<key_type, mapped_type>	*tmp_node, *tmp_begin, *tmp_end;
		size_type	tmp_size;

		tmp_begin = x._begin_node;
		tmp_end = x._end_node;
		tmp_node = x._root;
		tmp_size = x._size;
		x._begin_node = this->_begin_node;
		x._end_node = this->_end_node;
		x._root = this->_root;
		x._size = this->_size;
		this->_begin_node = tmp_begin;
		this->_end_node = tmp_end;
		this->_root = tmp_node;
		this->_size = tmp_size;
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	void
	Map<Key, T, Compare, Allocator>::clear() {
		for (; this->_size != 0;) {
			this->_delete_node(this->_root->data.first);
		}
		this->_begin_node->root = NULL;
		this->_end_node->root = NULL;
	}

	/// Observers

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::key_compare
	Map<Key, T, Compare, Allocator>::key_comp() const {
		return (key_compare());
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::value_compare
	Map<Key, T, Compare, Allocator>::value_comp() const {
		return (value_comp());
	}

	/// Operations

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::iterator
	Map<Key, T, Compare, Allocator>::find(const key_type& k) {
		map_node<key_type, mapped_type>	*tmp;

		tmp = this->_root;
		while (tmp->color != TAIL_COLOR && tmp->color != this->_null_node.color) {
			if (tmp->data.first == k)
				break ;
			else if (tmp->data.first < k)
				tmp = tmp->right;
			else
				tmp = tmp->left;
		}
		if (tmp->color == TAIL_COLOR || tmp->color == this->_null_node.color)
			return (iterator(this->end()));
		else
			return (iterator(tmp));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::const_iterator
	Map<Key, T, Compare, Allocator>::find(const key_type& k) const {
		map_node<key_type, mapped_type>	*tmp;

		tmp = this->_root;
		while (tmp->color != TAIL_COLOR && tmp->color != this->_null_node.color) {
			if (tmp->data.first == k)
				break ;
			else if (tmp->data.first < k)
				tmp = tmp->right;
			else
				tmp = tmp->left;
		}
		if (tmp->color == TAIL_COLOR || tmp->color == this->_null_node.color)
			return (const_iterator(this->end()));
		else
			return (const_iterator(tmp));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::size_type
	Map<Key, T, Compare, Allocator>::count(const key_type& k) const {
		if (find(k) != this->end())
			return (1);
		else
			return (0);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::iterator
	Map<Key, T, Compare, Allocator>::lower_bound(const key_type& k) {
		map_node<key_type, mapped_type>	*r = this->_root;
		iterator	res = this->end();

		while (r->color != this->_null_node.color && r->color != TAIL_COLOR) {
			if (!this->_my_comp(r->data.first, k)) {
				res = static_cast<iterator>(r);
				r = r->left;
			}
			else
				r = r->right;
		}
		return (res);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::const_iterator
	Map<Key, T, Compare, Allocator>::lower_bound(const key_type& k) const {
		map_node<key_type, mapped_type>	*r = this->_root;
		const_iterator	res = this->end();

		while (r->color != this->_null_node.color && r->color != TAIL_COLOR) {
			if (!this->_my_comp(r->data.first, k)) {
				res = static_cast<const_iterator>(r);
				r = r->left;
			}
			else
				r = r->right;
		}
		return (res);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::iterator
	Map<Key, T, Compare, Allocator>::upper_bound(const key_type& k) {
		map_node<key_type, mapped_type>	*r = this->_root;
		iterator	res = this->end();

		while (r->color != this->_null_node.color && r->color != TAIL_COLOR) {
			if (this->_my_comp(k, r->data.first)) {
				res = static_cast<iterator>(r);
				r = r->left;
			}
			else
				r = r->right;
		}
		return (res);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::const_iterator
	Map<Key, T, Compare, Allocator>::upper_bound(const key_type& k) const {
		map_node<key_type, mapped_type>	*r = this->_root;
		const_iterator	res = this->end();

		while (r->color != this->_null_node.color && r->color != TAIL_COLOR) {
			if (this->_my_comp(k, r->data.first)) {
				res = static_cast<const_iterator>(r);
				r = r->left;
			}
			else
				r = r->right;
		}
		return (res);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::std::pair<const_iterator,const_iterator>
	Map<Key, T, Compare, Allocator>::equal_range(const key_type& k) const {
		typedef std::pair<const_iterator, const_iterator> _p;

		const_iterator	res = this->end();
		map_node<key_type, mapped_type>	*r = this->_root;

		while (r->color != this->_null_node.color && r->color != TAIL_COLOR) {
			if (this->_my_comp(k, r->data.first)) {
				res = static_cast<const_iterator>(r);
				r = r->left;
			}
			else if (this->_my_comp(r->data.first, k))
				r = r->right;
			else {
				if (r->right->color != this->_null_node.color && r->right->color != TAIL_COLOR)
					return (_p(const_iterator(r), const_iterator(this->_minimum(r->right))));
				else
					return (_p(const_iterator(r), res));
			}
		}
		return (_p(res, res));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::std::pair<iterator,iterator>
	Map<Key, T, Compare, Allocator>::equal_range(const key_type& k) {
		typedef std::pair<iterator, iterator> _p;

		iterator	res = this->end();
		map_node<key_type, mapped_type>	*r = this->_root;

		while (r->color != this->_null_node.color && r->color != TAIL_COLOR) {
			if (this->_my_comp(k, r->data.first)) {
				res = static_cast<iterator>(r);
				r = r->left;
			}
			else if (this->_my_comp(r->data.first, k))
				r = r->right;
			else {
				if (r->right->color != this->_null_node.color && r->right->color != TAIL_COLOR)
					return (_p(iterator(r), iterator(this->_minimum(r->right))));
				else
					return (_p(iterator(r), res));
			}
		}
		return (_p(res, res));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	typename Map<Key, T, Compare, Allocator>::allocator_type
	Map<Key, T, Compare, Allocator>::get_allocator() const {
		return (allocator_type());
	}
}