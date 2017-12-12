#include "Gtest.cuh"
#include "scene_instance_process.h"
#include "recthelio_tracing.h"
#include "image_save.h"

#include <sstream>

namespace tmp {
	// Step 2: Generate micro-heliostats' normals
	__global__ void map_microhelio_normals(float3 *d_microhelio_normals, const float3 *d_microhelio_centers,
		float3 normal,
		const size_t size)
	{
		unsigned long long int myId = global_func::getThreadId();
		if (myId >= size)
			return;

		d_microhelio_normals[myId] = normal;
	}
	
	//// Step 2: Generate micro-heliostats' normals
	//__global__ void map_microhelio_normals(float3 *d_microhelio_normals, const float3 *d_microhelio_centers,
	//	float3 normal,
	//	const size_t size)
	//{
	//	unsigned long long int myId = global_func::getThreadId();
	//	if (myId >= size)
	//		return;

	//	float3 local_normal = d_microhelio_normals[myId];
	//	local_normal = global_func::local2world(local_normal, normal);
	//	local_normal = normalize(local_normal);
	//	d_microhelio_normals[myId] = local_normal;
	//}

	// Step 3: Transform local micro-helio center to world postion
	__global__ void map_microhelio_center2world(float3 *d_microhelio_world_centers, float3 *d_microhelio_local_centers,
		const float3 normal, const float3 world_pos,
		const size_t size)
	{
		unsigned long long int myId = global_func::getThreadId();
		if (myId >= size)
			return;

		float3 local = d_microhelio_local_centers[myId];
		local = global_func::local2world(local, normal);		// Then Rotate
		local = global_func::transform(local, world_pos);		// Translation to the world system
		d_microhelio_world_centers[myId] = local;
	}
}


