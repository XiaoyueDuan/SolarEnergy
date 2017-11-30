#include "Gtest.cuh"
#include "scene_instance_process.h"
#include "recthelio_tracing.h"
#include "image_save.h"
 
void test(SolarScene &solar_scene)
{
	//solar_scene.InitContent();
	
	RectangleHelio *recthelio = dynamic_cast<RectangleHelio *>(solar_scene.heliostats[0]);
	recthelio_ray_tracing(*solar_scene.sunray_,
							*solar_scene.receivers[0],
							*recthelio,
							*solar_scene.grid0s[0],
							solar_scene.heliostats);

	float *h_image = nullptr;
	global_func::gpu2cpu(h_image, solar_scene.receivers[0]->d_image_, solar_scene.receivers[0]->resolution_.x*solar_scene.receivers[0]->resolution_.y);
	// Id, Ssub, rou, Nc
	float Id=solar_scene.sunray_->dni_;
	float Ssub = recthelio->pixel_length_*recthelio->pixel_length_;
	float rou = solarenergy::reflected_rate;
	int Nc = solar_scene.sunray_->num_sunshape_lights_per_group_;
	float Srec = solar_scene.receivers[0]->pixel_length_*solar_scene.receivers[0]->pixel_length_;
	for (int i = 0; i < solar_scene.receivers[0]->resolution_.x*solar_scene.receivers[0]->resolution_.y; ++i)
	{
		h_image[i] = h_image[i] * Id * Ssub * rou / Nc/ Srec;
	}

	// Save image	
	ImageSaver::savetxt("face2face_shadow-1.txt", solar_scene.receivers[0]->resolution_.x, solar_scene.receivers[0]->resolution_.y, h_image);
}