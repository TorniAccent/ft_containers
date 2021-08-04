#ifndef FT_CONTAINERS_VECTORITERATOR_IPP
#define FT_CONTAINERS_VECTORITERATOR_IPP

namespace ft {

	template <typename T>
	VectorIterator<T>::VectorIterator(pointer ptr) : _ptr(ptr) {
	}

	template <typename T>
	VectorIterator<T>::VectorIterator(const VectorIterator &it) : _ptr(it._ptr) {
	}

	template <typename T>
	VectorIterator<T> &VectorIterator<T>::operator=(const VectorIterator &it) {
		this->_ptr = it._ptr;
		return (*this);
	}

	template <typename T>
	VectorIterator<T>::~VectorIterator() {
	}

	template <typename T>
	bool VectorIterator<T>::operator==(const VectorIterator &it) const {
		return (this->_ptr == it._ptr);
	}

	template <typename T>
	bool VectorIterator<T>::operator!=(const VectorIterator &it) const {
		return (!(*this == it));
	}

	template <typename T>
	typename VectorIterator<T>::reference VectorIterator<T>::operator*() {
		return (*this->_ptr);
	}

	template <typename T>
	typename VectorIterator<T>::pointer VectorIterator<T>::operator->() {
		return (this->_ptr);
	}

	template <typename T>
	VectorIterator<T> &VectorIterator<T>::operator++() {
		this->_ptr++;
		return (*this);
	}

	template <typename T>
	VectorIterator<T> VectorIterator<T>::operator++(int) {
		VectorIterator it(*this);
		this->_ptr++;
		return (it);
	}

	template <typename T>
	VectorIterator<T> &VectorIterator<T>::operator--() {
		this->_ptr--;
		return (*this);
	}

	template <typename T>
	VectorIterator<T> VectorIterator<T>::operator--(int) {
		VectorIterator it(*this);
		this->_ptr--;
		return (it);
	}

	template <typename T>
	VectorIterator<T> VectorIterator<T>::operator+(size_type n) const {
		return (VectorIterator(this->_ptr + n));
	}

	template <typename T>
	VectorIterator<T> VectorIterator<T>::operator-(size_type n) const {
		return (VectorIterator(this->_ptr - n));
	}

	template <typename T>
	bool VectorIterator<T>::operator<(const VectorIterator &it) const {
		return (this->_ptr < it._ptr);
	}

	template <typename T>
	bool VectorIterator<T>::operator>(const VectorIterator &it) const {
		return (it < *this);
	}

	template <typename T>
	bool VectorIterator<T>::operator<=(const VectorIterator &it) const {
		return (!(it < *this));
	}

	template <typename T>
	bool VectorIterator<T>::operator>=(const VectorIterator &it) const {
		return (!(*this < it));
	}

	template <typename T>
	VectorIterator<T> & VectorIterator<T>::operator+=(size_type n) {
		this->_ptr += n;
		return (*this);
	}

	template <typename T>
	VectorIterator<T> & VectorIterator<T>::operator-=(size_type n) {
		this->_ptr -= n;
		return (*this);
	}

	template <typename T>
	typename VectorIterator<T>::reference VectorIterator<T>::operator[](size_type n) {
		return (*(this->_ptr + n));
	}

}

namespace ft {

	template <typename T>
	VectorReverseIterator<T>::VectorReverseIterator(pointer ptr) : _ptr(ptr) {
	}

	template <typename T>
	VectorReverseIterator<T>::VectorReverseIterator(const VectorReverseIterator &it) : _ptr(it._ptr) {
	}

	template <typename T>
	VectorReverseIterator<T> &VectorReverseIterator<T>::operator=(const VectorReverseIterator &it) {
		this->_ptr = it._ptr;
		return (*this);
	}

	template <typename T>
	VectorReverseIterator<T>::~VectorReverseIterator() {
	}

	template <typename T>
	bool VectorReverseIterator<T>::operator==(const VectorReverseIterator &it) const {
		return (this->_ptr == it._ptr);
	}

	template <typename T>
	bool VectorReverseIterator<T>::operator!=(const VectorReverseIterator &it) const {
		return (!(*this == it));
	}

	template <typename T>
	typename VectorReverseIterator<T>::reference VectorReverseIterator<T>::operator*() {
		return (*this->_ptr);
	}

	template <typename T>
	typename VectorReverseIterator<T>::pointer VectorReverseIterator<T>::operator->() {
		return (this->_ptr);
	}

