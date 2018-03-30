#pragma once
#include "scene_instance_process.h"
#include "steps_for_raytracing.h"
#include "ray_tracing.h"

int recthelio_ray_tracing_init(const RectangleHelio &recthelio,			//	which heliostat will be traced
								const Grid &grid,							//	the grid heliostat belongs to
								const vector<Heliostat *> heliostats,		//	all heliostats
								const int &num_group,						//	number of sun-ray
								size_t &microhelio_num,
								float3 *&d_microhelio_centers,
								float3 *&d_microhelio_normals,
								float3 *&d_helio_vertexs,
								int *&d_microhelio_groups,
								long long &time_subcenter,
								long long &time_group_gen);

int recthelio_ray_tracing(const SunRay &sunray,
							Receiver &receiver,
							const RectangleHelio &recthelio,		//	which heliostat will be traced
							Grid &grid,								//	the grid heliostat belongs to
							const vector<Heliostat *> heliostats,		//	all heliostats
							long long &time_tracing,
							long long &time_subcenter,
							long long &time_group_gen);	//	all heliostats
							