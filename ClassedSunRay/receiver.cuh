#pragma once

#include "global_function.cuh"

// Receivers
class Receiver
{
public:
	// sub-class needs to redefine it
	__device__ __host__ virtual bool GIntersect(const float3 &orig, const float3 &dir, float &t, float &u, float &v) = 0;
	//__device__ __host__ virtual void CInit() = 0;
	virtual void CInit() = 0;

	// sub-class does NOT need to redefine it
	__device__ __host__ void GAddEnergy(const float &u, const float &v, const float &energy)	// add energy to d_image
																								//__device__ __host__ void Cset_resolution(const float3 &geometry_info);
	{
		int2 row_col = make_int2(u* resolution_.y, v* resolution_.x);	// Intersect location																	  
		unsigned int address = row_col.x*resolution_.x + row_col.y;		//col_row.y + col_row.x*resolution.y;
		atomicAdd(&(d_image_[address]), energy);
	}
	void Cset_resolution(const float3 &geometry_info);

	__device__ __host__ Receiver() :d_image_(nullptr) {}

	//__device__ __host__ Receiver(Receiver &rece)
	//{
	//
	//}

	__device__ __host__ ~Receiver()
	{
		if (d_image_)
			d_image_ = nullptr;
	}

	__device__ __host__ void CClear()
	{
		if (d_image_)
		{
			cudaFree(d_image_);
			d_image_ = nullptr;
		}
	}

	int type_;
	float3 normal_;
	float3 pos_;
	float3 size_;
	int face_num_;						// the number of receiving face
	float pixel_length_;
	float *d_image_;					// on GPU, size = resolution_.x * resolution_.y
	int2 resolution_;					// resolution.x is columns, resolution.y is rows
};

class RectangleReceiver :public Receiver
{
public:
	__device__ __host__ RectangleReceiver() {}
	__device__ __host__ virtual bool GIntersect(const float3 &orig, const float3 &dir, float &t, float &u, float &v) { return false; }//empty now
																																	  //__device__ __host__ virtual void CInit();
	virtual void CInit();

	float3 rect_vertex_[4];

private:
	//__device__ __host__ void Cset_localnormal();
	//__device__ __host__ void Cset_localvertex();
	//__device__ __host__ void Cset_vertex();
	void Cset_localnormal();
	void Cset_localvertex();
	void Cset_vertex();
	float3 localnormal_;
};

class CylinderReceiver : public Receiver
{
public:
	__device__ __host__ CylinderReceiver() {}
	__device__ __host__ bool GIntersect(const float3 &orig, const float3 &dir, float &t, float &u, float &v) { return false; }//empty now
																															  //__device__ __host__ virtual void CInit();
	virtual void CInit() {}//empty now

	float2 radius_hight_;				// radius_hight.x is radius, while radius_hight.y is hight
	float3 pos_;
};


class CircularTruncatedConeReceiver : public Receiver
{
public:
	__device__ __host__ CircularTruncatedConeReceiver() {}
	__device__ __host__ bool GIntersect(const float3 &orig, const float3 &dir, float &t, float &u, float &v) { return false; }//empty now
																															  //__device__ __host__ virtual void CInit();
	virtual void CInit() {}//empty now

	float3 topradius_bottomradius_hight_;	// topradius_bottomradius_hight_.x and while topradius_bottomradius_hight_.y is top radius and bottom radius respectively,
											// while radius_hight.z is hight
	float3 pos_;
};