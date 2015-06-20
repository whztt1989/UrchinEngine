#ifndef ENGINE_VECTOR2_H
#define ENGINE_VECTOR2_H

#include <iostream>
#include <cmath>

#include "math/algebra/matrix/Matrix2.h"

namespace urchin
{

	template<class T> class Vector2
	{
		public:
			Vector2();
			explicit Vector2(T Xu, T Yu);
			Vector2(const Vector2<T> &);
		
			void setValues(T, T);
			void setNull();

			Vector2<T> normalize() const;
			T length() const;
			T squareLength() const;
			T dotProduct(const Vector2<T> &) const;
			Vector2<T> crossProduct(const Vector2<T> &) const;
		
			Vector2<T> operator +() const;
			Vector2<T> operator -() const;
			Vector2<T> operator +(const Vector2<T> &) const;
			Vector2<T> operator -(const Vector2<T> &) const;
			Vector2<T> operator *(const Vector2<T> &) const;
			Vector2<T> operator /(const Vector2<T> &) const;
			const Vector2<T>& operator +=(const Vector2<T>&);
			const Vector2<T>& operator -=(const Vector2<T>&);
			const Vector2<T>& operator *=(const Vector2<T> &);
			const Vector2<T>& operator /=(const Vector2<T> &);
			const Vector2<T>& operator *=(T t);
			const Vector2<T>& operator /=(T t);

			T& operator [](int i);
			const T& operator [](int i) const;

			operator T*();
			operator const T*() const;
		
			T X, Y;
	};

	template<class T> Vector2<T> operator *(const Vector2<T> &, T t);
	template<class T> Vector2<T> operator *(T t, const Vector2<T> &);
	template<class T> Vector2<T> operator /(const Vector2<T> &, T t);

	template<class T> Vector2<T> operator *(const Matrix2<T> &, const Vector2<T> &);
	template<class T> Vector2<T> operator *(const Vector2<T> &, const Matrix2<T> &);

	template<class T> std::ostream& operator <<(std::ostream &, const Vector2<T> &);

}

#endif