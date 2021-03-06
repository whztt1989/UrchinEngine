#ifndef ENGINE_GJKTESTHELPER_H
#define ENGINE_GJKTESTHELPER_H

#include <memory>
#include "UrchinCommon.h"
#include "UrchinPhysicsEngine.h"
using namespace urchin;

class GJKTestHelper
{
	public:
		static std::shared_ptr<GJKResult<float>> executeGJK(const CollisionConvexObject3D &, const CollisionConvexObject3D &);

	private:
		GJKTestHelper();
		~GJKTestHelper();
};

#endif