void test(SolarScene &solar_scene)
{
	solar_scene.InitContent();
	
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
	float max = -1.0f;
	for (int i = 0; i < solar_scene.receivers[0]->resolution_.x*solar_scene.receivers[0]->resolution_.y; ++i)
	{
		h_image[i] = h_image[i] * Id * Ssub * rou / Nc/ Srec;
	
		if (max < h_image[i])
			max = h_image[i];
	}
	
	// Save image	
	ImageSaver::savetxt("../result/validate-with-paper.txt", solar_scene.receivers[0]->resolution_.x, solar_scene.receivers[0]->resolution_.y, h_image);

	//// load centers & normals
	//ifstream in("../userData/check_with_real_data/sandun.txt");
	//if (in.fail())
	//{
	//	cout << "The file does not exist!" << endl;
	//	return;
	//}

	//// step 2: prepare for data loading	
	//streambuf *cinbuf = cin.rdbuf();	//save old buf
	//cin.rdbuf(in.rdbuf());				//redirect cin to file
	//istringstream ss;
	//
	//int N;
	//cin >> N;	
	//float3 *h_microhelio_normals = new float3[N];		// micro-heliostat's normal
	//float3 *h_microhelio_origs = new float3[N];			// micro-heliostat's origins
	//
	//string line;
	//for (int i = 0; i < N; )
	//{
	//	getline(cin, line);
	//	if (line.empty() || line.substr(0, 2) == "//")	// empty or comment
	//		continue;

	//	ss.str(line); ss.clear();
	//	ss >> h_microhelio_origs[i].x;
	//	ss >> h_microhelio_origs[i].y;
	//	ss >> h_microhelio_origs[i].z;
	//	ss >> h_microhelio_normals[i].x;
	//	ss >> h_microhelio_normals[i].y;
	//	ss >> h_microhelio_normals[i].z;
	//	++i;
	//}
	//cin.rdbuf(cinbuf);

	//// transfer to gpu
	//float3 *d_microhelio_normals = nullptr;		// micro-heliostat's normal
	//float3 *d_microhelio_origs = nullptr;			// micro-heliostat's origins
	//global_func::cpu2gpu(d_microhelio_normals, h_microhelio_normals, N);
	//global_func::cpu2gpu(d_microhelio_origs, h_microhelio_origs, N);

	//delete[] h_microhelio_normals;
	//delete[] h_microhelio_origs;
	//h_microhelio_normals = nullptr;
	//h_microhelio_origs = nullptr;
	//
	//// tracing 1st
	//RectGrid *rectgrid0 = dynamic_cast<RectGrid *> (solar_scene.grid0s[0]);
	//RectangleReceiver *rect_receiver0 = dynamic_cast<RectangleReceiver *> (solar_scene.receivers[0]);

	//// d_helio_vertexs
	//int start_pos = rectgrid0->start_helio_pos_;
	//int end_pos = start_pos + rectgrid0->num_helios_;
	//float3 *d_helio_vertexs = nullptr;
	//set_helios_vertexes(solar_scene.heliostats, start_pos, end_pos, d_helio_vertexs);
	//cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

	//// d_microhelio_groups
	//int *d_microhelio_groups = nullptr;
	//set_microhelio_groups(d_microhelio_groups, solar_scene.sunray_->num_sunshape_groups_, N);
	//cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

	//
	//// micro-center local2world
	//int nThreads;
	//dim3 nBlocks;
	//global_func::setThreadsBlocks(nBlocks, nThreads, N);
	//tmp::map_microhelio_center2world <<<nBlocks, nThreads >>> (d_microhelio_origs, d_microhelio_origs,
	//	solar_scene.heliostats[0]->normal_, solar_scene.heliostats[0]->pos_, N);

	//// micro-normal local2world
	//tmp::map_microhelio_normals << <nBlocks, nThreads >> > 
	//	(d_microhelio_normals, d_microhelio_origs, solar_scene.heliostats[0]->normal_, N);

	//// Tracing	
	//nThreads = 256;
	//nBlocks;
	//global_func::setThreadsBlocks(nBlocks, nThreads, N*(solar_scene.sunray_->num_sunshape_lights_per_group_), true);
	//map_tracing <<<nBlocks, nThreads >>>(*solar_scene.sunray_, *rectgrid0, *rect_receiver0,
	//	d_helio_vertexs, d_microhelio_normals, d_microhelio_origs, d_microhelio_groups,
	//	N);
	//cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());


	//float *h_image = nullptr;
	//global_func::gpu2cpu(h_image, solar_scene.receivers[0]->d_image_, solar_scene.receivers[0]->resolution_.x*solar_scene.receivers[0]->resolution_.y);
	//// Id, Ssub, rou, Nc
	//float Id=solar_scene.sunray_->dni_;
	//float Ssub = 0.005;
	//float rou = solarenergy::reflected_rate;
	//int Nc = solar_scene.sunray_->num_sunshape_lights_per_group_;
	//float Srec = solar_scene.receivers[0]->pixel_length_*solar_scene.receivers[0]->pixel_length_;
	//float max = -1.0f;
	//for (int i = 0; i < solar_scene.receivers[0]->resolution_.x*solar_scene.receivers[0]->resolution_.y; ++i)
	//{
	//	h_image[i] = h_image[i] * Id * Ssub * rou / Nc/ Srec;
	//
	//	if (max < h_image[i])
	//		max = h_image[i];
	//}
	//
	//// Save image	
	//ImageSaver::savetxt("real_1.txt", solar_scene.receivers[0]->resolution_.x, solar_scene.receivers[0]->resolution_.y, h_image);
	//delete[] h_image;
	//h_image = nullptr;

	////// tracing 1st
	////RectGrid *rectgrid0 = dynamic_cast<RectGrid *> (solar_scene.grid0s[1]);
	////RectangleReceiver *rect_receiver0 = dynamic_cast<RectangleReceiver *> (solar_scene.receivers[1]);

	////// d_helio_vertexs
	////int start_pos = rectgrid0->start_helio_pos_;
	////int end_pos = start_pos + rectgrid0->num_helios_;
	////float3 *d_helio_vertexs = nullptr;
	////set_helios_vertexes(solar_scene.heliostats, start_pos, end_pos, d_helio_vertexs);
	////cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

	////// d_microhelio_groups
	////int *d_microhelio_groups = nullptr;
	////set_microhelio_groups(d_microhelio_groups, solar_scene.sunray_->num_sunshape_groups_, N);
	////cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());


	////// micro-center local2world
	////int nThreads;
	////dim3 nBlocks;
	////global_func::setThreadsBlocks(nBlocks, nThreads, N);
	////tmp::map_microhelio_center2world << <nBlocks, nThreads >> > (d_microhelio_origs, d_microhelio_origs,
	////	solar_scene.heliostats[1]->normal_, solar_scene.heliostats[1]->pos_, N);

	////// micro-normal local2world
	////tmp::map_microhelio_normals << <nBlocks, nThreads >> >
	////	(d_microhelio_normals, d_microhelio_origs, solar_scene.heliostats[1]->normal_, N);

	////// Tracing	
	////nThreads = 256;
	////nBlocks;
	////global_func::setThreadsBlocks(nBlocks, nThreads, N*(solar_scene.sunray_->num_sunshape_lights_per_group_), true);
	////map_tracing << <nBlocks, nThreads >> >(*solar_scene.sunray_, *rectgrid0, *rect_receiver0,
	////	d_helio_vertexs, d_microhelio_normals, d_microhelio_origs, d_microhelio_groups,
	////	N);
	////cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());


	////float *h_image = nullptr;
	////global_func::gpu2cpu(h_image, solar_scene.receivers[1]->d_image_, solar_scene.receivers[1]->resolution_.x*solar_scene.receivers[1]->resolution_.y);
	////// Id, Ssub, rou, Nc
	////float Id = solar_scene.sunray_->dni_;
	////float Ssub = 0.005;
	////float rou = solarenergy::reflected_rate;
	////int Nc = solar_scene.sunray_->num_sunshape_lights_per_group_;
	////float Srec = solar_scene.receivers[1]->pixel_length_*solar_scene.receivers[1]->pixel_length_;
	////float max = -1.0f;
	////for (int i = 0; i < solar_scene.receivers[1]->resolution_.x*solar_scene.receivers[1]->resolution_.y; ++i)
	////{
	////	h_image[i] = h_image[i] * Id * Ssub * rou / Nc / Srec;

	////	if (max < h_image[i])
	////		max = h_image[i];
	////}

	////// Save image	
	////ImageSaver::savetxt("real_2.txt", solar_scene.receivers[1]->resolution_.x, solar_scene.receivers[1]->resolution_.y, h_image);
	////delete[] h_image;
	////h_image = nullptr;
}