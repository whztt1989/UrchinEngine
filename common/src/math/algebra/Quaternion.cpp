#include "math/algebra/Quaternion.h"

namespace urchin
{

	template<class T> Quaternion<T>::Quaternion() :
		X(0), Y(0), Z(0), W(1)
	{

	}

	template<class T> Quaternion<T>::Quaternion(T Xu, T Yu, T Zu, T Wu) :
		X(Xu), Y(Yu), Z(Zu), W(Wu)
	{

	}

	template<class T> Quaternion<T>::Quaternion(const Matrix3<T> &matrix)
	{
		const T trace = matrix(0, 0) + matrix(1, 1) + matrix(2, 2);

		if(trace > 0.0)
		{
			const T s = 0.5f / sqrtf(trace + 1.0f);
			X = (matrix(2, 1) - matrix(1, 2)) * s;
			Y = (matrix(0, 2) - matrix(2, 0)) * s;
			Z = (matrix(1, 0) - matrix(0, 1)) * s;
			W = 0.25f / s;
		}else
		{
			if((matrix(0, 0) > matrix(1, 1)) && (matrix(0, 0) > matrix(2, 2)))
			{
				const T s = sqrtf(1.0 + matrix(0, 0) - matrix(1, 1) - matrix(2, 2)) * 2.0;
				X = 0.25 * s;
				Y = (matrix(0, 1) + matrix(1, 0)) / s;
				Z = (matrix(0, 2) + matrix(2, 0)) / s;
				W = (matrix(2, 1) - matrix(1, 2)) / s;
			}else if (matrix(1, 1) > matrix(2, 2))
			{
				const T s = sqrtf(1.0 - matrix(0, 0) + matrix(1, 1) - matrix(2, 2)) * 2.0;
				X = (matrix(0, 1) + matrix(1, 0)) / s;
				Y = 0.25 * s;
				Z = (matrix(1, 2) + matrix(2, 1)) / s;
				W = (matrix(0, 2) - matrix(2, 0)) / s;
			}else
			{
				const T s = sqrtf(1.0 - matrix(0, 0) - matrix(1, 1) + matrix(2, 2)) * 2.0;
				X = (matrix(0, 2) + matrix(2, 0)) / s;
				Y = (matrix(1, 2) + matrix(2, 1)) / s;
				Z = 0.25 * s;
				W = (matrix(1, 0) - matrix(0, 1)) / s;
			}
		}
	}

	template<class T> Quaternion<T>::Quaternion(const Vector3<T> &axis, T angle)
	{
		const T halfAngle = angle / 2.0;
		const T sin = std::sin(halfAngle);

		Vector3<T> normalizedAxis = axis.normalize();
		X = normalizedAxis.X * sin;
		Y = normalizedAxis.Y * sin;
		Z = normalizedAxis.Z * sin;
		W = std::cos(halfAngle);
	}