	template <typename T>
	VectorReverseIterator<T> &VectorReverseIterator<T>::operator++() {
		this->_ptr++;
		return (*this);
	}

	template <typename T>
	VectorReverseIterator<T> VectorReverseIterator<T>::operator++(int) {
		VectorReverseIterator it(*this);
		this->_ptr++;
		return (it);
	}

	template <typename T>
	VectorReverseIterator<T> &VectorReverseIterator<T>::operator--() {
		this->_ptr--;
		return (*this);
	}

	template <typename T>
	VectorReverseIterator<T> VectorReverseIterator<T>::operator--(int) {
		VectorReverseIterator it(*this);
		this->_ptr--;
		return (it);
	}

	template <typename T>
	VectorReverseIterator<T> VectorReverseIterator<T>::operator+(size_type n) const {
		return (VectorReverseIterator(this->_ptr + n));
	}

	template <typename T>
	VectorReverseIterator<T> VectorReverseIterator<T>::operator-(size_type n) const {
		return (VectorReverseIterator(this->_ptr - n));
	}

	template <typename T>
	bool VectorReverseIterator<T>::operator<(const VectorReverseIterator &it) const {
		return (this->_ptr < it._ptr);
	}

	template <typename T>
	bool VectorReverseIterator<T>::operator>(const VectorReverseIterator &it) const {
		return (it < *this);
	}

	template <typename T>
	bool VectorReverseIterator<T>::operator<=(const VectorReverseIterator &it) const {
		return (!(it < *this));
	}

	template <typename T>
	bool VectorReverseIterator<T>::operator>=(const VectorReverseIterator &it) const {
		return (!(*this < it));
	}

	template <typename T>
	VectorReverseIterator<T> & VectorReverseIterator<T>::operator+=(size_type n) {
		this->_ptr += n;
		return (*this);
	}

	template <typename T>
	VectorReverseIterator<T> & VectorReverseIterator<T>::operator-=(size_type n) {
		this->_ptr -= n;
		return (*this);
	}

	template <typename T>
	typename VectorReverseIterator<T>::reference VectorReverseIterator<T>::operator[](size_type n) {
		return (*(this->_ptr + n));
	}

}

namespace ft {
	
	template <typename T>
	VectorConstIterator<T>::VectorConstIterator(pointer ptr) {
		this->_ptr = ptr;
	}

	template <typename T>
	VectorConstIterator<T>::VectorConstIterator(const VectorIterator<T>& it) {
		this->_ptr = it._ptr;
	}

	template <typename T>
	VectorConstIterator<T> & VectorConstIterator<T>::operator= (const VectorIterator<T>& it) {
		this->_ptr = it._ptr;
		return (*this);
	}

	template <typename T>
	VectorConstIterator<T>::~VectorConstIterator() {
	}

	template <typename T>
	typename VectorConstIterator<T>::const_reference VectorConstIterator<T>::operator* () const {
		return (*(this->_ptr));
	}

	template <typename T>
	typename VectorConstIterator<T>::const_reference VectorConstIterator<T>::operator-> () const {
		return (this->_ptr);
	}

	template <typename T>
	typename VectorConstIterator<T>::const_reference VectorConstIterator<T>::operator[] (size_type index) const {
		return (*(this->_ptr + index));
	}
}

namespace ft {
	
	template <typename T>
	VectorConstReverseIterator<T>::VectorConstReverseIterator(pointer ptr) {
		this->_ptr = ptr;
	}

	template <typename T>
	VectorConstReverseIterator<T>::VectorConstReverseIterator(const VectorIterator<T>& it) {
		this->_ptr = it._ptr;
	}

	template <typename T>
	VectorConstReverseIterator<T> & VectorConstReverseIterator<T>::operator= (const VectorIterator<T>& it) {
		this->_ptr = it._ptr;
		return (*this);
	}

	template <typename T>
	VectorConstReverseIterator<T>::~VectorConstReverseIterator() {
	}

	template <typename T>
	typename VectorConstReverseIterator<T>::const_reference VectorConstReverseIterator<T>::operator* () const {
		return (*(this->_ptr));
	}

	template <typename T>
	typename VectorConstReverseIterator<T>::const_reference VectorConstReverseIterator<T>::operator-> () const {
		return (this->_ptr);
	}

	template <typename T>
	typename VectorConstReverseIterator<T>::const_reference VectorConstReverseIterator<T>::operator[] (size_type index) const {
		return (*(this->_ptr + index));
	}
}

#endif