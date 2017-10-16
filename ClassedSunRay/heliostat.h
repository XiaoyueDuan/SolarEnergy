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

	__device__ __host__ Heliostat(){}

	__device__ __host__ bool virtual GIntersect(const float3 &orig, const float3 &dir) = 0;
	__device__ __host__ virtual void init(const float3 focus_center) = 0;
};

class RectangleHelio :public Heliostat
{
public:
	__device__ __host__ RectangleHelio(){}
	void Cset_sub_row_col(const float &pixel_length);
	__device__ __host__ bool virtual GIntersect(const float3 &orig, const float3 &dir)	// whether the light with orig and dir can intersect with this heliostat
	{
		float t, u, v;
		return global_func::rayParallelogramIntersect(orig, dir, vertex_[0], vertex_[1], vertex_[3], t, u, v);
	}
	__device__ __host__ virtual void init(const float3 focus_center)
	{		
		set_normal(focus_center);
		set_localvertex();
		set_worldvertex();
	}
	
	float3 vertex_[4];
	int2 sub_row_col_;	// How many submirrors compose a mirror

private:
	__device__ __host__ void set_localvertex()
	{
		vertex_[0] = make_float3(-size_.x / 2, size_.y / 2, -size_.z / 2);
		vertex_[1] = make_float3(vertex_[0].x, vertex_[0].y, vertex_[0].z + size_.z);
		vertex_[2] = make_float3(vertex_[1].x + size_.x, vertex_[1].y, vertex_[1].z);
		vertex_[3] = make_float3(vertex_[0].x + size_.x, vertex_[0].y, vertex_[0].z);
	}

	__device__ __host__ void set_worldvertex()
	{
		vertex_[0] = global_func::local2world(vertex_[0], normal_);
		vertex_[1] = global_func::local2world(vertex_[1], normal_);
		vertex_[2] = global_func::local2world(vertex_[2], normal_);
		vertex_[3] = global_func::local2world(vertex_[3], normal_);

		vertex_[0] = global_func::transform(vertex_[0], pos_);
		vertex_[1] = global_func::transform(vertex_[1], pos_);
		vertex_[2] = global_func::transform(vertex_[2], pos_);
		vertex_[3] = global_func::transform(vertex_[3], pos_);
	}

	__device__ __host__ void set_normal(const float3 focus_center)
	{
		float3 local_center = make_float3(pos_.x, pos_.y+size_.y/2, pos_.z);
		float3 dir = focus_center - local_center;
		normal_ = normalize(dir);
	}
};

class ParaboloidHelio :public Heliostat	// has-RectangleHelio
{
public:
	__device__ __host__ ParaboloidHelio(){}
	__device__ __host__ void Cset_sub_row_col(const float &pixel_length)
	{
		invisual_recthelio_.Cset_sub_row_col(pixel_length);
	}

	__device__ __host__ bool virtual GIntersect(const float3 &orig, const float3 &dir)	// whether the light with orig and dir can intersect with this heliostat
	{
		// empty now
		return false;
	}						

	__device__ __host__ virtual void init(const float3 focus_center){}	// empty now

	float2 a_b;					// y = x^2/a^2 + z^2/b^2
	RectangleHelio invisual_recthelio_;
};