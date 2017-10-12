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

private:
	static SolarScene *m_instance;		//Singleton

public:
	float ground_length_;
	float ground_width_;
	int grid_num_;

	//scene object
	vector<Grid> grids;
	vector<Heliostat> heliostats;
	vector<Receiver> receivers;
};
