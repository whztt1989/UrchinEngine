#ifndef ENGINE_TEMPORALOBJECT_H
#define ENGINE_TEMPORALOBJECT_H

#include "shape/CollisionShape3D.h"
#include "utils/math/PhysicsTransform.h"

namespace urchin
{

	class TemporalObject
	{
		public:
			TemporalObject(const CollisionShape3D *, const PhysicsTransform &, const PhysicsTransform &);
			~TemporalObject();

			std::shared_ptr<const CollisionConvexObject3D> getLocalObject() const;

			const PhysicsTransform &getFrom() const;
			const PhysicsTransform &getTo() const;

		private:
			std::shared_ptr<const CollisionConvexObject3D> localObject;

			PhysicsTransform from;
			PhysicsTransform to;
	};

}

#endif
