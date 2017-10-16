#include "gui.h"
#include "sunlight.hpp"


GUI::GUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.actionopen,&QAction::triggered, this,&GUI::openFile);
	connect(ui.actionsave, &QAction::triggered, this, &GUI::saveFile);
	connect(ui.actionsave_as, &QAction::triggered, this, &GUI::saveAsFile);
	connect(ui.actionSunLight, &QAction::triggered, this, &GUI::setSunLight);

}

GUI::~GUI()
{

}

void GUI::initParamerter() {
	curFilePath = "";
	curFileModified = false;
}
void GUI::saveSceneFile() {
	//to save the filePath
	
}




void GUI::openFile() {
	QString path = QFileDialog::getOpenFileName(this,
		tr("Open File"),
		".",
		tr("Scene Files(*.scn)"));
	curFilePath = path;  //save the file path
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Read File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		QMessageBox::warning(this, tr("Read File"),
			tr("open file:\n%1").arg(path));
		return;
		/*QTextStream in(&file);
		textEdit->setText(in.readAll());
		file.close();*/
	}
	else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}
};

void GUI::saveFile() {
	// file is not modified
	if (!curFileModified) {  
		return;
	}
	QString path = curFilePath;
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Write File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		//saveSceneFile();  //save the scene paramater
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}
};

void GUI::saveAsFile() {
	QString path = QFileDialog::getSaveFileName(this,
							tr("Open File"),
							".",
							tr("Text Files(*.scn)"));
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Write File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		saveSceneFile();  //save the scene paramater
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}


}

void GUI::setSunLight() {
	SunLight sunlight;
	sunlight.exec();

}