#include "solar_scene.h"
#include <fstream>
#include <sstream>
#include <iostream>

SolarScene* SolarScene::m_instance;
SolarScene* SolarScene::GetInstance()
{
	if (m_instance == NULL) InitInstance();
	return m_instance;
}

void SolarScene::InitInstance()
{
	m_instance = new SolarScene();
}

SolarScene::SolarScene() {
	//init the random
	RandomGenerator::initSeed();
	InitSolarScece();
}

SolarScene::~SolarScene() {

}


bool SolarScene::InitSolarScece() {
	string filepath = solarenergy::scene_filepath;
	return InitSolarScene(filepath);
}

bool SolarScene::InitSolarScene(string filepath) {
	return LoadSceneFromFile(filepath);
}

bool SolarScene::LoadSceneFromFile(string filepath) {

	std::string scene_line_code;
	std::ifstream scene_file;
	// ensure ifstream objects can throw exceptions:
	scene_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		//openfile
		scene_file.open(filepath);
		stringstream scene_stream;
		// read file's buffer contents into streams
		scene_stream << scene_file.rdbuf();
		//close the file handlers
		scene_file.close();
		while (scene_stream >> scene_line_code) {
			std::cout << scene_line_code << std::endl;
		}


	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return false;
	}

	return true;
}