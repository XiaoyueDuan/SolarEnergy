#include "Gtest.cuh"
#include "scene_instance_process.h"
#include "recthelio_tracing.h"
#include "image_save.h"

#include <sstream>


namespace tmp
{
	template<typename T>
	void init_matrix(T *matrix, int size)
	{
		for (int i = 0; i < size; ++i)
			matrix[i] = 0;
	}

	void save_array(string filename, float *array, int size)
	{
		ofstream out(filename.c_str());
		for (int i = 0; i < size; ++i)
			out << array[i] << endl;
		out.close();
	}
};

void test(SolarScene &solar_scene)
{
	////// helios
	////float helio_granularity[] = { 0.01f, 0.02f };
	//
	////// rays
	////int sun_shape_per_group[] = { 1024, 2048 };
	////float csrs[] = { 0.1f, 0.15f, 0.2f };	
	////float disturb_stds[] = { 0.001,0.002,0.003 };
	//
	//// helios
	//float helio_granularity[] = { 0.01f };
	////float helio_granularity[] = { 0.02f, 0.05f, 0.1f };
	//
	//// rays
	//int sun_shape_per_group[] = { 128 };
	////int sun_shape_per_group[] = {512};
	//float csrs[] = { 0.1f };
	////float csrs[] = { 0.2f, 0.3f };
	//float disturb_stds[] = { 0.001 };
	////float disturb_stds[] = { 0.003 };
	//
	//int start_n = 0, end_n = 50, save_number = 2000;
	//string save_path("../result//try//128-128-_____.txt");
	//
	//float *h_image = nullptr;
	//
	//int index = 0;
	//Receiver *recv = dynamic_cast<RectangleReceiver *>(solar_scene.receivers[0]);
	//
	//
	//float *h_avg_img = new float[recv->resolution_.x*recv->resolution_.y];
	//tmp::init_matrix(h_avg_img, recv->resolution_.x*recv->resolution_.y);
	//
	////int helio_num[] = { 4, 14, 24, 34,
	////					20, 22, 26, 28, 29 };
	//int helio_num[] = { 24 };
	//
	//for (int id = 0; id < sizeof(helio_num) / sizeof(helio_num[0]); ++id)
	//{
	//	int i = helio_num[id];
	//	tmp::init_matrix(h_avg_img, recv->resolution_.x*recv->resolution_.y);
	//
	//	RectangleHelio *recthelio = dynamic_cast<RectangleHelio *>(solar_scene.heliostats[i]);
	//
	//	int avg_index = 0;
	//	for (int i_gral = 0; i_gral < sizeof(helio_granularity) / sizeof(float); ++i_gral)
	//	{
	//		recthelio->pixel_length_ = helio_granularity[i_gral];
	//		for (int j = start_n; j < end_n; ++j)
	//		{
	//			for (int i_n_per_group = 0; i_n_per_group < sizeof(sun_shape_per_group) / sizeof(int); ++i_n_per_group)
	//			{
	//				solar_scene.sunray_->num_sunshape_lights_per_group_ = sun_shape_per_group[i_n_per_group];
	//				solar_scene.sunray_->CClear();
	//				for (int i_csr = 0; i_csr < sizeof(csrs) / sizeof(float); ++i_csr)
	//				{
	//					solar_scene.sunray_->csr_ = csrs[i_csr];
	//					for (int i_dist = 0; i_dist < sizeof(disturb_stds) / sizeof(float); ++i_dist)
	//					{
	//						solarenergy::disturb_std = disturb_stds[i_dist];
	//						// reset sunray
	//						SceneProcessor::set_sunray_content(*solar_scene.sunray_);
	//
	//						// clean screen to all 0s
	//						recv->Cclean_image_content();
	//
	//						// ray-tracing
	//						recthelio_ray_tracing(*solar_scene.sunray_,
	//							*recv,
	//							*recthelio,
	//							*solar_scene.grid0s[i],
	//							solar_scene.heliostats);
	//
	//						// Save result
	//						global_func::gpu2cpu(h_image, recv->d_image_, recv->resolution_.x*recv->resolution_.y);
	//						// Id, Ssub, rou, Nc
	//						float Id = solar_scene.sunray_->dni_;
	//						float Ssub = recthelio->pixel_length_*recthelio->pixel_length_;
	//						float rou = solarenergy::reflected_rate;
	//						int Nc = solar_scene.sunray_->num_sunshape_lights_per_group_;
	//						float Srec = recv->pixel_length_*recv->pixel_length_;
	//						float max = -1.0f, max_avg = -1.0f;
	//						for (int p = 0; p < recv->resolution_.x*recv->resolution_.y; ++p)
	//						{
	//							h_image[p] = h_image[p] * Id * Ssub * rou / Nc / Srec;
	//							h_avg_img[p] = (h_avg_img[p] * float(j) + h_image[p]) / float(j + 1);
	//
	//							if (max < h_image[p])
	//								max = h_image[p];
	//
	//							if (max_avg < h_avg_img[p])
	//								max_avg = h_avg_img[p];
	//						}
	//
	//						if (j < save_number)
	//						{
	//							string tmp = save_path;
	//							tmp.insert(tmp.size() - 9, to_string(i));
	//							tmp.insert(tmp.size() - 8, to_string(j));
	//							tmp.insert(tmp.size() - 7, to_string(helio_granularity[i_gral]));
	//							tmp.insert(tmp.size() - 6, to_string(sun_shape_per_group[i_n_per_group]));
	//							tmp.insert(tmp.size() - 5, to_string(csrs[i_csr]));
	//							tmp.insert(tmp.size() - 4, to_string(disturb_stds[i_dist]));
	//							ImageSaver::savetxt(tmp, recv->resolution_.x, recv->resolution_.y, h_image);
	//						}
	//						
	//						printf("No.%d\n", ++index);
	//					}
	//				}
	//			}
	//			printf("(%d,\t%d)\n", i, j);
	//		}
	//	}
	//}
	//
	//delete[] h_image;
	//h_image = nullptr;
	//
	//delete[] h_avg_img;
	//h_avg_img = nullptr;



	RectangleHelio *recthelio = dynamic_cast<RectangleHelio *>(solar_scene.heliostats[24]);
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
	float max = -1.0f;
	for (int i = 0; i < solar_scene.receivers[0]->resolution_.x*solar_scene.receivers[0]->resolution_.y; ++i)
	{
		h_image[i] = h_image[i] * Id * Ssub * rou / Nc/ Srec;
	
		if (max < h_image[i])
			max = h_image[i];
	}
	
	// Save image	
	ImageSaver::savetxt("../result/24th-128.txt", solar_scene.receivers[0]->resolution_.x, solar_scene.receivers[0]->resolution_.y, h_image);
}