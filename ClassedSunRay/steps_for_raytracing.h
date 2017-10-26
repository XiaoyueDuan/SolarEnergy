#pragma once
#include "solar_scene.h"

// float3 *d_microhelio_centers
// float3 *d_microhelio_normals
// microhelio_num
bool set_microhelio_centers(const RectangleHelio &recthelio, float3 *d_microhelio_centers, float3 *d_microhelio_normals, size_t &size);

// const float3 *d_helio_vertexs


// const int *d_microhelio_groups
