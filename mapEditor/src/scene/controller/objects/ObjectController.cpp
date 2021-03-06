#include <stdexcept>

#include "ObjectController.h"
#include "scene/controller/objects/bodyshape/support/DefaultBodyShapeCreator.h"

namespace urchin
{

	ObjectController::ObjectController(MapHandler *mapHandler) :
			bIsModified(false),
			mapHandler(mapHandler)
	{

	}

	ObjectController::~ObjectController()
	{

	}

	bool ObjectController::isModified() const
	{
		return bIsModified;
	}

	void ObjectController::markModified()
	{
		bIsModified = true;
	}

	void ObjectController::resetModified()
	{
		bIsModified = false;
	}

	std::list<const SceneObject *> ObjectController::getSceneObjects() const
	{
		std::list<SceneObject *> sceneObjects = mapHandler->getMap()->getSceneObjects();
		std::list<const SceneObject *> constSceneObjects;
		constSceneObjects.insert(constSceneObjects.begin(), sceneObjects.begin(), sceneObjects.end());

		return constSceneObjects;
	}

	void ObjectController::addSceneObject(SceneObject *sceneObject)
	{
		mapHandler->getMap()->addSceneObject(sceneObject);

		markModified();
	}

	void ObjectController::removeSceneObject(const SceneObject *constSceneObject)
	{
		SceneObject *sceneObject = findSceneObject(constSceneObject);
		mapHandler->getMap()->removeSceneObject(sceneObject);

		markModified();
	}

	void ObjectController::createDefaultBody(const SceneObject *constSceneObject)
	{
		SceneObject *sceneObject = findSceneObject(constSceneObject);

		std::string bodyId = constSceneObject->getName();
		Transform<float> modelTransform = constSceneObject->getModel()->getTransform();
		std::shared_ptr<const CollisionShape3D> bodyShape = DefaultBodyShapeCreator(constSceneObject).createDefaultBodyShape(CollisionShape3D::ShapeType::BOX_SHAPE, false);

		RigidBody *rigidBody = new RigidBody(bodyId, modelTransform, bodyShape);
		sceneObject->setRigidBody(rigidBody);

		markModified();
	}

	void ObjectController::changeBodyShape(const SceneObject *constSceneObject, CollisionShape3D::ShapeType shapeType)
	{
		std::shared_ptr<const CollisionShape3D> newCollisionShape = DefaultBodyShapeCreator(constSceneObject).createDefaultBodyShape(shapeType, false);

		updateSceneObjectPhysicsShape(constSceneObject, newCollisionShape);
	}

	void ObjectController::removeBody(const SceneObject *constSceneObject)
	{
		SceneObject *sceneObject = findSceneObject(constSceneObject);
		sceneObject->setRigidBody(nullptr);

		markModified();
	}

	const SceneObject *ObjectController::updateSceneObjectTransform(const SceneObject *constSceneObject, const Transform<float> &transform)
	{
		SceneObject *sceneObject = findSceneObject(constSceneObject);
		Model *model = sceneObject->getModel();

		model->setTransform(transform);

		markModified();
		return sceneObject;
	}

	const SceneObject *ObjectController::updateSceneObjectFlags(const SceneObject *constSceneObject, bool produceShadow)
	{
		SceneObject *sceneObject = findSceneObject(constSceneObject);
		Model *model = sceneObject->getModel();

		model->setProduceShadow(produceShadow);

		markModified();
		return sceneObject;
	}

	const SceneObject *ObjectController::updateSceneObjectPhysicsProperties(const SceneObject *constSceneObject, float mass, float restitution,
			float friction, float rollingFriction, float linearDamping, float angularDamping, const Vector3<float> &linearFactor,
			const Vector3<float> &angularFactor)
	{
		SceneObject *sceneObject = findSceneObject(constSceneObject);
		RigidBody *rigidBody = sceneObject->getRigidBody();

		rigidBody->setMassProperties(mass, rigidBody->getScaledShape()->computeLocalInertia(mass));
		rigidBody->setRestitution(restitution);
		rigidBody->setFriction(friction);
		rigidBody->setRollingFriction(rollingFriction);

		rigidBody->setDamping(linearDamping, angularDamping);

		rigidBody->setLinearFactor(linearFactor);
		rigidBody->setAngularFactor(angularFactor);

		markModified();
		return sceneObject;
	}

	const SceneObject *ObjectController::updateSceneObjectPhysicsShape(const SceneObject *constSceneObject, std::shared_ptr<const CollisionShape3D> newCollisionShape)
	{
		SceneObject *sceneObject = findSceneObject(constSceneObject);
		RigidBody *rigidBody = sceneObject->getRigidBody();

		std::string bodyId = constSceneObject->getName();
		Transform<float> modelTransform = constSceneObject->getModel()->getTransform();
		RigidBody *newRigidBody = new RigidBody(bodyId, modelTransform, newCollisionShape);

		newRigidBody->setMassProperties(rigidBody->getMass(), newRigidBody->getScaledShape()->computeLocalInertia(rigidBody->getMass()));
		newRigidBody->setRestitution(rigidBody->getRestitution());
		newRigidBody->setFriction(rigidBody->getFriction());
		newRigidBody->setRollingFriction(rigidBody->getRollingFriction());

		sceneObject->setRigidBody(newRigidBody);

		markModified();
		return sceneObject;
	}

	SceneObject *ObjectController::findSceneObject(const SceneObject *constSceneObject)
	{
		std::list<SceneObject *> sceneObjects = mapHandler->getMap()->getSceneObjects();
		std::list<SceneObject *>::iterator it = std::find(sceneObjects.begin(), sceneObjects.end(), constSceneObject);

		if(it!=sceneObjects.end())
		{
			return *it;
		}

		throw std::invalid_argument("Impossible to find scene object: " + constSceneObject->getName());
	}

}
