#ifndef ENGINE_MAPEDITOR_NEWSOUNDDIALOG_H
#define ENGINE_MAPEDITOR_NEWSOUNDDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>

#include "UrchinMapHandler.h"
#include "scene/controller/sounds/SoundController.h"

namespace urchin
{

	class NewSoundDialog : public QDialog
	{
		Q_OBJECT

		#define AMBIENT_SOUND_LABEL "Ambient"
		#define POINT_SOUND_LABEL "Point"

		public:
			NewSoundDialog(QWidget *parent, const SoundController *);

			SceneSound *getSceneSound() const;

		private:
			void setupNameFields();
			void setupSoundFilenameFields();
			void setupSoundTypeFields();

			void updateSoundName();
			int buildSceneSound(int);

			void done(int);
			bool isSceneSoundExist(const std::string &);

			const SoundController *soundController;

			QLabel *soundNameLabel;
			QLineEdit *soundNameText;
			QLabel *soundFilenameLabel;
			QLineEdit *soundFilenameText;
			QLabel *soundTypeLabel;
			QComboBox *soundTypeComboBox;

			std::string soundName;
			std::string soundFilename;
			SceneSound *sceneSound;
			static QString preferredSoundPath;

		private slots:
			void showSoundFilenameDialog();
	};

}

#endif
