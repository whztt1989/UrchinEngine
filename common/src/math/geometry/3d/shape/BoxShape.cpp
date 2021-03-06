#include <algorithm>

#include "BoxShape.h"

namespace urchin
{

	/**
	 * @param halfSizes Half sizes (width, height and depth) of box
	 */
	template<class T> BoxShape<T>::BoxShape(const Vector3<T> &halfSizes) :
			Shape3D(),
			halfSizes(halfSizes)
	{

	}

	template<class T> BoxShape<T>::~BoxShape()
	{

	}

	template<class T> const T BoxShape<T>::getHalfSize(unsigned int index) const
	{
		return halfSizes[index];
	}

	template<class T> const Vector3<T> &BoxShape<T>::getHalfSizes() const
	{
		return halfSizes;
	}

	template<class T> const T BoxShape<T>::getMaxHalfSize() const
	{
		return std::max(std::max(halfSizes[0], halfSizes[1]), halfSizes[2]);
	}

	template<class T> unsigned int BoxShape<T>::getMaxHalfSizeIndex() const
	{
		if(halfSizes[0] > halfSizes[1])
		{
			if(halfSizes[0] > halfSizes[2])
			{
				return 0;
			}
			return 1;
		}else if(halfSizes[1] > halfSizes[2])
		{
			return 1;
		}
		return 2;
	}

	template<class T> const T BoxShape<T>::getMinHalfSize() const
	{
		return std::min(std::min(halfSizes[0], halfSizes[1]), halfSizes[2]);
	}

	template<class T> unsigned int BoxShape<T>::getMinHalfSizeIndex() const
	{
		if(halfSizes[0] < halfSizes[1])
		{
			if(halfSizes[0] < halfSizes[2])
			{
				return 0;
			}
			return 1;
		}else if(halfSizes[1] < halfSizes[2])
		{
			return 1;
		}
		return 2;
	}

	template<class T> T BoxShape<T>::getVolume() const
	{
		return halfSizes.X * halfSizes.Y * halfSizes.Z * 8.0;
	}

	//explicit template
	template class BoxShape<float>;
	template class BoxShape<double>;
}
