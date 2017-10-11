#pragma once
#include "cuda_runtime.h"

// Receivers
class Receiver
{
public:
	// sub-class needs to redefine it
	__device__ __host__ bool GIntersect(const float3 &orig, const float3 &dir, float &t, float &u, float &v);

	// sub-class does NOT need to redefine it
	__device__ __host__ void GAddEnergy(const float &u, const float &v, const float &energy);	// add energy to d_image
	__device__ __host__ void Cset_resolution(const float3 &geometry_info);

	Receiver() :d_image_(nullptr) {}

	Receiver(Receiver &rece)
	{

	}

	~Receiver()
	{
		if(d_image_)
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

	float pixel_length_;
	float *d_image_;					// on GPU, size = resolution_.x * resolution_.y
	int2 resolution_;					// resolution.x is columns, resolution.y is rows
};


class RectangleReceiver :public Receiver
{
public:
	__device__ __host__ bool GIntersect(const float3 &orig, const float3 &dir, float &t, float &u, float &v);
	__device__ __host__ bool CInit(const int &type);

	float3 rect_vertex_[4];
	float3 normal_;
	float3 pos_;
	float3 size_;

private:
	__device__ __host__ bool Cset_normal(const int &type);
	__device__ __host__ bool Cset_vertex(const int &type);
};

inline bool RectangleReceiver::CInit(const int &type)
{
	Cset_normal(type);
	Cset_vertex(type);
}


class CylinderReceiver : public Receiver
{
public:
	__device__ __host__ bool GIntersect(const float3 &orig, const float3 &dir, float &t, float &u, float &v);

	float2 radius_hight_;				// radius_hight.x is radius, while radius_hight.y is hight
	float3 pos_;
};


class CircularTruncatedConeReceiver : public Receiver
{
public:
	__device__ __host__ bool GIntersect(const float3 &orig, const float3 &dir, float &t, float &u, float &v);

	float3 topradius_bottomradius_hight_;	// topradius_bottomradius_hight_.x and while topradius_bottomradius_hight_.y is top radius and bottom radius respectively,
											// while radius_hight.z is hight
	float3 pos_;
};