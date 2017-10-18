/********************************************************************************
** Form generated from reading UI file 'sunlight.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUNLIGHT_H
#define UI_SUNLIGHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SunLight
{
public:
    QTabWidget *sunLightWidget;
    QWidget *tab;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QTableWidget *tableWidget;
    QWidget *tab_2;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox_2;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *SunLight)
    {
        if (SunLight->objectName().isEmpty())
            SunLight->setObjectName(QStringLiteral("SunLight"));
        SunLight->resize(629, 426);
        QIcon icon;
        icon.addFile(QStringLiteral("icons/lightKit.png"), QSize(), QIcon::Normal, QIcon::Off);
        SunLight->setWindowIcon(icon);
        sunLightWidget = new QTabWidget(SunLight);
        sunLightWidget->setObjectName(QStringLiteral("sunLightWidget"));
        sunLightWidget->setGeometry(QRect(20, 10, 581, 351));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sunLightWidget->sizePolicy().hasHeightForWidth());
        sunLightWidget->setSizePolicy(sizePolicy);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 521, 271));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        tableWidget = new QTableWidget(layoutWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 1, 1, 1, 1);

        sunLightWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        layoutWidget1 = new QWidget(tab_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(40, 50, 431, 141));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(layoutWidget1);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));

        gridLayout_2->addWidget(doubleSpinBox, 0, 1, 1, 1);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        doubleSpinBox_2 = new QDoubleSpinBox(layoutWidget1);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));

        gridLayout_2->addWidget(doubleSpinBox_2, 1, 1, 1, 1);

        sunLightWidget->addTab(tab_2, QString());
        layoutWidget2 = new QWidget(SunLight);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(300, 370, 301, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(layoutWidget2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        retranslateUi(SunLight);

        sunLightWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SunLight);
    } // setupUi

    void retranslateUi(QDialog *SunLight)
    {
        SunLight->setWindowTitle(QApplication::translate("SunLight", "SunLight", Q_NULLPTR));
        label->setText(QApplication::translate("SunLight", "Sunshape Type:", Q_NULLPTR));
        label_2->setText(QApplication::translate("SunLight", "Parameter:", Q_NULLPTR));
        sunLightWidget->setTabText(sunLightWidget->indexOf(tab), QApplication::translate("SunLight", "Sun Shape", Q_NULLPTR));
        label_3->setText(QApplication::translate("SunLight", "Azimuth(degrees from North):", Q_NULLPTR));
        label_4->setText(QApplication::translate("SunLight", "Elevation(degree):", Q_NULLPTR));
        sunLightWidget->setTabText(sunLightWidget->indexOf(tab_2), QApplication::translate("SunLight", "Sun Position", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SunLight", "Ok", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("SunLight", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SunLight: public Ui_SunLight {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUNLIGHT_H
