#pragma once

#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include "vector_arithmetic.cuh"
#include "global_constant.h"
#include "utils.h"

namespace global_func
{
	//	Transform the local coordinate to world coordinate
	__host__ __device__ inline float3 local2world(const float3 &d_local, const float3 &aligned_normal)
	{
		// u : X
		// n is normal: Y
		// v : Z	
		// Sample(world coordinate)= Sample(local) * Transform matrix
		// Transform matrix:
		// |u.x		u.y		u.z|	
		// |n.x		n.y		n.z|	
		// |v.x		v.y		v.z|	

		float3 u, n, v;// could be shared

		n = aligned_normal;
		u = cross(n, make_float3(0.0f, 1.0f, 0.0f));
		if (abs(u.x)<global_const::Epsilon&&
			abs(u.y)<global_const::Epsilon&&
			abs(u.z)<global_const::Epsilon)		//	parallel to (0,1,0), don't need to transform
			return d_local;		
		else
		{
			u /= length(u);
			v = cross(u, n); v /= length(v);
		}

		float3 d_world = make_float3(d_local.x*u.x + d_local.y*n.x + d_local.z*v.x,
			d_local.x*u.y + d_local.y*n.y + d_local.z*v.y,
			d_local.x*u.z + d_local.y*n.z + d_local.z*v.z);

		return d_world;
	}

	// Transform
	template <typename T>
	__host__ __device__ inline T transform(const T &d_in, const T transform_vector)
	{
		return d_in + transform_vector;
	}

	__host__ __device__ inline float3 rotateY(const float3 &origin, const float3 &old_dir, const float3 &new_dir)
	{		
		// Rotate matrix:
		// |cos		0		sin|	
		// |0		1		0  |	
		// |-sin	0		cos|	
		int dir = (cross(old_dir, new_dir).y > 0) ? 1:-1;// when parallel to (0,1,0), sin=0, doesn't have effect
		float cos = dot(old_dir, new_dir);
		float sin = dir*sqrtf(1 - cos*cos);
		float3 rotate_result = make_float3(cos*origin.x+sin*origin.z,
											origin.y,
											-sin*origin.x + cos*origin.z);
		return rotate_result;
	}
}