
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

	// 1. free memory on GPU
	free::gpu_free(receivers);
	free::gpu_free(grid0s);
	free::gpu_free(sunray_);

	// 2. free memory on CPU
	free::cpu_free(receivers);
	free::cpu_free(grid0s);
	free::cpu_free(heliostats);
	free::cpu_free(sunray_);
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