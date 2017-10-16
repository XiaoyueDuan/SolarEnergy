#include "receiver.cuh"

// Receiver
void Receiver::Calloc_image()
{
	checkCudaErrors(cudaMalloc((void **)&d_image_, sizeof(float)*resolution_.x*resolution_.y));
}



// RectangleReceiver
void RectangleReceiver::CInit(const int &geometry_info)
{
	Cinit_vertex();
	Cset_resolution(geometry_info);
	Calloc_image();
}

void RectangleReceiver::Cinit_vertex()
{
	Cset_localnormal();	// set local normal
	Cset_localvertex();	// set local vertex according to face type
	Cset_vertex();		// set world vertex according to normal
}

void RectangleReceiver::Cset_resolution(const int &geometry_info)
{
	float height = length(rect_vertex_[1] - rect_vertex_[0]);
	float width = length(rect_vertex_[1] - rect_vertex_[2]);
	resolution_.x = width*float(geometry_info);
	resolution_.y = height*float(geometry_info);
}

void RectangleReceiver::Cset_localnormal()
{
	switch (face_num_)
	{
	case 0:
		localnormal_ = make_float3(0.0f, 0.0f, 1.0f);
		break;
	case 1:
		localnormal_ = make_float3(1.0f, 0.0f, 0.0f);
		break;
	case 2:
		localnormal_ = make_float3(0.0f, 0.0f, -1.0f);
		break;
	case 3:
		localnormal_ = make_float3(-1.0f, 0.0f, 0.0f);
		break;
	default:
		break;
	}
}

void RectangleReceiver::Cset_localvertex()
{
	switch (face_num_)
	{
	case 0:
		rect_vertex_[0] = make_float3(-size_.x / 2, -size_.y / 2, size_.z / 2);
		rect_vertex_[1] = make_float3(-size_.x / 2, size_.y / 2, size_.z / 2);
		rect_vertex_[2] = make_float3(size_.x / 2, size_.y / 2, size_.z / 2);
		rect_vertex_[3] = make_float3(size_.x / 2, -size_.y / 2, size_.z / 2);
		break;
	case 1:
		rect_vertex_[0] = make_float3(size_.x / 2, -size_.y / 2, size_.z / 2);
		rect_vertex_[1] = make_float3(size_.x / 2, size_.y / 2, size_.z / 2);
		rect_vertex_[2] = make_float3(size_.x / 2, size_.y / 2, -size_.z / 2);
		rect_vertex_[3] = make_float3(size_.x / 2, -size_.y / 2, -size_.z / 2);
		break;
	case 2:
		rect_vertex_[0] = make_float3(size_.x / 2, -size_.y / 2, -size_.z / 2);
		rect_vertex_[1] = make_float3(size_.x / 2, size_.y / 2, -size_.z / 2);
		rect_vertex_[2] = make_float3(-size_.x / 2, size_.y / 2, -size_.z / 2);
		rect_vertex_[3] = make_float3(-size_.x / 2, -size_.y / 2, -size_.z / 2);
		break;
	case 3:
		rect_vertex_[0] = make_float3(-size_.x / 2, -size_.y / 2, -size_.z / 2);
		rect_vertex_[1] = make_float3(-size_.x / 2, size_.y / 2, -size_.z / 2);
		rect_vertex_[2] = make_float3(-size_.x / 2, size_.y / 2, size_.z / 2);
		rect_vertex_[3] = make_float3(-size_.x / 2, -size_.y / 2, size_.z / 2);
		break;
	default:
		break;
	}
}

void RectangleReceiver::Cset_vertex()
{
	normal_ = normalize(normal_);
	rect_vertex_[0] = global_func::rotateY(rect_vertex_[0], localnormal_, normal_);
	rect_vertex_[1] = global_func::rotateY(rect_vertex_[1], localnormal_, normal_);
	rect_vertex_[2] = global_func::rotateY(rect_vertex_[2], localnormal_, normal_);
	rect_vertex_[3] = global_func::rotateY(rect_vertex_[3], localnormal_, normal_);

	rect_vertex_[0] = global_func::transform(rect_vertex_[0], pos_);
	rect_vertex_[1] = global_func::transform(rect_vertex_[1], pos_);
	rect_vertex_[2] = global_func::transform(rect_vertex_[2], pos_);
	rect_vertex_[3] = global_func::transform(rect_vertex_[3], pos_);
}