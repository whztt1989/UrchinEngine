#include "shape/CollisionSphereShape.h"
#include "object/CollisionSphereObject.h"

namespace urchin
{

	/**
	* @param innerMargin Collision inner margin (must be equals to sphere radius)
	*/
	CollisionSphereShape::CollisionSphereShape(float innerMargin) :
			CollisionShape3D(innerMargin),
			sphereShape(SphereShape<float>(innerMargin))
	{

	}

	CollisionSphereShape::~CollisionSphereShape()
	{

	}

	CollisionShape3D::ShapeType CollisionSphereShape::getShapeType() const
	{
		return CollisionShape3D::SPHERE_SHAPE;
	}

	float CollisionSphereShape::getRadius() const
	{
		return sphereShape.getRadius();
	}

	std::shared_ptr<CollisionShape3D> CollisionSphereShape::scale(float scale) const
	{
		return std::make_shared<CollisionSphereShape>(sphereShape.getRadius() * scale);
	}

	std::shared_ptr<CollisionSphereShape> CollisionSphereShape::retrieveSphereShape() const
	{
		return std::make_shared<CollisionSphereShape>(sphereShape.getRadius());
	}

	AABBox<float> CollisionSphereShape::toAABBox(const PhysicsTransform &physicsTransform) const
	{
		const Point3<float> &position = physicsTransform.getPosition();
		return AABBox<float>(position - sphereShape.getRadius(), position + sphereShape.getRadius());
	}

	std::shared_ptr<CollisionConvexObject3D> CollisionSphereShape::toConvexObject(const PhysicsTransform &physicsTransform) const
	{
		const Point3<float> &position = physicsTransform.getPosition();
		return std::make_shared<CollisionSphereObject>(getInnerMargin(), position);
	}

	Vector3<float> CollisionSphereShape::computeLocalInertia(float mass) const
	{
		float localInertia = (2.0/5.0) * mass * sphereShape.getRadius() * sphereShape.getRadius();
		return Vector3<float>(localInertia, localInertia, localInertia);
	}

}
