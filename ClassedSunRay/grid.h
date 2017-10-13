#pragma once

#include "cuda_runtime.h"
#include "heliostat.h"
#include <vector>

using namespace std;

// Grid
class Grid
{
public:
	int type_;
	int helio_type_;
	__device__ __host__ Grid(){}
};


class RectGrid :public Grid
{
public:
	__device__ __host__ void CGridHelioMatch(const RectangleHelio *h_helios, const size_t &num_helios);	// set *d_grid_helio_match_, *d_grid_helio_index_ and num_grid_helio_match_
	__device__ __host__ void CGridHelioMatch(const vector<RectangleHelio> &h_helios);					// overload
	__device__ __host__ void CGridHelioMatch(const ParaboloidHelio *h_helios, const size_t &num_helios);	// set *d_grid_helio_match_, *d_grid_helio_index_ and num_grid_helio_match_
	__device__ __host__ void CGridHelioMatch(const vector<ParaboloidHelio> &h_helios);					// overload
	RectGrid():d_grid_helio_index_(nullptr), d_grid_helio_match_(nullptr) {}

	~RectGrid()
	{
		if(d_grid_helio_match_)
			d_grid_helio_match_ = nullptr;
		if (d_grid_helio_index_)
			d_grid_helio_index_ = nullptr;
	}

	__device__ __host__ void CClear()
	{
		if (d_grid_helio_match_)
		{
			cudaFree(d_grid_helio_match_);
			d_grid_helio_match_ = nullptr;
		}

		if (d_grid_helio_index_)
		{
			cudaFree(d_grid_helio_index_);
			d_grid_helio_index_ = nullptr;
		}
	}

	float3 min_vertex_;
	float3 pos_;
	float3 size_;
	float3 interval_;
	int num_helios_;
	int *d_grid_helio_match_;			// size = num_grid_helio_match_
	int *d_grid_helio_index_;			// size = size.x * size.y * size.z +1
	size_t num_grid_helio_match_;
	Heliostat **d_helios;				// *d_helios point to a Heliostat array
};