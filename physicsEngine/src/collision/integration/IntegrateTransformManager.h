#ifndef ENGINE_INTEGRATETRANSFORMMANAGER_H
#define ENGINE_INTEGRATETRANSFORMMANAGER_H

#include "body/BodyManager.h"
#include "body/work/WorkRigidBody.h"
#include "collision/broadphase/BroadPhaseManager.h"
#include "collision/narrowphase/NarrowPhaseManager.h"

namespace urchin
{

	/**
	* Manager allowing to perform integration on bodies transformation
	*/
	class IntegrateTransformManager
	{
		public:
			IntegrateTransformManager(const BodyManager *, const BroadPhaseManager *, const NarrowPhaseManager *);
			~IntegrateTransformManager();

			void integrateTransform(float);

		private:
			PhysicsTransform integrateTransform(const PhysicsTransform &, const Vector3<float> &, const Vector3<float> &, float) const;
			void handleContinuousCollision(WorkRigidBody *, const PhysicsTransform &, const PhysicsTransform &, float);

			const BodyManager *bodyManager;
			const BroadPhaseManager *broadPhaseManager;
			const NarrowPhaseManager *narrowPhaseManager;
	};

}

#endif
