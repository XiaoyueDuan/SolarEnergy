/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include <scenewindow.h>

QT_BEGIN_NAMESPACE

class Ui_GUIClass
{
public:
    QAction *actionopen;
    QAction *actionsave;
    QAction *actionsave_as;
    QAction *actionSunLight;
    QAction *actionTranmissvity;
    QAction *actionCreate_Scene;
    QAction *actionOpen_Scene;
    QAction *actionreload;
    QAction *actionrecent_file;
    QAction *actionConstant_Variable;
    QAction *actionrun;
    QAction *actionFlux_Analysis;
    QAction *actionRayTrace_Option;
    QAction *actionAbout;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter_2;
    SceneWindow *sceneWidget;
    QSplitter *splitter;
    QTreeWidget *nodeTreeWidget;
    QTableWidget *parameterTableWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEnvironment;
    QMenu *menuScene;
    QMenu *menuRay_Trace;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GUIClass)
    {
        if (GUIClass->objectName().isEmpty())
            GUIClass->setObjectName(QStringLiteral("GUIClass"));
        GUIClass->setEnabled(true);
        GUIClass->resize(1265, 853);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(GUIClass->sizePolicy().hasHeightForWidth());
        GUIClass->setSizePolicy(sizePolicy);
        GUIClass->setMinimumSize(QSize(1265, 853));
        GUIClass->setMaximumSize(QSize(10000, 10000));
        QIcon icon;
        icon.addFile(QStringLiteral(":/GUI/icons/sunIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        GUIClass->setWindowIcon(icon);
        actionopen = new QAction(GUIClass);
        actionopen->setObjectName(QStringLiteral("actionopen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/GUI/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionopen->setIcon(icon1);
        actionsave = new QAction(GUIClass);
        actionsave->setObjectName(QStringLiteral("actionsave"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/GUI/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsave->setIcon(icon2);
        actionsave_as = new QAction(GUIClass);
        actionsave_as->setObjectName(QStringLiteral("actionsave_as"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/GUI/icons/saveas.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsave_as->setIcon(icon3);
        actionSunLight = new QAction(GUIClass);
        actionSunLight->setObjectName(QStringLiteral("actionSunLight"));
        actionTranmissvity = new QAction(GUIClass);
        actionTranmissvity->setObjectName(QStringLiteral("actionTranmissvity"));
        actionCreate_Scene = new QAction(GUIClass);
        actionCreate_Scene->setObjectName(QStringLiteral("actionCreate_Scene"));
        actionOpen_Scene = new QAction(GUIClass);
        actionOpen_Scene->setObjectName(QStringLiteral("actionOpen_Scene"));
        actionreload = new QAction(GUIClass);
        actionreload->setObjectName(QStringLiteral("actionreload"));
        actionrecent_file = new QAction(GUIClass);
        actionrecent_file->setObjectName(QStringLiteral("actionrecent_file"));
        actionConstant_Variable = new QAction(GUIClass);
        actionConstant_Variable->setObjectName(QStringLiteral("actionConstant_Variable"));
        actionrun = new QAction(GUIClass);
        actionrun->setObjectName(QStringLiteral("actionrun"));
        actionFlux_Analysis = new QAction(GUIClass);
        actionFlux_Analysis->setObjectName(QStringLiteral("actionFlux_Analysis"));
        actionRayTrace_Option = new QAction(GUIClass);
        actionRayTrace_Option->setObjectName(QStringLiteral("actionRayTrace_Option"));
        actionAbout = new QAction(GUIClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(GUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter_2 = new QSplitter(centralWidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy1);
        splitter_2->setOrientation(Qt::Horizontal);
        sceneWidget = new SceneWindow(splitter_2);
        sceneWidget->setObjectName(QStringLiteral("sceneWidget"));
        sizePolicy.setHeightForWidth(sceneWidget->sizePolicy().hasHeightForWidth());
        sceneWidget->setSizePolicy(sizePolicy);
        splitter_2->addWidget(sceneWidget);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy2);
        splitter->setOrientation(Qt::Vertical);
        nodeTreeWidget = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("Node"));
        nodeTreeWidget->setHeaderItem(__qtreewidgetitem);
        new QTreeWidgetItem(nodeTreeWidget);
        new QTreeWidgetItem(nodeTreeWidget);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(nodeTreeWidget);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        nodeTreeWidget->setObjectName(QStringLiteral("nodeTreeWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(nodeTreeWidget->sizePolicy().hasHeightForWidth());
        nodeTreeWidget->setSizePolicy(sizePolicy3);
        splitter->addWidget(nodeTreeWidget);
        parameterTableWidget = new QTableWidget(splitter);
        if (parameterTableWidget->columnCount() < 2)
            parameterTableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        parameterTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        parameterTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (parameterTableWidget->rowCount() < 2)
            parameterTableWidget->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        parameterTableWidget->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        parameterTableWidget->setVerticalHeaderItem(1, __qtablewidgetitem3);
        parameterTableWidget->setObjectName(QStringLiteral("parameterTableWidget"));
        sizePolicy3.setHeightForWidth(parameterTableWidget->sizePolicy().hasHeightForWidth());
        parameterTableWidget->setSizePolicy(sizePolicy3);
        parameterTableWidget->setColumnCount(2);
        splitter->addWidget(parameterTableWidget);
        splitter_2->addWidget(splitter);

        horizontalLayout->addWidget(splitter_2);

        GUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1265, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEnvironment = new QMenu(menuBar);
        menuEnvironment->setObjectName(QStringLiteral("menuEnvironment"));
        menuScene = new QMenu(menuBar);
        menuScene->setObjectName(QStringLiteral("menuScene"));
        menuRay_Trace = new QMenu(menuBar);
        menuRay_Trace->setObjectName(QStringLiteral("menuRay_Trace"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        GUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GUIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GUIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GUIClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEnvironment->menuAction());
        menuBar->addAction(menuScene->menuAction());
        menuBar->addAction(menuRay_Trace->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionopen);
        menuFile->addAction(actionsave);
        menuFile->addAction(actionsave_as);
        menuFile->addSeparator();
        menuFile->addAction(actionreload);
        menuFile->addAction(actionrecent_file);
        menuEnvironment->addAction(actionSunLight);
        menuEnvironment->addAction(actionTranmissvity);
        menuEnvironment->addAction(actionConstant_Variable);
        menuScene->addAction(actionCreate_Scene);
        menuScene->addAction(actionOpen_Scene);
        menuRay_Trace->addAction(actionrun);
        menuRay_Trace->addAction(actionFlux_Analysis);
        menuRay_Trace->addSeparator();
        menuRay_Trace->addAction(actionRayTrace_Option);
        menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionopen);
        mainToolBar->addAction(actionsave);
        mainToolBar->addAction(actionsave_as);

        retranslateUi(GUIClass);

        QMetaObject::connectSlotsByName(GUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *GUIClass)
    {
        GUIClass->setWindowTitle(QApplication::translate("GUIClass", "SolarEnergy", Q_NULLPTR));
        actionopen->setText(QApplication::translate("GUIClass", "open", Q_NULLPTR));
        actionsave->setText(QApplication::translate("GUIClass", "save", Q_NULLPTR));
        actionsave_as->setText(QApplication::translate("GUIClass", "save as", Q_NULLPTR));
        actionSunLight->setText(QApplication::translate("GUIClass", "Sun Light", Q_NULLPTR));
        actionTranmissvity->setText(QApplication::translate("GUIClass", "Tranmissvity", Q_NULLPTR));
        actionCreate_Scene->setText(QApplication::translate("GUIClass", "Create Scene", Q_NULLPTR));
        actionOpen_Scene->setText(QApplication::translate("GUIClass", "Open Scene", Q_NULLPTR));
        actionreload->setText(QApplication::translate("GUIClass", "reload", Q_NULLPTR));
        actionrecent_file->setText(QApplication::translate("GUIClass", "recent file", Q_NULLPTR));
        actionConstant_Variable->setText(QApplication::translate("GUIClass", "Constant Variable", Q_NULLPTR));
        actionrun->setText(QApplication::translate("GUIClass", "Run", Q_NULLPTR));
        actionFlux_Analysis->setText(QApplication::translate("GUIClass", "Flux Analysis", Q_NULLPTR));
        actionRayTrace_Option->setText(QApplication::translate("GUIClass", "RayTrace Option", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("GUIClass", "About", Q_NULLPTR));

        const bool __sortingEnabled = nodeTreeWidget->isSortingEnabled();
        nodeTreeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem = nodeTreeWidget->topLevelItem(0);
        ___qtreewidgetitem->setText(0, QApplication::translate("GUIClass", "ground", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem1 = nodeTreeWidget->topLevelItem(1);
        ___qtreewidgetitem1->setText(0, QApplication::translate("GUIClass", "receiver", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem2 = nodeTreeWidget->topLevelItem(2);
        ___qtreewidgetitem2->setText(0, QApplication::translate("GUIClass", "grid", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem2->child(0);
        ___qtreewidgetitem3->setText(0, QApplication::translate("GUIClass", "heliostat0", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem2->child(1);
        ___qtreewidgetitem4->setText(0, QApplication::translate("GUIClass", "heliostat1", Q_NULLPTR));
        nodeTreeWidget->setSortingEnabled(__sortingEnabled);

        QTableWidgetItem *___qtablewidgetitem = parameterTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("GUIClass", "parameter", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = parameterTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("GUIClass", "value", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("GUIClass", "File", Q_NULLPTR));
        menuEnvironment->setTitle(QApplication::translate("GUIClass", "Environment", Q_NULLPTR));
        menuScene->setTitle(QApplication::translate("GUIClass", "Scene", Q_NULLPTR));
        menuRay_Trace->setTitle(QApplication::translate("GUIClass", "Ray Trace", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("GUIClass", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GUIClass: public Ui_GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
