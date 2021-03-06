#include "collision/OverlappingPair.h"

namespace urchin
{

	OverlappingPair::OverlappingPair(AbstractWorkBody *body1, AbstractWorkBody *body2) :
			body1(body1),
			body2(body2),
			bodiesId(computeBodiesId(body1, body2)),
			collisionAlgorithm(nullptr)
	{

	}

	/**
	* @param bodiesId Unique id representing both bodies
	*/
	OverlappingPair::OverlappingPair(AbstractWorkBody *body1, AbstractWorkBody *body2, uint_fast64_t bodiesId) :
			body1(body1),
			body2(body2),
			bodiesId(bodiesId),
			collisionAlgorithm(nullptr)
	{

	}

	OverlappingPair::~OverlappingPair()
	{

	}

	AbstractWorkBody *OverlappingPair::getBody1() const
	{
		return body1;
	}

	AbstractWorkBody *OverlappingPair::getBody2() const
	{
		return body2;
	}

	/**
	 * Computes an unique key for both bodies
	 */
	uint_fast64_t OverlappingPair::computeBodiesId(const AbstractWorkBody *body1, const AbstractWorkBody *body2)
	{
		if(body1->getObjectId() > body2->getObjectId())
		{ //swap bodies
			std::swap(body1, body2);
		}

		uint_fast64_t key = body1->getObjectId();
		key = key << 32;
		key += body2->getObjectId();

		return key;
	}

	/**
	 * @return Unique id representing both bodies
	 */
	uint_fast64_t OverlappingPair::getBodiesId() const
	{
		return bodiesId;
	}

	void OverlappingPair::setCollisionAlgorithm(std::shared_ptr<CollisionAlgorithm> collisionAlgorithm)
	{
		this->collisionAlgorithm = collisionAlgorithm;
	}

	std::shared_ptr<CollisionAlgorithm> OverlappingPair::getCollisionAlgorithm() const
	{
		return collisionAlgorithm;
	}

}
