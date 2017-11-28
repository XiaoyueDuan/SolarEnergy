#pragma once

#include "common_var.h"
#include "grid.h"
#include "heliostat.cuh"
#include "random_generator.h"
#include "receiver.cuh"
#include "sunray.h"
#include "destroy.h"
#include "scene_instance_process.h"

//Singleton design model to  control the  access to resources
class SolarScene {
protected:
	SolarScene();

public:
	static SolarScene* GetInstance();   //static member
	static void InitInstance();
	~SolarScene();

	bool InitSolarScene(string filepath);
	bool InitContent();					// Call the method only if all grids, heliostats and receivers needs initializing. 
	bool ResetHelioNorm(float3 foucupoint);			    // reset heliostats focus point


private:
	static SolarScene *m_instance;		//Singleton
	bool InitSolarScece();              // only used in the InitInstance
	bool LoadSceneFromFile(string filepath);

public:
	float ground_length_;
	float ground_width_;
	int grid_num_;
	
	SunRay *sunray_;
	float3 focus_center_;  // focus point
	//scene object
	vector<Grid *> grid0s;
	vector<Heliostat *> heliostats;
	vector<Receiver *> receivers;
};
