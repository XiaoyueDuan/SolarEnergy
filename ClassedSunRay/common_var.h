#pragma once
#include <cuda_runtime.h>

namespace solarenergy {
	//sun ray related default value
	float3 sun_dir = make_float3(0.306454, -0.790155, 0.530793);
	float dni = 1000.0;
	float csr = 0.1;
	float num_sunshape_groups = 8;
	float num_sunshape_lights_per_group = 1024;

	//



}