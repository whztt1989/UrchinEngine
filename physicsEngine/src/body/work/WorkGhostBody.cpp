#include "body/work/WorkGhostBody.h"
#include "collision/broadphase/VectorPairContainer.h"

namespace urchin
{

	WorkGhostBody::WorkGhostBody(const std::string &id, const PhysicsTransform &physicsTransform, std::shared_ptr<const CollisionShape3D> shape) :
			AbstractWorkBody(id, physicsTransform, shape),
			pairContainer(new VectorPairContainer())
	{
		setIsStatic(false); //can move and be affected by the physics world: not a static body
		setIsActive(false); //default value: body is not active
	}

	WorkGhostBody::~WorkGhostBody()
	{
		delete pairContainer;
	}

	WorkGhostBody *WorkGhostBody::upCast(AbstractWorkBody *workBody)
	{
		return dynamic_cast<WorkGhostBody*>(workBody);
	}

	const WorkGhostBody *WorkGhostBody::upCast(const AbstractWorkBody *workBody)
	{
		return dynamic_cast<const WorkGhostBody*>(workBody);
	}

	/**
	 * @return Pair container used to collect colliding pairs on ghost body
	 */
	PairContainer *WorkGhostBody::getPairContainer() const
	{
		return pairContainer;
	}

}