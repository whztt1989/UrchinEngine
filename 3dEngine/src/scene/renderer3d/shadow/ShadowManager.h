#ifndef ENGINE_SHADOWMANAGER_H
#define ENGINE_SHADOWMANAGER_H

#include <set>
#include "UrchinCommon.h"

#include "scene/renderer3d/shadow/data/ShadowData.h"
#include "scene/renderer3d/shadow/data/FrustumShadowData.h"
#include "scene/renderer3d/shadow/display/ShadowUniform.h"
#include "scene/renderer3d/shadow/display/ShadowModelUniform.h"
#include "scene/renderer3d/light/Light.h"
#include "scene/renderer3d/light/LightManager.h"
#include "scene/renderer3d/octree/OctreeManager.h"
#include "scene/renderer3d/model/Model.h"
#include "scene/renderer3d/model/displayer/ModelDisplayer.h"
#include "scene/renderer3d/camera/Camera.h"

namespace urchin
{

	/**
	* Manager for shadow mapping (parallel-split shadow maps)
	*/
	class ShadowManager : public Observer
	{
		public:
			ShadowManager(LightManager *, OctreeManager<Model> *);
			virtual ~ShadowManager();

			void initialize(unsigned int);
			void onResize(int, int);
			void onCameraProjectionUpdate(const Camera *const);
			void notify(Observable *, int);

			void setShadowMapResolution(unsigned int);
			unsigned int getShadowMapResolution() const;
			void setNumberShadowMaps(unsigned int);
			unsigned int getNumberShadowMaps() const;
			void setViewingShadowDistance(float);
			float getViewingShadowDistance() const;

			const ShadowData &getShadowData(const Light *const) const;
			std::set<Model *> getVisibleModels();

			void updateVisibleModels(const Frustum<float> &);
			void updateShadowMaps();
			void loadShadowMaps(const Matrix4<float> &);
			
		private:
			//light handling
			void addShadowLight(Light *const);
			void removeShadowLight(Light *const);
			void updateShadowLights();
			void onFrustumUpdate(const Frustum<float> &);

			//splits handling
			void updateViewMatrix(const Light *const);
			void updateFrustumShadowData(const Light *const, ShadowData *const);
			AABBox<float> createSceneIndependentBox(const Frustum<float> &, const Light *const, const Matrix4<float> &) const;
			float computeNearZForSceneIndependentBox(const Frustum<float> &) const;
			AABBox<float> createSceneDependentBox(const AABBox<float> &, const std::set<Model *> &, const Matrix4<float> &) const;
			void splitFrustum(const Frustum<float> &);

			//shadow map handling
			void createShadowMaps(const Light *const);
			void removeShadowMaps(const Light *const);

			//matrix information
			int sceneWidth, sceneHeight;
			float percentageUniformSplit; //percentage of uniform split against the logarithmic split to split frustum
			unsigned int shadowMapResolution, nbShadowMaps;
			float viewingShadowDistance;

			//scene information
			bool isInitialized;
			ModelDisplayer *shadowModelDisplayer;
			LightManager *lightManager;
			OctreeManager<Model> *modelOctreeManager;
			Matrix4<float> projectionMatrix;
			ShadowUniform *shadowUniform;
			ShadowModelUniform *shadowModelUniform;

			//shadow information
			int depthComponent;
			float frustumDistance;
			std::vector<float> splittedDistance;
			std::vector<Frustum<float>> splittedFrustum;
			std::map<const Light *, ShadowData *> shadowDatas;
			unsigned int depthSplitDistanceLoc;

			//light information
			struct LightLocation
			{ //reservation of light locations for light producing shadow
				int shadowMapTexLoc;
				int *mLightProjectionViewLoc;
				unsigned int shadowMapTextureUnits;
			};
			LightLocation *lightsLocation;
	};

}

#endif