#ifndef ENGINE_ACCEPTALLFILTER_H
#define ENGINE_ACCEPTALLFILTER_H

#include "UrchinCommon.h"

#include "OctreeableFilter.h"

namespace urchin
{

	template<class TOctreeable> class AcceptAllFilter : public OctreeableFilter<TOctreeable>
	{
		public:
			AcceptAllFilter();
			~AcceptAllFilter();

			bool isAccepted(const TOctreeable *const) const;
	};

	#include "AcceptAllFilter.inl"

}

#endif
