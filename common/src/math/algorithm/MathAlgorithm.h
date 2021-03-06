#ifndef ENGINE_MATHALGORITHM_H
#define ENGINE_MATHALGORITHM_H

namespace urchin
{

	class MathAlgorithm
	{
		public:
			template<class T> static T clamp(T, T, T);
			template<class T> static T sign(T);
			static int nextPowerOfTwo(int);
			static bool isZero(float);
			static unsigned int powerOfTwo(unsigned int);
	};

}

#endif
