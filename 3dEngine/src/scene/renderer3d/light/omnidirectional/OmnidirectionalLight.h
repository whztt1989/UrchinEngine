#ifndef ENGINE_OMNIDIRECTIONALLIGHT_H
#define ENGINE_OMNIDIRECTIONALLIGHT_H

#include "UrchinCommon.h"

#include "scene/renderer3d/light/Light.h"

namespace urchin
{

	class OmnidirectionalLight : public Light
	{
		public:
			OmnidirectionalLight(const Point3<float> &);
			virtual ~OmnidirectionalLight();

			//general methods
			void setPosition(const Point3<float> &);
			const Point3<float> &getPosition() const;
			std::vector<Vector3<float>> getDirections() const;
			LightType getLightType() const;
			bool hasParallelBeams() const;
			const AABBox<float> &getAABBox() const;

			//attenuation methods
			void setAttenuation(float);
			float getExponentialAttenuation() const;
			const AABBox<float> &getAABBoxScope() const;
			const Sphere<float> &getSphereScope() const;

		private:
			void computeScope();

			//general properties
			Point3<float> position;

			//attenuation properties
			const float attenuationNoEffect; //defines when the attenuation of a light has no light effect on objects
			float exponentialAttenuation;
			Sphere<float> *sphereScope;
			AABBox<float> *bboxScope;

	};

}

#endif
