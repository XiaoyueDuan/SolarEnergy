#include "Gtest.cuh"
#include "scene_instance_process.h"
 
void test(SolarScene &solar_scene)
{
	// 1
	SceneProcessor::set_grid_content(solar_scene.grid0s, solar_scene.heliostats);
	
	// 2
	float3 focus_center = solar_scene.receivers[0]->pos_;
	SceneProcessor::set_helio_content(solar_scene.heliostats, focus_center);

	// 3
	SceneProcessor::set_receiver_content(solar_scene.receivers);

	// 4
	SceneProcessor::set_sunray_content(*solar_scene.sunray_);
}