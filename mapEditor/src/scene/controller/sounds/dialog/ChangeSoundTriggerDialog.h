#ifndef ENGINE_MAPEDITOR_CHANGESOUNDTRIGGERDIALOG_H
#define ENGINE_MAPEDITOR_CHANGESOUNDTRIGGERDIALOG_H

#include <list>
#include <QtWidgets/QDialog>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>

#include "UrchinMapHandler.h"
#include "UrchinSoundEngine.h"

namespace urchin
{

	class ChangeSoundTriggerDialog : public QDialog
	{
		Q_OBJECT

		#define MANUAL_TRIGGER_LABEL "Manual"
		#define SHAPE_TRIGGER_LABEL "Shape"

		public:
			ChangeSoundTriggerDialog(QWidget *parent);

			SoundTrigger::TriggerType getTriggerType() const;

		private:
			void setupSoundTriggerTypeFields();

			void done(int);

			QLabel *soundTriggerTypeLabel;
			QComboBox *soundTriggerTypeComboBox;

			SoundTrigger::TriggerType triggerType;
	};

}

#endif