	template<class T> Quaternion<T>::Quaternion(const Vector3<T> &eulerAngles, RotationSequence rotationSequence)
	{
		Quaternion<T> finalQuaternion;

		switch(rotationSequence)
		{
			case RotationSequence::XYZ:
				finalQuaternion = Quaternion(Vector3<T>(0.0, 0.0, 1.0), eulerAngles[2]) *
						Quaternion(Vector3<T>(0.0, 1.0, 0.0), eulerAngles[1]) *
						Quaternion(Vector3<T>(1.0, 0.0, 0.0), eulerAngles[0]);
				break;
			case RotationSequence::XZY:
				finalQuaternion = Quaternion(Vector3<T>(0.0, 1.0, 0.0), eulerAngles[2]) *
						Quaternion(Vector3<T>(0.0, 0.0, 1.0), eulerAngles[1]) *
						Quaternion(Vector3<T>(1.0, 0.0, 0.0), eulerAngles[0]);
				break;
			case RotationSequence::YXZ:
				finalQuaternion = Quaternion(Vector3<T>(0.0, 0.0, 1.0), eulerAngles[2]) *
						Quaternion(Vector3<T>(1.0, 0.0, 0.0), eulerAngles[1]) *
						Quaternion(Vector3<T>(0.0, 1.0, 0.0), eulerAngles[0]);
				break;
			case RotationSequence::YZX:
				finalQuaternion = Quaternion(Vector3<T>(1.0, 0.0, 0.0), eulerAngles[2]) *
						Quaternion(Vector3<T>(0.0, 0.0, 1.0), eulerAngles[1]) *
						Quaternion(Vector3<T>(0.0, 1.0, 0.0), eulerAngles[0]);
				break;
			case RotationSequence::ZXY:
				finalQuaternion = Quaternion(Vector3<T>(0.0, 1.0, 0.0), eulerAngles[2]) *
						Quaternion(Vector3<T>(1.0, 0.0, 0.0), eulerAngles[1]) *
						Quaternion(Vector3<T>(0.0, 0.0, 1.0), eulerAngles[0]);
				break;
			case RotationSequence::ZYX:
				finalQuaternion = Quaternion(Vector3<T>(1.0, 0.0, 0.0), eulerAngles[2]) *
						Quaternion(Vector3<T>(0.0, 1.0, 0.0), eulerAngles[1]) *
						Quaternion(Vector3<T>(0.0, 0.0, 1.0), eulerAngles[0]);
				break;
			case RotationSequence::XYX:
				finalQuaternion = Quaternion(Vector3<T>(1.0, 0.0, 0.0), eulerAngles[2]) *
						Quaternion(Vector3<T>(0.0, 1.0, 0.0), eulerAngles[1]) *
						Quaternion(Vector3<T>(1.0, 0.0, 0.0), eulerAngles[0]);
				break;
			case RotationSequence::XZX:
				finalQuaternion = Quaternion(Vector3<T>(1.0, 0.0, 0.0), eulerAngles[2]) *
						Quaternion(Vector3<T>(0.0, 0.0, 1.0), eulerAngles[1]) *
						Quaternion(Vector3<T>(1.0, 0.0, 0.0), eulerAngles[0]);
				break;
			case RotationSequence::YXY:
				finalQuaternion = Quaternion(Vector3<T>(0.0, 1.0, 0.0), eulerAngles[2]) *
						Quaternion(Vector3<T>(1.0, 0.0, 0.0), eulerAngles[1]) *
						Quaternion(Vector3<T>(0.0, 1.0, 0.0), eulerAngles[0]);
				break;
			case RotationSequence::YZY:
				finalQuaternion = Quaternion(Vector3<T>(0.0, 1.0, 0.0), eulerAngles[2]) *
						Quaternion(Vector3<T>(0.0, 0.0, 1.0), eulerAngles[1]) *
						Quaternion(Vector3<T>(0.0, 1.0, 0.0), eulerAngles[0]);
				break;
			case RotationSequence::ZXZ:
				finalQuaternion = Quaternion(Vector3<T>(0.0, 0.0, 1.0), eulerAngles[2]) *
						Quaternion(Vector3<T>(1.0, 0.0, 0.0), eulerAngles[1]) *
						Quaternion(Vector3<T>(0.0, 0.0, 1.0), eulerAngles[0]);
				break;
			case RotationSequence::ZYZ:
				finalQuaternion = Quaternion(Vector3<T>(0.0, 0.0, 1.0), eulerAngles[2]) *
						Quaternion(Vector3<T>(0.0, 1.0, 0.0), eulerAngles[1]) *
						Quaternion(Vector3<T>(0.0, 0.0, 1.0), eulerAngles[0]);
				break;
			default:
				throw std::invalid_argument("Unknown quaternion rotation sequence: " + rotationSequence);
		}

		X = finalQuaternion.X;
		Y = finalQuaternion.Y;
		Z = finalQuaternion.Z;
		W = finalQuaternion.W;
	}

	template<class T> void Quaternion<T>::computeW()
	{
		const T t = 1.0f - (X*X) - (Y*Y) - (Z*Z);

		if (t<0.0f)
		{
			W = 0.0f;
		}else
		{
			W = -sqrt(t);
		}
	}

	template<class T> void Quaternion<T>::setIdentity()
	{
		X = Y = Z = 0.0f;
		W = 1.0f;
	}

	template<class T> Quaternion<T> Quaternion<T>::normalize() const
	{
		//computes magnitude of the quaternion
		const T mag = length();
	
		//checks for bogus length, to protect against divide by zero
		if(mag>0.0f)
		{
			return Quaternion<T>(X/mag, Y/mag, Z/mag, W/mag);
		}

		return Quaternion(X, Y, Z, W);
	}

