#include "grid.h"

void RectGrid::CClear()
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

int boxIntersect(int &mirrowId, float3 &min_pos, float3 &max_pos, RectGrid &grid,
	vector<vector<int>> &grid_mirrow_match_vector)
{
	int size = 0;
	int3 min_grid_pos = make_int3((min_pos - grid.pos_).x / grid.interval_.x,
		(min_pos - grid.pos_).y / grid.interval_.y,
		(min_pos - grid.pos_).z / grid.interval_.z);
	int3 max_grid_pos = make_int3((max_pos - grid.pos_).x / grid.interval_.x,
		(max_pos - grid.pos_).y / grid.interval_.y,
		(max_pos - grid.pos_).z / grid.interval_.z);

	for (int x = min_grid_pos.x; x <= max_grid_pos.x; ++x)
		for (int y = min_grid_pos.y; y <= max_grid_pos.y; ++y)
			for (int z = min_grid_pos.z; z <= max_grid_pos.z; ++z)
			{
				int pos = x * grid.size_.y * grid.size_.z + y * grid.size_.z + z;
				grid_mirrow_match_vector[pos].push_back(mirrowId);
				++size;
			}
	return size;
}

void RectGrid::CGridHelioMatch(const Heliostat *h_helios, const size_t &num_helios) // set *d_grid_helio_match_, *d_grid_helio_index_ and num_grid_helio_match_
{
	float3 minPos, maxPos;
	float length;
	num_grid_helio_match_ = 0;
	vector<vector<int>> grid_mirrow_match_vector(size_.x * size_.y * size_.z);
	for (int i = 0; i < num_helios; ++i)
	{
		length = h_helios[i].size_.x * h_helios[i].size_.x +
				h_helios[i].size_.y * h_helios[i].size_.y +
				h_helios[i].size_.z * h_helios[i].size_.z;

		length = sqrt(length) / 2;
		minPos = h_helios[i].pos_ - length;
		maxPos = h_helios[i].pos_ + length;

		num_grid_helio_match_ += boxIntersect(i, minPos, maxPos, *this, grid_mirrow_match_vector);
	}

	int *h_grid_helio_index = new int[size_.x * size_.y * size_.z + 1];
	h_grid_helio_index[0] = 0;
	int *h_grid_helio_match = new int[num_grid_helio_match_];

	int index = 0;
	for (int i = 0; i < size_.x * size_.y * size_.z; ++i)
	{
		h_grid_helio_index[i + 1] = h_grid_helio_index[i] + grid_mirrow_match_vector[i].size();
		for (int j = 0; j < grid_mirrow_match_vector[i].size(); ++j, ++index)
			h_grid_helio_match[index] = grid_mirrow_match_vector[i][j];
	}

	global_func::cpu2gpu(d_grid_helio_match_, h_grid_helio_match, num_grid_helio_match_);
	global_func::cpu2gpu(d_grid_helio_index_, h_grid_helio_index, size_.x * size_.y * size_.z + 1);

	delete[] h_grid_helio_index;
	delete[] h_grid_helio_match;
	h_grid_helio_index = nullptr;
	h_grid_helio_match = nullptr;
}