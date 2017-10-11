#pragma once

class RandomGenerator
{
public:
	// [0,1]
	static bool cpu_Uniform(float *h_0_1_array, const size_t &array_length);
	static bool gpu_Uniform(float *d_0_1_array, const size_t &array_length);

	static bool cpu_Gaussian(float *h_0_1_array, const float &mean, const float &stddev, const size_t &array_length);
	static bool gpu_Gaussian(float *d_0_1_array, const float &mean, const float &stddev, const size_t &array_length);

	// [low_threshold, high_threshold]
	static bool cpu_Uniform(int *h_min_max_array, const int &low_threshold, const int &high_threshold, const size_t &array_length);
	static bool gpu_Uniform(int *d_min_max_array, const int &low_threshold, const int &high_threshold, const size_t &array_length);
};