	template<class T> Quaternion<T> Quaternion<T>::conjugate() const
	{
		return Quaternion<T>(-X, -Y, -Z, W);
	}

	template<class T> T Quaternion<T>::length() const
	{
		return sqrt((X*X) + (Y*Y) + (Z*Z) + (W*W));
	}

	template<class T> T Quaternion<T>::squareLength() const
	{
		return (X*X) + (Y*Y) + (Z*Z) + (W*W);
	}

	template<class T> T Quaternion<T>::dotProduct(const Quaternion<T> &q) const
	{
		return ((X*q.X) + (Y*q.Y) + (Z*q.Z) + (W*q.W));
	}

	template<class T> Point3<T> Quaternion<T>::rotatePoint(const Point3<T> &in) const
	{
		//Rotate point only works with normalized quaternion
		#ifdef _DEBUG
			const T mag = length();
			assert(mag >= (T)0.9999);
			assert(mag <= (T)1.0001);
		#endif

		const Quaternion<T> &conjugateThis = conjugate().normalize();

		Quaternion<T> final = (*this)*(in);
		final = final*conjugateThis;

		return Point3<T>(final.X, final.Y, final.Z);
	}

	template<class T> Quaternion<T> Quaternion<T>::slerp(const Quaternion &q, T t) const
	{
		//check for out-of range parameter and return edge points if so
		if(t <= 0.0)
		{
			return *this;
		}

		if(t >= 1.0)
		{
			return q;
		}

		//compute "cosine of angle between quaternions" using dot product
		T cosOmega = dotProduct(q);

		//if negative dot, use -q1.  two quaternions q and -q represent the same rotation, but may produce different slerp.  we chose q or -q to rotate using the acute angle.
		T q1w = q.W;
		T q1x = q.X;
		T q1y = q.Y;
		T q1z = q.Z;

		if(cosOmega < 0.0f)
		{
			q1w = -q1w;
			q1x = -q1x;
			q1y = -q1y;
			q1z = -q1z;
			cosOmega = -cosOmega;
		}

		//we should have two unit quaternions, so dot should be <= 1.0
		assert(cosOmega < 1.1f);

		//computes interpolation fraction, checking for quaternions almost exactly the same
		T k0, k1;

		if(cosOmega > 0.9999f)
		{
			//very close - just use linear interpolation, which will protect againt a divide by zero
			k0 = 1.0f - t;
			k1 = t;
		}else
		{
			//computes the sin of the angle using the trig identity sin^2(omega) + cos^2(omega) = 1
			T sinOmega = sqrt(1.0f - (cosOmega * cosOmega));

			//computes the angle from its sin and cosine
			T omega = atan2(sinOmega, cosOmega);

			//computes inverse of denominator, so we only have to divide once
			T oneOverSinOmega = 1.0f / sinOmega;

			//computes interpolation parameters
			k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
			k1 = sin(t * omega) * oneOverSinOmega;
		}

		//interpolates and returns new quaternion
		return Quaternion<T>(	(k0 * X) + (k1 * q1x),
					(k0 * Y) + (k1 * q1y),
					(k0 * Z) + (k1 * q1z),
					(k0 * W) + (k1 * q1w));
	}

	template<class T> Matrix4<T> Quaternion<T>::toMatrix4() const
	{
		const T xx = X * X;
		const T xy = X * Y;
		const T xz = X * Z;
		const T xw = X * W;
		const T yy = Y * Y;
		const T yz = Y * Z;
		const T yw = Y * W;
		const T zz = Z * Z;
		const T zw = Z * W;

		return Matrix4<T>(	1 - 2 * (yy + zz),     	2 * (xy - zw),     	2 * (xz + yw), 		0,
				2 * (xy + zw), 		1 - 2 * (xx + zz),     	2 * (yz - xw), 		0,
				2 * (xz - yw),     	2 * (yz + xw), 		1 - 2 * (xx + yy), 	0,
				0,                 	0,                 	0, 			1);
	}

