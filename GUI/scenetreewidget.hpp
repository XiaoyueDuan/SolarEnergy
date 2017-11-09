#pragma once
#include <QtWidgets/QTreeWidget>
#include "convert_type.h"
#include <vector>

class sceneTreeWidget : public QTreeWidget {
	Q_OBJECT

public:
	sceneTreeWidget(QWidget * parent = Q_NULLPTR);
	~sceneTreeWidget();

	void refreshData();

public slots:
	void openRowEditor(QTreeWidgetItem *item, int column);
	void closeRowEditor();



private:
	QTreeWidgetItem* groundTree = nullptr;
	QTreeWidgetItem* receiverTree = nullptr;
	std::vector<QTreeWidgetItem*> gridTree;
	QTreeWidgetItem* addSelfItem(QTreeWidgetItem* parent, QString key, QString value, DataType dtype = DataType::TYPE_NONE, int isCheck = 0,QString iconPath=nullptr);
	
	QTreeWidgetItem* editItem = nullptr;
	int editColumn;

};
