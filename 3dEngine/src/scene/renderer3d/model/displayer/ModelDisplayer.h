#ifndef ENGINE_MODELDISPLAYER_H
#define ENGINE_MODELDISPLAYER_H

#include <set>
#include <map>
#include <string>
#include "UrchinCommon.h"

#include "MeshParameter.h"
#include "CustomUniform.h"
#include "CustomModelUniform.h"
#include "scene/renderer3d/model/Model.h"
#include "scene/renderer3d/camera/Camera.h"

namespace urchin
{

	/**
	* Allow to display models given in parameter depending of a configuration (view matrix, projection matrix, display mode...)
	*/
	class ModelDisplayer
	{
		public:
			enum DisplayMode
			{
				DEFAULT_MODE = 0,
				DEPTH_ONLY_MODE
			};

			ModelDisplayer(DisplayMode displayMode);
			~ModelDisplayer();

			void initialize();
			void onCameraProjectionUpdate(const Camera *const);

			int getUniformLocation(const std::string &name);
			void setCustomGeometryShader(const std::string &, const std::map<std::string, std::string> &);
			void setCustomFragmentShader(const std::string &, const std::map<std::string, std::string> &);
			void setCustomUniform(CustomUniform *);
			void setCustomModelUniform(CustomModelUniform *);
			void setModels(const std::set<Model *> &);

			void updateAnimation(float);
			void display(const Matrix4<float> &);

			#ifdef _DEBUG
				void drawBBox(const Matrix4<float> &, const Matrix4<float> &) const;
			#endif

		private:
			void createShader(const std::string &, const std::string &, const std::string &);

			bool isInitialized;

			std::string geometryShaderName, fragmentShaderName;
			std::map<std::string, std::string> geometryTokens, fragmentTokens;

			DisplayMode displayMode;
			MeshParameter meshParameter;
			unsigned int modelShader;
			Matrix4<float> projectionMatrix;
			int mProjectionLoc, mModelLoc, mViewLoc, mNormalLoc, ambientFactorLoc;

			CustomUniform *customUniform;
			CustomModelUniform *customModelUniform;

			std::set<Model *> models;
	};

}

#endif
