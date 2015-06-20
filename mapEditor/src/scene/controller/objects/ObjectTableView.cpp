#include <QHeaderView>
#include <QVariant>

#include "ObjectTableView.h"

namespace urchin
{

	ObjectTableView::ObjectTableView(QWidget *parent) :
		QTableView(parent)
	{
		objectsListModel = new QStandardItemModel(0, 2, this);
		objectsListModel->setHorizontalHeaderItem(0, new QStandardItem("Object Name"));
		objectsListModel->setHorizontalHeaderItem(1, new QStandardItem("Mesh File"));
		setModel(objectsListModel);

		horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
		horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive);
		horizontalHeader()->resizeSection(0, 90);
		horizontalHeader()->resizeSection(1, 230);
		verticalHeader()->hide();

		setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
		setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	}

	void ObjectTableView::selectionChanged(const QItemSelection &, const QItemSelection &)
	{
		//hack to refresh selection
		horizontalHeader()->resizeSection(0, 91);
		horizontalHeader()->resizeSection(0, 90);

		notifyObservers(this, NotificationType::SELECTION_CHANGED);
	}

	bool ObjectTableView::hasSceneObjectSelected() const
	{
		return this->currentIndex().row()!=-1;
	}

	const SceneObject *ObjectTableView::getSelectedSceneObject() const
	{
		QModelIndex selectedIndex = this->currentIndex();
		if(selectedIndex.row()!=-1)
		{
			return selectedIndex.data(Qt::UserRole + 1).value<const SceneObject *>();
		}
		return nullptr;
	}

	void ObjectTableView::addObject(const SceneObject *sceneObject)
	{
		QStandardItem *itemObjectName = new QStandardItem(QString::fromStdString(sceneObject->getName()));
		itemObjectName->setData(qVariantFromValue(sceneObject), Qt::UserRole + 1);
		itemObjectName->setEditable(false);

		QStandardItem *itemMeshFile = new QStandardItem(QString::fromStdString(sceneObject->getModel()->getMeshes()->getMeshFilename()));
		itemMeshFile->setData(qVariantFromValue(sceneObject), Qt::UserRole + 1);
		itemMeshFile->setEditable(false);

		int nextRow = objectsListModel->rowCount();
		objectsListModel->insertRow(nextRow);
		objectsListModel->setItem(nextRow, 0, itemObjectName);
		objectsListModel->setItem(nextRow, 1, itemMeshFile);

		resizeRowsToContents();
	}

	bool ObjectTableView::removeSelectedObject()
	{
		if(hasSceneObjectSelected())
		{
			objectsListModel->removeRow(this->currentIndex().row());
			resizeRowsToContents();

			return true;
		}

		return false;
	}

	void ObjectTableView::removeAllObjects()
	{
		objectsListModel->removeRows(0, objectsListModel->rowCount());
		resizeRowsToContents();
	}

}