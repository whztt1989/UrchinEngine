#include "LineSegment3D.h"

namespace urchin
{

	template<class T> LineSegment3D<T>::LineSegment3D(const Point3<T> &a,  const Point3<T> &b) :
		a(a), b(b)
	{

	}

	template<class T> const Point3<T> &LineSegment3D<T>::getA() const
	{
		return a;
	}

	template<class T> const Point3<T> &LineSegment3D<T>::getB() const
	{
		return b;
	}

	template<class T> Point3<T> LineSegment3D<T>::getSupportPoint(const Vector3<T> &direction) const
	{
		const T pointADotDirection = a.toVector().dotProduct(direction);
		const T pointBDotDirection = b.toVector().dotProduct(direction);

		if(pointADotDirection > pointBDotDirection)
		{
			return a;
		}

		return b;
	}

	/**
	 * @param barycentrics [out] Returns barycentric coordinates for closest point
	 * @return Point on segment AB closest to point p
	 */
	template<class T> Point3<T> LineSegment3D<T>::closestPoint(const Point3<T> &p, T barycentrics[2]) const
	{
		Vector3<T> ab = a.vector(b);

		T abSquareLength = ab.dotProduct(ab);
		if(abSquareLength==(T)0.0)
		{
			barycentrics[0] = 1.0;
			barycentrics[1] = 0.0;
			return a;
		}

		Vector3<T> ap = a.vector(p);
		T t = ap.dotProduct(ab) / abSquareLength;
		t = std::min((T)1.0, std::max((T)0.0, t));

		barycentrics[0] = 1.0-t;
		barycentrics[1] = t;
		return ((b-a)*t) + a;
	}

	/**
	 * @return Minimum square distance between segment AB and point p
	 */
	template<class T> T LineSegment3D<T>::squareDistance(const Point3<T> &p) const
	{
		Vector3<T> ab = a.vector(b);
		Vector3<T> ap = a.vector(p);

		T e = ap.dotProduct(ab);
		if (e <= 0.0f)
		{
			return ap.dotProduct(ap);
		}

		T f = ab.dotProduct(ab);
		if (e >= f)
		{
			Vector3<T> bp = b.vector(p);
			return bp.dotProduct(bp);
		}

		return ap.dotProduct(ap) - ((e * e) / f);
	}

	template<class T> std::ostream& operator <<(std::ostream &stream, const LineSegment3D<T> &l)
	{
		return stream << l.getA().X << " " << l.getA().Y << " " << l.getA().Z << " - " << l.getB().X << " " << l.getB().Y << " " << l.getB().Z ;
	}

	//explicit template
	template class LineSegment3D<float>;
	template std::ostream& operator <<<float>(std::ostream &, const LineSegment3D<float> &);

}