#ifndef ENGINE_GUIRENDERER_H
#define ENGINE_GUIRENDERER_H

#include <set>
#include "UrchinCommon.h"

#include "scene/Renderer.h"
#include "scene/GUI/widget/Widget.h"

namespace urchin
{
	
	class GUIRenderer : public Renderer, public Observer
	{
		public:
			GUIRenderer();
			virtual ~GUIRenderer();

			void onResize(unsigned int, unsigned  int);
			void notify(Observable *, int);
			void setupSkin(const std::string &);

			bool onKeyDown(unsigned int);
			bool onKeyUp(unsigned int);
			bool onChar(unsigned int);
			bool onMouseMove(int, int);
			void onDisable();
			
			void addWidget(Widget *);
			void removeWidget(Widget *);

			void display(float);
			
		private:
			std::vector<Widget *> widgets;

			Matrix3<float> mProjection, mModelView;
			unsigned int GUIShader;
			int mProjectionLoc, translateDistanceLoc, diffuseTexSamplerLoc;
	};
	
}

#endif
