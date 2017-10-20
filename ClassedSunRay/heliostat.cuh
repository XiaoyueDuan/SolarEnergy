#pragma once

#include "utils.h"
#include "global_function.cuh"

// Heliostats
class Heliostat
{
public:
	float3 pos_;
	float3 size_;
	float3 normal_;
	int2 row_col_;		// How many mirrors compose a heliostat
	float2 gap_;		// The gap between mirrors

	__device__ __host__ Heliostat() {}

	virtual void Crotate(const float3 focus_center) = 0;
};

class RectangleHelio :public Heliostat
{
public:
	__device__ __host__ RectangleHelio() {}
	void Cset_sub_row_col(const float &pixel_length);
	//__device__ __host__ virtual bool GIntersect(const float3 &orig, const float3 &dir)	// whether the light with orig and dir can intersect with this heliostat
	//{
	//	float t, u, v;
	//	return global_func::rayParallelogramIntersect(orig, dir, vertex_[0], vertex_[1], vertex_[3], t, u, v);
	//}
	virtual void Crotate(const float3 focus_center);

	float3 vertex_[4];
	int2 sub_row_col_;	// How many submirrors compose a mirror

private:
	void Cset_localvertex();
	void Cset_worldvertex();
	void Cset_normal(const float3 focus_center);
};
 
class ParaboloidHelio :public Heliostat	// has-RectangleHelio
{
public:
	__device__ __host__ ParaboloidHelio() {}
	__device__ __host__ void Cset_sub_row_col(const float &pixel_length)
	{
		invisual_recthelio_.Cset_sub_row_col(pixel_length);
	}

	//__device__ __host__ virtual bool GIntersect(const float3 &orig, const float3 &dir)	// whether the light with orig and dir can intersect with this heliostat
	//{
	//	return invisual_recthelio_.GIntersect(orig, dir);
	//}

	virtual void Crotate(const float3 focus_center) {}	// empty now

	float2 a_b;					// y = x^2/a^2 + z^2/b^2

private:
	RectangleHelio invisual_recthelio_;
};