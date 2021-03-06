#include <stdexcept>

#include "CollisionShapeReaderWriterRetriever.h"
#include "resources/object/bodyshape/CollisionSphereReaderWriter.h"
#include "resources/object/bodyshape/CollisionCapsuleReaderWriter.h"
#include "resources/object/bodyshape/CollisionCylinderReaderWriter.h"
#include "resources/object/bodyshape/CollisionBoxReaderWriter.h"
#include "resources/object/bodyshape/CollisionConvexHullReaderWriter.h"
#include "resources/object/bodyshape/CollisionCompoundShapeReaderWriter.h"

namespace urchin
{

	std::shared_ptr<CollisionShapeReaderWriter> CollisionShapeReaderWriterRetriever::retrieveShapeReaderWriter(std::shared_ptr<XmlChunk> shapeChunk)
	{
		std::string shapeType = shapeChunk->getAttributeValue(TYPE_ATTR);
		if(shapeType.compare(SPHERE_VALUE)==0)
		{
			return std::make_shared<CollisionSphereReaderWriter>();
		}else if(shapeType.compare(CAPSULE_VALUE)==0)
		{
			return std::make_shared<CollisionCapsuleReaderWriter>();
		}else if(shapeType.compare(CYLINDER_VALUE)==0)
		{
			return std::make_shared<CollisionCylinderReaderWriter>();
		}else if(shapeType.compare(BOX_VALUE)==0)
		{
			return std::make_shared<CollisionBoxReaderWriter>();
		}else if(shapeType.compare(CONVEX_HULL_VALUE)==0)
		{
			return std::make_shared<CollisionConvexHullReaderWriter>();
		}else if(shapeType.compare(COMPOUND_SHAPE_VALUE)==0)
		{
			return std::make_shared<CollisionCompoundShapeReaderWriter>();
		}

		throw std::invalid_argument("Unknown shape type: " + shapeType);
	}

	std::shared_ptr<CollisionShapeReaderWriter> CollisionShapeReaderWriterRetriever::retrieveShapeReaderWriter(const CollisionShape3D *collisionShape)
	{
		CollisionShape3D::ShapeType shapeType = collisionShape->getShapeType();
		if(shapeType==CollisionShape3D::SPHERE_SHAPE)
		{
			return std::make_shared<CollisionSphereReaderWriter>();
		}else if(shapeType==CollisionShape3D::CAPSULE_SHAPE)
		{
			return std::make_shared<CollisionCapsuleReaderWriter>();
		}else if(shapeType==CollisionShape3D::CYLINDER_SHAPE)
		{
			return std::make_shared<CollisionCylinderReaderWriter>();
		}else if(shapeType==CollisionShape3D::BOX_SHAPE)
		{
			return std::make_shared<CollisionBoxReaderWriter>();
		}else if(shapeType==CollisionShape3D::CONVEX_HULL_SHAPE)
		{
			return std::make_shared<CollisionConvexHullReaderWriter>();
		}else if(shapeType==CollisionShape3D::COMPOUND_SHAPE)
		{
			return std::make_shared<CollisionCompoundShapeReaderWriter>();
		}

		throw std::invalid_argument("Unknown shape type: " + shapeType);
	}

}
