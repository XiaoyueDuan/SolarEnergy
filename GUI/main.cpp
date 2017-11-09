#include "gui.h"
#include "test/glwidget.h"
#include <QtWidgets/QApplication>
#include <QDebug>
// ray tracing part
#include "../ClassedSunRay/solar_scene.h"
#include "../ClassedSunRay/Gtest.cuh"

#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//init the solar Scene
	SolarScene *solar_scene;
	solar_scene =  SolarScene::GetInstance();
	GUI w;
	w.show();
	return a.exec();
}
