#pragma once

#include "common_var.h"
#include "grid.h"
#include "heliostat.h"
#include "random_generator.h"
#include "receiver.h"
#include "sunray.h"



//Singleton design model to  control the  access to resources
class SolarScene {
protected:
	SolarScene();

public:
	static SolarScene* GetInstance();   //static member
	static void InitInstance();
	~SolarScene();

	bool InitSolarScece();
	bool InitSolarScene(string filepath);
	bool LoadSceneFromFile(string filepath);
	//scene object
	Grid *grid_;
	Heliostat *heliostat_;




private:
	static SolarScene *m_instance;		//Singleton

};
