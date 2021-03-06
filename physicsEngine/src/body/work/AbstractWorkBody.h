#ifndef ENGINE_ABSTRACTWORKBODY_H
#define ENGINE_ABSTRACTWORKBODY_H

#include <string>
#include <cstdint>
#include <memory>
#include "UrchinCommon.h"

#include "shape/CollisionShape3D.h"
#include "utils/math/PhysicsTransform.h"
#include "collision/island/IslandElement.h"

namespace urchin
{

	/**
	* A work body is copy of the body. This copy is useful when working on concurrent environment in order to avoid
	* concurrent access each times we want to access to body methods.
	*/
	class AbstractWorkBody : public IslandElement
	{
		public:
			AbstractWorkBody(const std::string &, const PhysicsTransform &, const std::shared_ptr<const CollisionShape3D> &);
			virtual ~AbstractWorkBody();

			const PhysicsTransform &getPhysicsTransform() const;

			void setPosition(const Point3<float> &);
			const Point3<float> &getPosition() const;

			void setOrientation(const Quaternion<float> &);
			const Quaternion<float> &getOrientation() const;

			const CollisionShape3D *getShape() const;
			const std::string &getId() const;
			void setRestitution(float);
			float getRestitution() const;
			void setFriction(float);
			float getFriction() const;
			void setRollingFriction(float);
			float getRollingFriction() const;

			bool isStatic() const;
			void setIsStatic(bool);
			bool isActive() const;
			void setIsActive(bool);
			virtual bool isGhostBody() const = 0;

			void setIslandElementId(unsigned int);
			unsigned int getIslandElementId() const;

			uint_fast32_t getObjectId() const;

		private:
			//work body representation data
			PhysicsTransform physicsTransform;

			//work body description data
			std::shared_ptr<const CollisionShape3D> shape;
			std::string id;
			float restitution;
			float friction;
			float rollingFriction;

			//state flags
			bool bIsStatic;
			bool bIsActive;

			//island
			unsigned int islandElementId;

			//technical object id
			static uint_fast32_t nextObjectId;
			uint_fast32_t objectId;
	};

}

#endif
