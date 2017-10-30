#include "Gtest.cuh"
#include "scene_instance_process.h"
#include "recthelio_tracing.h"
 
void test(SolarScene &solar_scene)
{
	solar_scene.InitContent();
	
	RectangleHelio *recthelio = dynamic_cast<RectangleHelio *>(solar_scene.heliostats[4]);
	recthelio_ray_tracing(*solar_scene.sunray_,
							*solar_scene.receivers[0],
							*recthelio,
							*solar_scene.grid0s[1],
							solar_scene.heliostats);

	//// float3 *d_microhelio_centers
	//// float3 *d_microhelio_normals
	//// microhelio_num
	//size_t size;
	//float3 *d_microhelio_centers = nullptr;
	//float3 *d_microhelio_normals = nullptr;
	//
	//set_microhelio_centers(*recthelio, d_microhelio_centers, d_microhelio_normals, size);
	//cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

	//// float3 *d_helio_vertexs
	//int start_pos = solar_scene.grid0s[0]->start_helio_pos_;
	//int end_pos = start_pos + solar_scene.grid0s[0]->num_helios_;
	//float3 *d_helio_vertexs = nullptr;
	//set_helios_vertexes(solar_scene.heliostats, start_pos, end_pos, d_helio_vertexs);

	//// int *d_microhelio_groups
	//int *d_microhelio_groups = nullptr;
	//set_microhelio_groups(d_microhelio_groups, solar_scene.sunray_->num_sunshape_groups_, size);

	//int *h_microhelio_groups = nullptr;
	//global_func::gpu2cpu(h_microhelio_groups, d_microhelio_groups, size);
}