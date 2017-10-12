
#include "solar_scene.h"
#include "scene_file_proc.h"

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
	return LoadSceneFromFile(filepath);
}

bool SolarScene::InitSolarScene(string filepath) {
	return LoadSceneFromFile(filepath);
}

bool SolarScene::LoadSceneFromFile(string filepath) {

	SceneFileProc proc;
	return proc.SceneFileRead(this, filepath);
}