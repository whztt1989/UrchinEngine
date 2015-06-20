#ifndef ENGINE_ABSTRACTBODY_H
#define ENGINE_ABSTRACTBODY_H

#include <boost/thread.hpp>
#include <string>
#include <memory>
#include "UrchinCommon.h"

#include "body/work/AbstractWorkBody.h"
#include "shape/CollisionShape3D.h"

namespace urchin
{

	class AbstractBody
	{
		public:
			AbstractBody(const std::string &, const Transform<float> &, std::shared_ptr<const CollisionShape3D>);
			virtual ~AbstractBody();

			void setIsNew(bool);
			bool isNew() const;

			void markAsDeleted();
			bool isDeleted() const;

			virtual AbstractWorkBody *createWorkBody() const = 0;
			void setWorkBody(AbstractWorkBody *);
			AbstractWorkBody *getWorkBody() const;

			virtual void update(AbstractWorkBody *);
			virtual void apply(const AbstractWorkBody *);

			const Transform<float> &getTransform() const;
			const Point3<float> &getPosition() const;
			const Quaternion<float> &getOrientation() const;
			std::shared_ptr<const CollisionShape3D> getOriginalShape() const;
			std::shared_ptr<const CollisionShape3D> getScaledShape() const;

			const std::string &getId() const;

			void setRestitution(float);
			float getRestitution() const;
			void setFriction(float);
			float getFriction() const;
			void setRollingFriction(float);
			float getRollingFriction() const;

			bool isStatic() const;
			bool isActive() const;

		protected:
			void setIsStatic(bool);

			//mutex for attributes modifiable from external
			mutable boost::recursive_mutex bodyMutex;

		private:
			//technical data
			bool bIsNew;
			bool bIsDeleted;
			AbstractWorkBody *workBody;

			//body representation data
			Transform<float> transform;

			//body description data
			std::shared_ptr<const CollisionShape3D> originalShape;
			std::shared_ptr<const CollisionShape3D> scaledShape;
			std::string id;
			float restitution;
			float friction;
			float rollingFriction;

			//state flags
			bool bIsStatic;
			bool bIsActive;
	};

}

#endif