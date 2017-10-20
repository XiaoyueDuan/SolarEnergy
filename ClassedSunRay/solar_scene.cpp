
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
	//init the sunray
	sunray_ = new SunRay(solarenergy::sun_dir,solarenergy::num_sunshape_groups,solarenergy::num_sunshape_lights_per_group,
		solarenergy::dni,solarenergy::csr);
	InitSolarScece();
}

SolarScene::~SolarScene() {
	if (sunray_) {
		delete sunray_;
	}
	
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