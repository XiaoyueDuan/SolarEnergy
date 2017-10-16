#include "gui.h"
#include "test/glwidget.h"
#include <QtWidgets/QApplication>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//GLWidget gl;
	//gl.show();
	GUI w;
	w.show();
	return a.exec();
}
