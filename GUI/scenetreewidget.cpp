#include "scenetreewidget.hpp"
#include <QtWidgets/QTreeWidget>
#include "../ClassedSunRay/solar_scene.h"


sceneTreeWidget::sceneTreeWidget(QWidget * parent) : QTreeWidget(parent) {
	setHeaderLabels(QStringList() << "Key" << "Value");
	//refresh data
	refreshData();

	//connect
	connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this,SLOT(openRowEditor(QTreeWidgetItem*, int)));
	connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(closeRowEditor()));
	setStyleSheet("QTreeWidget::item{height:20px}");
}

sceneTreeWidget::~sceneTreeWidget() {
	if (groundTree) delete groundTree;
	if (receiverTree) delete receiverTree;
	if (!gridTree.empty()) {
		for (auto &e : gridTree) {
			delete e;
			e = nullptr;
		}
	}
}
QTreeWidgetItem* sceneTreeWidget::addSelfItem(QTreeWidgetItem* parent, QString key, QString value, DataType dtype, int isCheck,QString iconPath) {
	QStringList columItemList;
	QTreeWidgetItem *child;
	columItemList << key << value <<QString::number(dtype);
	child = new QTreeWidgetItem(columItemList);
	if (iconPath!=nullptr) {
		child->setIcon(0,QIcon(iconPath));
	}
	if (isCheck) {
		if (isCheck == 1) {
			child->setCheckState(0, Qt::Checked);
		}
		else {
			child->setCheckState(0, Qt::Unchecked);
		}
	}
	parent->addChild(child);
	return child;
}


void sceneTreeWidget::refreshData() {
	// set the init data
	groundTree = new QTreeWidgetItem(QStringList() << "ground" << " " << QString::number(DataType::TYPE_NONE));
	groundTree->setIcon(0, QIcon(":/GUI/icons/viewer_viewSun.png"));
	receiverTree = new QTreeWidgetItem(QStringList() << "receiver" << " " << QString::number(DataType::TYPE_NONE));
	receiverTree->setIcon(0, QIcon(":/GUI/icons/separatorKit.png"));
	addTopLevelItem(groundTree);
	addTopLevelItem(receiverTree);

	SolarScene *solar_scene;
	solar_scene = SolarScene::GetInstance();
	// init the ground scene
	QString key, value;
	key = "length";
	value = QString::number(solar_scene->ground_length_);
	addSelfItem(groundTree, key, value, DataType::TYPE_FLOAT);
	key = "width";
	value = QString::number(solar_scene->ground_width_);
	addSelfItem(groundTree, key, value, DataType::TYPE_FLOAT);
	key = "ngrid";
	value = QString::number(solar_scene->grid_num_);
	addSelfItem(groundTree, key, value, DataType::TYPE_NONE);
	
	//init the receiver: add check 
	int receiver_num = solar_scene->receivers.size();
	for (int i = 0; i < receiver_num; i++) {
		//add the receiver 
		key = "rece_"+ QString::number(i);
		value = "";
		QTreeWidgetItem* rece = addSelfItem(receiverTree, key, value, DataType::TYPE_NONE,2,QString(":/GUI/icons/receiver.png"));
		//params
		key = "pos";
		value = float3_to_string(solar_scene->receivers[i]->pos_);
		addSelfItem(rece, key, value, DataType::TYPE_FLOAT3);
		key = "size";
		value = float3_to_string(solar_scene->receivers[i]->size_);
		addSelfItem(rece, key, value, DataType::TYPE_FLOAT3);
		key = "norm";
		value = float3_to_string(solar_scene->receivers[i]->normal_);
		addSelfItem(rece, key, value, DataType::TYPE_NONE);
	}

	//init the helio: add check
	int grid_num = solar_scene->grid0s.size();
	for (int i = 0; i < grid_num;i++) {
		QString grid_name = "grid_"+ QString::number(i);
		QTreeWidgetItem* gridTree_t = new QTreeWidgetItem(QStringList() << grid_name);
		gridTree_t->setIcon(0, QIcon(":/GUI/icons/tcube.png"));
		addTopLevelItem(gridTree_t);
		RectGrid *cur_grid;
		if (solar_scene->grid0s[i]->type_ == 0) {
			cur_grid = dynamic_cast<RectGrid*>(solar_scene->grid0s[i]);
			key = "pos";
			value = float3_to_string(cur_grid->pos_);
			addSelfItem(gridTree_t, key, value, DataType::TYPE_FLOAT3);
			key = "size";
			value = float3_to_string(cur_grid->size_);
			addSelfItem(gridTree_t, key, value, DataType::TYPE_FLOAT3);
			key = "interval";
			value = float3_to_string(cur_grid->interval_);
			addSelfItem(gridTree_t, key, value, DataType::TYPE_FLOAT3);
			key = "face";
			value = QString::number(cur_grid->helio_type_);
			addSelfItem(gridTree_t, key,value, DataType::TYPE_NONE);

		}
		//add helioStat
		int grid_start_helio_pos = solar_scene->grid0s[i]->start_helio_pos_;
		int total_helios = solar_scene->grid0s[i]->num_helios_;
		for (int j = 0; j < total_helios; j++) {
			int helio_index = grid_start_helio_pos + j;
			//add the helio 
			key = "helio_" + QString::number(helio_index);
			value = "";
			QTreeWidgetItem* helio = addSelfItem(gridTree_t, key, value, DataType::TYPE_NONE,2, QString(":/GUI/icons/helio.png"));
			//params
			key = "pos";
			value = float3_to_string(solar_scene->heliostats[helio_index]->pos_);
			addSelfItem(helio, key, value, DataType::TYPE_FLOAT3);
			key = "size";
			value = float3_to_string(solar_scene->heliostats[helio_index]->size_);
			addSelfItem(helio, key, value, DataType::TYPE_FLOAT3);
			key = "norm";
			value = float3_to_string(solar_scene->heliostats[helio_index]->normal_);
			addSelfItem(helio, key, value, DataType::TYPE_FLOAT3);
			key = "gap";
			value = float2_to_string(solar_scene->heliostats[helio_index]->gap_);
			addSelfItem(helio, key, value, DataType::TYPE_FLOAT2);
			key = "matric";
			value = int2_to_string(solar_scene->heliostats[helio_index]->row_col_);
			addSelfItem(helio, key, value, DataType::TYPE_INT2);
		}
	}
}


void sceneTreeWidget::openRowEditor(QTreeWidgetItem *item, int column) {
	if (column == 1)
	{
		openPersistentEditor(item, column);// 设置某一item可以编辑
		editItem = item;
		editColumn = column;
	}
}

void sceneTreeWidget::closeRowEditor() {
	if (editItem != nullptr) {
		closePersistentEditor(editItem, editColumn);// 设置某一item不可编辑
		editItem = nullptr;
	}
}