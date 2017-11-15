#pragma once
#include <QtWidgets/QTreeWidget>
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QRegExp>

#include "convert_type.h"
#include "../ClassedSunRay/solar_scene.h"
#include <vector>


class sceneTreeWidget : public QTreeWidget {
	Q_OBJECT

public:
	sceneTreeWidget(QWidget * parent = Q_NULLPTR);
	~sceneTreeWidget();

	void releaseData();
	void refreshData();

public slots:
	void openRowEditor(QTreeWidgetItem *item, int column);
	void closeRowEditor();
	void popMenu(const QPoint&);
	void addSceneNode();
	void deleteSceneNode();


private:
	QTreeWidgetItem* groundTree = nullptr;
	QTreeWidgetItem* receiverTree = nullptr;
	std::vector<QTreeWidgetItem*> gridTree;
	/*
	* parent       the parentNode ptr
	* key,value    the first and second columns              
	* dtype        represent the datatype
	* isCheck      0  no checkitem  1 checked  2 not checked
	* iconPath     the icon path
    */
	QTreeWidgetItem* addSelfItem(QTreeWidgetItem* parent, QString key, QString value, DataType dtype = DataType::TYPE_NONE, int isCheck = 0,QString iconPath=nullptr);
	
	QTreeWidgetItem* editItem = nullptr;
	int editColumn;

};