	template<class T> Matrix3<T> Quaternion<T>::toMatrix3() const
	{
		const T xx = X * X;
		const T xy = X * Y;
		const T xz = X * Z;
		const T xw = X * W;
		const T yy = Y * Y;
		const T yz = Y * Z;
		const T yw = Y * W;
		const T zz = Z * Z;
		const T zw = Z * W;

		return Matrix3<T>(	1 - 2 * (yy + zz),     	2 * (xy - zw),     	2 * (xz + yw),
				2 * (xy + zw), 		1 - 2 * (xx + zz),     	2 * (yz - xw),
				2 * (xz - yw),     	2 * (yz + xw), 		1 - 2 * (xx + yy));
	}

	template<class T> void Quaternion<T>::toAxisAngle(Vector3<T> &axis, T &angle) const
	{
		angle = std::acos(W) * 2;

		T norm = sqrtf(X*X + Y*Y + Z*Z);
		if(std::fabs(norm) > 0.0)
		{
			axis.X = X / norm;
			axis.Y = Y / norm;
			axis.Z = Z / norm;
		}else
		{
			axis.X = 0.0;
			axis.Y = 1.0;
			axis.Z = 0.0;
		}
	}

	template<class T> Vector3<T> Quaternion<T>::toEulerAngle(RotationSequence rotationSequence) const
	{
		switch(rotationSequence)
		{
			case RotationSequence::XYZ:
				return threeAxisEulerRotation(0, 1, 2);
			case RotationSequence::XZY:
				return threeAxisEulerRotation(0, 2, 1);
			case RotationSequence::YXZ:
				return threeAxisEulerRotation(1, 0, 2);
			case RotationSequence::YZX:
				return threeAxisEulerRotation(1, 2, 0);
			case RotationSequence::ZXY:
				return threeAxisEulerRotation(2, 0, 1);
			case RotationSequence::ZYX:
				return threeAxisEulerRotation(2, 1, 0);
			case RotationSequence::XYX:
				return twoAxisEulerRotation(0, 1, 2);
			case RotationSequence::XZX:
				return twoAxisEulerRotation(0, 2, 1);
			case RotationSequence::YXY:
				return twoAxisEulerRotation(1, 0, 2);
			case RotationSequence::YZY:
				return twoAxisEulerRotation(1, 2, 0);
			case RotationSequence::ZXZ:
				return twoAxisEulerRotation(2, 0, 1);
			case RotationSequence::ZYZ:
				return twoAxisEulerRotation(2, 1, 0);
			default:
				throw std::invalid_argument("Unknown quaternion rotation sequence: " + rotationSequence);
		}
	}

	template<class T> Vector3<T> Quaternion<T>::threeAxisEulerRotation(int i, int j, int k) const
	{ //inspired on Eigen library (EulerAngle.h)
		Vector3<T> euler;

		bool sequenceAxis = ((i+1)%3==j) ? true : false;
		Matrix3<T> m = toMatrix3();

		euler[0] = atan2(m(k, j), m(k, k));
		T cosEuler1 = Vector2<T>(m(i, i), m(j, i)).length();

		if((sequenceAxis && euler[0]<0) || ((!sequenceAxis) && euler[0]>0))
		{
			euler[0] = (euler[0] > 0) ? euler[0] - PI_VALUE : euler[0] + PI_VALUE;
			euler[1] = atan2(-m(k, i), -cosEuler1);
		}else
		{
			euler[1] = atan2(-m(k, i), cosEuler1);
		}

		T sinEuler0 = sin(euler[0]);
		T cosEuler0 = cos(euler[0]);
		euler[2] = atan2(sinEuler0*m(i, k) - cosEuler0*m(i, j), cosEuler0*m(j, j) - sinEuler0*m(j, k));

		return sequenceAxis ? euler : -euler;
	}

