#pragma once
#include <QDialog>
#include "GeneratedFiles/ui_sunlight.h"

class SunLight : public QDialog {
	Q_OBJECT

public:
	SunLight(QWidget * parent = Q_NULLPTR);
	~SunLight();

private:
	Ui::SunLight ui;

};
