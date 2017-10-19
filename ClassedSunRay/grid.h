#pragma once

#include "cuda_runtime.h"
#include "heliostat.cuh"
#include <vector>

using namespace std;

// Grid
class Grid
{
public:
	int type_;
	int helio_type_;
	__device__ __host__ Grid(){}
	
	void virtual CGridHelioMatch(const vector<RectangleHelio *> &h_helios) = 0;				// set *d_grid_helio_match_, *d_grid_helio_index_ and num_grid_helio_match_
};


class RectGrid :public Grid
{
public:
	void virtual CGridHelioMatch(const vector<Heliostat *> &h_helios);				// set *d_grid_helio_match_, *d_grid_helio_index_ and num_grid_helio_match_

	__device__ __host__ RectGrid():d_grid_helio_index_(nullptr), d_grid_helio_match_(nullptr){}

	__device__ __host__ ~RectGrid()
	{
		if(d_grid_helio_match_)
			d_grid_helio_match_ = nullptr;
		if (d_grid_helio_index_)
			d_grid_helio_index_ = nullptr;
	}

	void CClear();

	float3 pos_;
	float3 size_;
	float3 interval_;
	int num_helios_;					// How many heliostats in the grid
	int *d_grid_helio_match_;			// size = num_grid_helio_match_
	int *d_grid_helio_index_;			// size = size.x * size.y * size.z +1
	size_t num_grid_helio_match_;
};