#include "receiver.cuh"

// atomicAdd can only occur in .cu file
// but __device__ function can only in the same compile unit

//__device__ void add_energy(float *d_image, 
//	const float &u, const float &v, 
//	const int2 &resolution,
//	const float &energy)
//{
//	int2 row_col = make_int2(u* resolution.y, v* resolution.x);	// Intersect location																	  
//	int address = row_col.x*resolution.x + row_col.y;				//col_row.y + col_row.x*resolution.y;																	
//	atomicAdd(&(d_image[address]), energy);
//}
//
//inline __device__ void Receiver::GAddEnergy(const float &u, const float &v, const float &energy)	// add energy to d_image																							
//{
//	int2 row_col = make_int2(u* resolution_.y, v* resolution_.x);	// Intersect location																	  
//	int address = row_col.x*resolution_.x + row_col.y;				//col_row.y + col_row.x*resolution.y;																	
//	atomicAdd(&(d_image_[address]), energy);
//}

//inline __device__ bool RectangleReceiver::GIntersect(const float3 &orig, const float3 &dir, float &t, float &u, float &v)
//{ 
//	return global_func::rayParallelogramIntersect(orig, dir, rect_vertex_[0], rect_vertex_[1], rect_vertex_[3], t, u, v);	
//}
