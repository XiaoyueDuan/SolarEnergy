#include "recthelio_tracing.h"

void recthelio_ray_tracing_init(const RectangleHelio &recthelio,			//	which heliostat will be traced
	const Grid &grid,						//	the grid heliostat belongs to
	const vector<Heliostat *> heliostats,	//	all heliostats
	const int &num_group,					//	number of sun-ray
	size_t &microhelio_num,
	float3 *&d_microhelio_centers,
	float3 *&d_microhelio_normals,
	float3 *&d_helio_vertexs)
{
	//size_t microhelio_num;
	//float3 *d_microhelio_centers = nullptr;
	//float3 *d_microhelio_normals = nullptr;

	set_microhelio_centers(recthelio, d_microhelio_centers, d_microhelio_normals, microhelio_num);
	cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

	int start_pos = grid.start_helio_pos_;
	int end_pos = start_pos + grid.num_helios_;
	//float3 *d_helio_vertexs = nullptr;
	set_helios_vertexes(heliostats, start_pos, end_pos, d_helio_vertexs);
	cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
}

void recthelio_ray_tracing(const SunRay &sunray,
	Receiver &receiver,
	const RectangleHelio &recthelio,			//	which heliostat will be traced
	Grid &grid,									//	the grid heliostat belongs to
	const vector<Heliostat *> heliostats,		//	all heliostats
	long long &tracing_time,
	long long &subcenter_time)		
{
	size_t microhelio_num;
	float3 *d_microhelio_centers = nullptr;
	float3 *d_microhelio_normals = nullptr;
	float3 *d_helio_vertexs = nullptr;

	auto start = std::chrono::high_resolution_clock::now();			 // nano-seconds
	//	Init
	recthelio_ray_tracing_init(recthelio, grid, heliostats, sunray.num_sunshape_groups_,
		microhelio_num, d_microhelio_centers, d_microhelio_normals, 
		d_helio_vertexs);
	auto elapsed = std::chrono::high_resolution_clock::now() - start;// nano-seconds
	subcenter_time+= std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

	//	ray_tracing
	start = std::chrono::high_resolution_clock::now();
	ray_tracing(sunray, grid, receiver,
		d_helio_vertexs, d_microhelio_normals, d_microhelio_centers, microhelio_num);
	elapsed = std::chrono::high_resolution_clock::now() - start;// nano-seconds
	tracing_time += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

	//	Clean all
	cudaFree(d_microhelio_centers);
	cudaFree(d_microhelio_normals);
	cudaFree(d_helio_vertexs);

	d_microhelio_centers = nullptr;
	d_microhelio_normals = nullptr;
	d_helio_vertexs = nullptr;
}