#pragma once

#include "solar_scene.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <string>

// Value-Defintions of the different String values
static enum StringValue {
	ground,
	receiver,
	grid,
	heliostat
};


class SceneFileProc{
public:
	SceneFileProc();
	bool SceneFileRead(SolarScene *solarscene, std::string filepath);
private:
	SolarScene *solarScene_;  //eqaul the Scolar::GetInstance
	// Map to associate the strings with the enum values
	std::map<std::string, StringValue> string_value_read_map;

};