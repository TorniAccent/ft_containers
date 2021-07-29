#pragma once

#include <cstddef>

namespace ft {

	template <typename T>
	class VectorIterator;

	template <typename T>
	class VectorReverseIterator;

	template <typename T>
	class VectorReverseIterator;

	template <typename T>
	class VectorConstReverseIterator;

}

namespace ft {

	template <typename T>
	class VectorIterator
	{
	public :
		template <typename K>
		friend class VectorConstIterator;

		typedef T				value_type;
		typedef value_type*		pointer;
		typedef value_type&		reference;
		typedef size_t			size_type;

	protected :
		pointer _ptr;

	public :
		explicit VectorIterator(pointer ptr = NULL);

		VectorIterator(const VectorIterator& it);

		VectorIterator& operator= (const VectorIterator& it);

		virtual ~VectorIterator();

		///
		bool operator== (const VectorIterator& it) const;

		bool operator!= (const VectorIterator& it) const;

		bool operator< (const VectorIterator& it) const;

		bool operator> (const VectorIterator& it) const;

		bool operator<= (const VectorIterator& it) const;

		bool operator>= (const VectorIterator& it) const;

		reference operator* ();

		pointer operator-> ();

		VectorIterator& operator++ ();

		VectorIterator operator++ (int);

		VectorIterator& operator-- ();

		VectorIterator operator-- (int);

		VectorIterator operator+ (size_type n) const;

		VectorIterator operator- (size_type n) const;

		VectorIterator& operator+= (size_type n);

		VectorIterator& operator-= (size_type n);

		reference operator[] (size_type n);
	};

	template <typename T>
	class VectorReverseIterator
	{
	public :
		template <typename K>
		friend class VectorConstReverseIterator;

		typedef T				value_type;
		typedef value_type*		pointer;
		typedef value_type&		reference;
		typedef size_t			size_type;

	protected :
		pointer _ptr;

	public :
		explicit VectorReverseIterator(pointer ptr = NULL);

		VectorReverseIterator(const VectorReverseIterator& it);

		VectorReverseIterator& operator= (const VectorReverseIterator& it);

		virtual ~VectorReverseIterator();

		///
		bool operator== (const VectorReverseIterator& it) const;

		bool operator!= (const VectorReverseIterator& it) const;

		bool operator< (const VectorReverseIterator& it) const;

		bool operator> (const VectorReverseIterator& it) const;

		bool operator<= (const VectorReverseIterator& it) const;

		bool operator>= (const VectorReverseIterator& it) const;

		reference operator* ();

		pointer operator-> ();

		VectorReverseIterator& operator++ ();

		VectorReverseIterator operator++ (int);

		VectorReverseIterator& operator-- ();

		VectorReverseIterator operator-- (int);

		VectorReverseIterator operator+ (size_type n) const;

		VectorReverseIterator operator- (size_type n) const;

		VectorReverseIterator& operator+= (size_type n);

		VectorReverseIterator& operator-= (size_type n);

		reference operator[] (size_type n);
	};

	template <typename T>
	class VectorConstIterator : public VectorIterator<T>
	{
	public :
		typedef T					value_type;
		typedef size_t				size_type;
		typedef value_type*			pointer;
		typedef const value_type&	const_reference;

		explicit VectorConstIterator(pointer ptr = NULL);

		VectorConstIterator(const VectorIterator<T>& it);

		VectorConstIterator& operator= (const VectorIterator<T>& it);

		virtual ~VectorConstIterator();

		const_reference operator* () const;

		const_reference operator-> () const;

		const_reference operator[] (size_type index) const;
	};

	template <typename T>
	class VectorConstReverseIterator : public VectorReverseIterator<T>
	{
	public :
		typedef T					value_type;
		typedef size_t				size_type;
		typedef value_type*			pointer;
		typedef const value_type&	const_reference;

		explicit VectorConstReverseIterator(pointer ptr = NULL);

		VectorConstReverseIterator(const VectorIterator<T>& it);

		VectorConstReverseIterator& operator= (const VectorIterator<T>& it);

		virtual ~VectorConstReverseIterator();

		const_reference operator* () const;

		const_reference operator-> () const;

		const_reference operator[] (size_type index) const;
	};
}

#include "VectorIterator.ipp"