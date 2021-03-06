#ifndef ENGINE_TRANSFORM_H
#define ENGINE_TRANSFORM_H

#include "math/algebra/Quaternion.h"
#include "math/algebra/point/Point3.h"
#include "math/algebra/matrix/Matrix4.h"

namespace urchin
{
	
	/**
	* Class allow to create transform matrix from a given position, orientation and scale
	*/
	template<class T> class Transform
	{
		public:
			Transform();
			Transform(const Point3<T> &, const Quaternion<T> &q = Quaternion<T>(), T scale = (T)1.0);
		
			void setPosition(const Point3<T> &);
			const Point3<T> &getPosition() const;

			void setOrientation(const Quaternion<T> &);
			const Quaternion<T> &getOrientation() const;

			void setScale(T);
			T getScale() const;

			const Matrix4<T> &getPositionMatrix() const;
			const Matrix4<T> &getOrientationMatrix() const;
			const Matrix4<T> &getScaleMatrix() const;
			const Matrix4<T> &getTransformMatrix() const;
		
		private:
			Point3<T> pPosition;
			Quaternion<T> qOrientation;
			T fScale;

			Matrix4<T> mPosition, mOrientation, mScale, mTransform;
	};

}

#endif
