#pragma once

#include "global_function.cuh"
#include "utils.h"

// Receivers
class Receiver
{
public:
	// sub-class needs to redefine it
	__device__ __host__ virtual bool GIntersect(const float3 &orig, const float3 &dir, float &t, float &u, float &v) = 0;
	//__device__ __host__ virtual void CInit() = 0;
	virtual void CInit(const int &geometry_info) = 0;

	// sub-class does NOT need to redefine it
	//__device__ void GAddEnergy(const float &u, const float &v, const float &energy);	// add energy to d_image
																							
	void Calloc_image();

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

private:
	//__device__ __host__ void Cset_resolution(const float3 &geometry_info);
	virtual void Cset_resolution(const int &geometry_info) = 0;
};

class RectangleReceiver :public Receiver
{
public:
	__device__ __host__ RectangleReceiver() {}
	__device__ __host__ virtual bool GIntersect(const float3 &orig, const float3 &dir, float &t, float &u, float &v)
	{
		return global_func::rayParallelogramIntersect(orig, dir, rect_vertex_[0], rect_vertex_[1], rect_vertex_[3], t, u, v);	
	}
	
	//__device__ __host__ virtual void CInit();
	virtual void CInit(const int &geometry_info);
	float3 rect_vertex_[4];

private:
	//__device__ __host__ void Cset_localnormal();
	//__device__ __host__ void Cset_localvertex();
	//__device__ __host__ void Cset_vertex();
	void Cinit_vertex();
	void Cset_localnormal();
	void Cset_localvertex();
	void Cset_vertex();
	virtual void Cset_resolution(const int &geometry_info);

	float3 localnormal_;
};

class CylinderReceiver : public Receiver
{
public:
	__device__ __host__ CylinderReceiver() {}
	__device__ __host__ virtual bool GIntersect(const float3 &orig, const float3 &dir, float &t, float &u, float &v) { return false; }//empty now
	//__device__ __host__ virtual void CInit();
	virtual void CInit(const int &geometry_info) {}//empty now

	float2 radius_hight_;				// radius_hight.x is radius, while radius_hight.y is hight
	float3 pos_;
private:
	virtual void Cset_resolution(const int &geometry_info) {}//empty now
};


class CircularTruncatedConeReceiver : public Receiver
{
public:
	__device__ __host__ CircularTruncatedConeReceiver() {}
	__device__  __host__ virtual bool GIntersect(const float3 &orig, const float3 &dir, float &t, float &u, float &v) { return false; }//empty now
	//__device__ __host__ virtual void CInit();
	virtual void CInit(const int &geometry_info) {}//empty now

	float3 topradius_bottomradius_hight_;	// topradius_bottomradius_hight_.x and while topradius_bottomradius_hight_.y is top radius and bottom radius respectively,
											// while radius_hight.z is hight
	
private:
	virtual void Cset_resolution(const int &geometry_info) {}//empty now
};