#ifndef GUI_H
#define GUI_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "GeneratedFiles/ui_gui.h"

class GUI : public QMainWindow
{
	Q_OBJECT
public:
	GUI(QWidget *parent = 0);
	~GUI();
	void saveSceneFile();  // TO-DO

private:
	void initParamerter();
	
private slots:
	void openFile();
	void saveFile();
	void saveAsFile();
	void setSunLight();

private:
	Ui::GUIClass ui;
	QString curFilePath;
	bool curFileModified;
	



};

#endif // GUI_H
