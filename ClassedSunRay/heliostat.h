#pragma once

#include "cuda_runtime.h"

// Heliostats
class Heliostat
{
public:
	float3 pos_;
	float3 size_;
	float3 normal_;

	__device__ __host__ Heliostat(){}
	__device__ __host__ bool GIntersect(const float3 &orig, const float3 &dir){}
};

class RectangleHelio :public Heliostat
{
public:
	__device__ __host__ RectangleHelio(){}
	__device__ __host__ void Cset_sub_row_col(const float &pixel_length);
	__device__ __host__ bool GIntersect(const float3 &orig, const float3 &dir);	// whether the light with orig and dir can intersect with this heliostat

	
	float3 vertex_[4];
	int2 row_col_;		// How many mirrors compose a heliostat
	int2 sub_row_col_;	// How many submirrors compose a mirror
	float2 gap_;		// The gap between mirrors

private:
	__device__ __host__ void set_localvertex();
	__device__ __host__ void set_worldvertex();
	__device__ __host__ void set_normal(const float3 focus_center);
};

class ParaboloidHelio :public Heliostat	// has-RectangleHelio
{
public:
	__device__ __host__ ParaboloidHelio(){}
	__device__ __host__ void Cset_sub_row_col(const float &pixel_length)
	{
		invisual_recthelio_.Cset_sub_row_col(pixel_length);
	}

	__device__ __host__ bool GIntersect(const float3 &orig, const float3 &dir);	// whether the light with orig and dir can intersect with this heliostat

	float2 a_b;					// y = x^2/a^2 + z^2/b^2
	RectangleHelio invisual_recthelio_;
};