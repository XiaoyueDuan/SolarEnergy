#pragma once
#include "cuda_runtime.h"

class SunRay
{
public:
	SunRay() :d_samplelights_(nullptr), d_perturbation_(nullptr) {}
	~SunRay()
	{
		d_samplelights_ = nullptr;
		d_perturbation_ = nullptr;
	}
	__device__ __host__ void Clear()
	{
		cudaFree(d_samplelights_);
		cudaFree(d_perturbation_);
		d_samplelights_ = nullptr;
		d_perturbation_ = nullptr;
	}

	float3 sun_dir_;					// e.g. 0.306454	-0.790155	0.530793
	float dni_;							// e.g. 1000.0
	float csr_;							// e.g. 0.1
	int num_sunshape_groups_;			// e.g. 8
	int num_sunshape_lights_per_group_;	// e.g. 1024
	float3* d_samplelights_;			// e.g. point to sample lights memory on GPU
										//		memory size = num_sunshape_groups_ * num_sunshape_lights_per_group_
	float3* d_perturbation_;			// e.g. point to the memory on GPU
										//		which obeys Gaussian distribution 
										//		memory size = num_sunshape_lights_per_group_
};