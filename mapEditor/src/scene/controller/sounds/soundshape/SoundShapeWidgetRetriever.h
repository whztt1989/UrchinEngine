#ifndef ENGINE_MAPEDITOR_SOUNDSHAPEWIDGETRETRIEVER_H
#define ENGINE_MAPEDITOR_SOUNDSHAPEWIDGETRETRIEVER_H

#include <memory>
#include <QWidget>

#include "UrchinSoundEngine.h"
#include "UrchinMapHandler.h"
#include "scene/controller/sounds/soundshape/SoundShapeWidget.h"

namespace urchin
{

	class SoundShapeWidgetRetriever
	{
		public:
			SoundShapeWidgetRetriever(QWidget *, const SceneSound *);

			SoundShapeWidget *retrieveShapeWidget(const SoundShape *);
			SoundShapeWidget *retrieveShapeWidget(SoundShape::ShapeType);

		private:
			QWidget *parentWidget;
			const SceneSound *sceneSound;
	};

}

#endif