	template<class T> Vector3<T> Quaternion<T>::twoAxisEulerRotation(int i, int j, int k) const
	{ //inspired on Eigen library (EulerAngle.h)
		Vector3<T> euler;

		bool sequenceAxis = ((i+1)%3==j) ? true : false;
		Matrix3<T> m = toMatrix3();

		euler[0] = atan2(m(i, j), m(i, k));
		T sinEuler1 = Vector2<T>(m(i, j), m(i, k)).length();

	    if((sequenceAxis && euler[0]<0) || ((!sequenceAxis) && euler[0]>0))
	    {
	    	euler[0] = (euler[0] > 0) ? euler[0] - PI_VALUE : euler[0] + PI_VALUE;
	    	euler[1] = -atan2(sinEuler1, m(i, i));
	    }else
	    {
	    	euler[1] = atan2(sinEuler1, m(i, i));
	    }

	    T sinEuler0 = sin(euler[0]);
	    T cosEuler0 = cos(euler[0]);
	    euler[2] = atan2(cosEuler0*m(k, j) - sinEuler0*m(k, k), cosEuler0*m(j, j) - sinEuler0*m(j, k));

		return sequenceAxis ? euler : -euler;
	}

	template<class T> Quaternion<T> Quaternion<T>::operator +(const Quaternion<T> &q) const
	{
		return Quaternion<T>(X+q.X, Y+q.Y, Z+q.Z, W+q.W);
	}

	template<class T> Quaternion<T> Quaternion<T>::operator -(const Quaternion<T> &q) const
	{
		return Quaternion<T>(X-q.X, Y-q.Y, Z-q.Z, W-q.W);
	}

	template<class T> Quaternion<T> Quaternion<T>::operator *(const Quaternion<T> &q) const
	{
		return Quaternion<T>(
				W*q.X + X*q.W + Y*q.Z - Z*q.Y,
				W*q.Y - X*q.Z + Y*q.W + Z*q.X,
				W*q.Z + X*q.Y - Y*q.X + Z*q.W,
				W*q.W - X*q.X - Y*q.Y - Z*q.Z);
	}

	template<class T> const Quaternion<T>& Quaternion<T>::operator -=(const Quaternion<T> &q)
	{
		*this = *this - q;

		return *this;
	}

	template<class T> const Quaternion<T>& Quaternion<T>::operator +=(const Quaternion<T> &q)
	{
		*this = *this + q;

		return *this;
	}

	template<class T> const Quaternion<T>& Quaternion<T>::operator *=(const Quaternion<T> &q)
	{
		*this = *this * q;

		return *this;
	}

	template<class T> const Quaternion<T>& Quaternion<T>::operator *=(const Point3<T> &p)
	{
		*this = *this * p;

		return *this;
	}

	template<class T> const Quaternion<T>& Quaternion<T>::operator *=(T t)
	{
		*this = *this * t;

		return *this;
	}

	template<class T> T& Quaternion<T>::operator [](int i)
	{
		return (&X)[i];
	}

	template<class T> const T& Quaternion<T>::operator [](int i) const
	{
		return (&X)[i];
	}

	template<class T> Quaternion<T> operator *(const Quaternion<T> &q, const Point3<T> &p)
	{
		return Quaternion<T>(
				(q.W*p.X) + (q.Y*p.Z) - (q.Z*p.Y),
				(q.W*p.Y) + (q.Z*p.X) - (q.X*p.Z),
				(q.W*p.Z) + (q.X*p.Y) - (q.Y*p.X),
				-(q.X*p.X) - (q.Y*p.Y) - (q.Z*p.Z));
	}

	template<class T> Quaternion<T> operator *(const Quaternion<T> &q, T t)
	{
		return Quaternion<T>(q.X*t, q.Y*t, q.Z*t, q.W*t);
	}

	template<class T> Quaternion<T> operator *(T t, const Quaternion<T> &q)
	{
		return q * t;
	}

	template<class T> std::ostream& operator <<(std::ostream &stream, const Quaternion<T> &q)
	{
		return stream << q.X << " " << q.Y << " " << q.Z << " " << q.W;
	}

	//explicit template
	template class Quaternion<float>;
	template Quaternion<float> operator *(const Quaternion<float> &, const Point3<float> &);
	template Quaternion<float> operator *(const Quaternion<float> &, float);
	template Quaternion<float> operator *(float, const Quaternion<float> &);
	template std::ostream& operator <<<float>(std::ostream &, const Quaternion<float> &);

	template class Quaternion<double>;
	template Quaternion<double> operator *(const Quaternion<double> &, const Point3<double> &);
	template Quaternion<double> operator *(const Quaternion<double> &, double);
	template Quaternion<double> operator *(double, const Quaternion<double> &);
	template std::ostream& operator <<<double>(std::ostream &, const Quaternion<double> &);

}
