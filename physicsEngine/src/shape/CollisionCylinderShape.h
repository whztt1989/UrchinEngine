#ifndef ENGINE_COLLISIONCYLINDERSHAPE_H
#define ENGINE_COLLISIONCYLINDERSHAPE_H

#include <memory>
#include <vector>
#include "UrchinCommon.h"

#include "shape/CollisionShape3D.h"
#include "object/CollisionConvexObject3D.h"
#include "utils/math/PhysicsTransform.h"

namespace urchin
{

	class CollisionCylinderShape : public CollisionShape3D
	{
		public:
			CollisionCylinderShape(float, float, CylinderShape<float>::CylinderOrientation);
			CollisionCylinderShape(float, float, float, CylinderShape<float>::CylinderOrientation);
			~CollisionCylinderShape();

			CollisionShape3D::ShapeType getShapeType() const;
			float getRadius() const;
			float getHeight() const;
			CylinderShape<float>::CylinderOrientation getCylinderOrientation() const;

			std::shared_ptr<CollisionShape3D> scale(float) const;
			std::shared_ptr<CollisionSphereShape> retrieveSphereShape() const;

			AABBox<float> toAABBox(const PhysicsTransform &) const;
			std::shared_ptr<CollisionConvexObject3D> toConvexObject(const PhysicsTransform &) const;

			Vector3<float> computeLocalInertia(float) const;

		private:
			void computeSafeMargin();

			const CylinderShape<float> cylinderShape; //shape including margin
	};

}

#endif
