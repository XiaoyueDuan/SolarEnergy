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
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QTableWidget *tableWidget;
    QWidget *tab_2;
    QWidget *widget1;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox_2;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *SunLight)
    {
        if (SunLight->objectName().isEmpty())
            SunLight->setObjectName(QStringLiteral("SunLight"));
        SunLight->resize(629, 426);
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
        widget = new QWidget(tab);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 20, 521, 271));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        tableWidget = new QTableWidget(widget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 1, 1, 1, 1);

        sunLightWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        widget1 = new QWidget(tab_2);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(40, 50, 431, 141));
        gridLayout_2 = new QGridLayout(widget1);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(widget1);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));

        gridLayout_2->addWidget(doubleSpinBox, 0, 1, 1, 1);

        label_4 = new QLabel(widget1);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        doubleSpinBox_2 = new QDoubleSpinBox(widget1);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));

        gridLayout_2->addWidget(doubleSpinBox_2, 1, 1, 1, 1);

        sunLightWidget->addTab(tab_2, QString());
        widget2 = new QWidget(SunLight);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(300, 370, 301, 51));
        horizontalLayout = new QHBoxLayout(widget2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(widget2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget2);
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
