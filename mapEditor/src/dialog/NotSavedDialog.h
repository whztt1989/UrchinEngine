#ifndef ENGINE_MAPEDITOR_NOTSAVEDDIALOG_H
#define ENGINE_MAPEDITOR_NOTSAVEDDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

namespace urchin
{

	class NotSavedDialog : public QDialog
	{
		Q_OBJECT

		public:
			NotSavedDialog(QWidget *parent=0);

			bool needSave() const;

		private:
			bool bNeedSave;
			QDialogButtonBox *buttonBox;

		private slots:
			void buttonclick(QAbstractButton *);
	};

}

#endif
