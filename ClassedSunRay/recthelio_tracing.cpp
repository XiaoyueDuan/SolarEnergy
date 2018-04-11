#include "recthelio_tracing.h"
#include <chrono>

int recthelio_ray_tracing_init(const RectangleHelio &recthelio,			//	which heliostat will be traced
	const Grid &grid,						//	the grid heliostat belongs to
	const vector<Heliostat *> heliostats,	//	all heliostats
	const int &num_group,					//	number of sun-ray
	size_t &microhelio_num,
	float3 *&d_microhelio_centers,
	float3 *&d_microhelio_normals,
	float3 *&d_helio_vertexs,
	int *&d_microhelio_groups,
	long long &time_subcenter,
	long long &time_group_gen)
{
	int num_subcenters = 0;
	auto start = std::chrono::high_resolution_clock::now();			 // nano-seconds
	switch (recthelio.type)
	{
		case(SubCenterType::Grid):
		{	
			set_microhelio_centers(recthelio, d_microhelio_centers, d_microhelio_normals, microhelio_num);
			num_subcenters = microhelio_num;
			break;
		}			
		case(SubCenterType::Poisson):
		{
			num_subcenters = set_possion_microhelio_centers(recthelio, d_microhelio_centers, d_microhelio_normals, microhelio_num);
			break;
		}
		default:
			break;
	}
	cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
	auto elapsed = std::chrono::high_resolution_clock::now() - start;// nano-seconds
	time_subcenter+= std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

	int start_pos = grid.start_helio_pos_;
	int end_pos = start_pos + grid.num_helios_;
	//float3 *d_helio_vertexs = nullptr;
	set_helios_vertexes(heliostats, start_pos, end_pos, d_helio_vertexs);
	cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

	//int *d_microhelio_groups = nullptr;
	start = std::chrono::high_resolution_clock::now();			 // nano-seconds
	set_microhelio_groups(d_microhelio_groups, num_group, microhelio_num);
	elapsed = std::chrono::high_resolution_clock::now() - start;// nano-seconds
	time_group_gen += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

	return num_subcenters;
}

int recthelio_ray_tracing(const SunRay &sunray,
	Receiver &receiver,
	const RectangleHelio &recthelio,			//	which heliostat will be traced
	Grid &grid,									//	the grid heliostat belongs to
	const vector<Heliostat *> heliostats,		//	all heliostats
	long long &time_tracing,
	long long &time_subcenter, 
	long long &time_group_gen)
{
	size_t microhelio_num;
	float3 *d_microhelio_centers = nullptr;
	float3 *d_microhelio_normals = nullptr;
	float3 *d_helio_vertexs = nullptr;
	int *d_microhelio_groups = nullptr;
	
	//	Init
	int num_subcenters=recthelio_ray_tracing_init(recthelio, grid, heliostats, 
		sunray.num_sunshape_groups_*sunray.num_sunshape_lights_per_group_,
		microhelio_num, d_microhelio_centers, d_microhelio_normals, 
		d_helio_vertexs, d_microhelio_groups,
		time_subcenter, time_group_gen);

	//	ray_tracing
	auto start = std::chrono::high_resolution_clock::now();			 // nano-seconds
	ray_tracing(sunray, grid, receiver,
		d_helio_vertexs, d_microhelio_normals, d_microhelio_centers, d_microhelio_groups, microhelio_num);
	auto elapsed = std::chrono::high_resolution_clock::now() - start;// nano-seconds
	time_tracing+= std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count(); // microseconds

	//	Clean all
	cudaFree(d_microhelio_centers);
	cudaFree(d_microhelio_normals);
	cudaFree(d_helio_vertexs);
	cudaFree(d_microhelio_groups);

	d_microhelio_centers = nullptr;
	d_microhelio_normals = nullptr;
	d_helio_vertexs = nullptr;
	d_microhelio_groups = nullptr;

	return num_subcenters;
}