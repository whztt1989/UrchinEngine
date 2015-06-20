#ifndef ENGINE_SIMPLEX_H
#define ENGINE_SIMPLEX_H

#include <vector>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include "UrchinCommon.h"

namespace urchin
{

	template<class T> struct SupportMapping
	{
		Point3<T> supportPointA;
		Point3<T> supportPointB;
		Point3<T> point; //supportPointA - supportPointB
		T barycentric; //barycentric/weight of point 'point'. Value undefined when simplex contain the origin.
	};

	template<class T> class Simplex
	{
		public:
			Simplex();
			~Simplex();

			void addPoint(const Point3<T> &, const Point3<T> &);
			void removePoint(unsigned int);
			void swapPoints(unsigned int, unsigned int);
			void setBarycentric(unsigned int, T);
			void setClosestPointToOrigin(const Point3<T> &);

			unsigned int getSize() const;
			const Point3<T> &getPoint(unsigned int) const;
			const Point3<T> &getSupportPointA(unsigned int) const;
			const Point3<T> &getSupportPointB(unsigned int) const;
			const Point3<T> &getClosestPointToOrigin() const;
			bool isPointInSimplex(const Point3<T> &) const;

			void computeClosestPoints(Point3<T> &, Point3<T> &) const;

		private:
			std::vector<SupportMapping<T>> simplexPoints;
			Point3<T> closestPointToOrigin;
	};

}

#endif