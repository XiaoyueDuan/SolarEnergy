#include "Gtest.cuh"
 
void test(SolarScene &solar_scene)
{
	//Heliostat *h = new RectangleHelio[4];
	// Receiver
	//solar_scene.receivers[0]->normal_ = make_float3(1.0f, 0.0f, 0.0f);
	//solar_scene.receivers[0]->CInit(100);
	//
	//float3 dir = make_float3(0.0f, 0.0f, - 1.0f);
	//float3 orig = make_float3(4.0f, 104.0f, 100.0f);

	//float t, u, v;
	//solar_scene.receivers[0]->GIntersect(orig, dir, t, u, v);
	//
	//// Heliostat
	//RectangleHelio *rectangle_helio =dynamic_cast<RectangleHelio *>(solar_scene.heliostats[1]);
	//rectangle_helio->normal_ = make_float3(0, 0, 1);
	//rectangle_helio->Cset_sub_row_col(0.01f);
	//rectangle_helio->Crotate(solar_scene.receivers[0]->pos_);

	//// Grid
	//RectGrid *rectgrid = dynamic_cast<RectGrid *>(solar_scene.grid0s[0]);
	//rectgrid->CGridHelioMatch(solar_scene.heliostats);

	// random generator
	///* cpu */
	int size = 100;
	float *h_array = new float[size];	
	int *h_array_int = new int[size];
	RandomGenerator::cpu_Uniform(h_array, size);
	RandomGenerator::cpu_Gaussian(h_array, 0.0f, 1.0f, size);	
	RandomGenerator::cpu_Uniform(h_array_int, -5, 5, size);

	/* gpu */
	float *d_array = nullptr;
	int *d_array_int = nullptr;
	checkCudaErrors(cudaMalloc((void **)&d_array, size * sizeof(float)));
	checkCudaErrors(cudaMalloc((void **)&d_array_int, size * sizeof(int)));
	RandomGenerator::gpu_Uniform(d_array, size);
	RandomGenerator::gpu_Gaussian(d_array, 0.0f, 1.0f, size);
	RandomGenerator::gpu_Uniform(d_array_int, -5, 5, size);
	float *h_array_aftercompute = nullptr;
	global_func::gpu2cpu(h_array_aftercompute, d_array, size);

	delete[] h_array;
	delete[] h_array_int;
	h_array = nullptr;
	h_array_int = nullptr;
	cudaFree(d_array);
	d_array = nullptr;

}