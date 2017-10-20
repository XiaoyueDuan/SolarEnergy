#include "heliostat.cuh"

void RectangleHelio::Cset_sub_row_col(const float &pixel_length)
{
	float sub_helio_col_length = (size_.x - gap_.x*(row_col_.y - 1))/ row_col_.y;
	float sub_helio_row_length = (size_.z - gap_.y*(row_col_.x - 1)) / row_col_.x;
	sub_row_col_.x = sub_helio_row_length / pixel_length;
	sub_row_col_.y = sub_helio_col_length / pixel_length;
}

void RectangleHelio::Crotate(const float3 focus_center)
{
	Cset_normal(focus_center);
	Cset_localvertex();
	Cset_worldvertex();
}

void RectangleHelio::Cset_localvertex()
{
	vertex_[0] = make_float3(-size_.x / 2, size_.y / 2, -size_.z / 2);
	vertex_[1] = make_float3(vertex_[0].x, vertex_[0].y, vertex_[0].z + size_.z);
	vertex_[2] = make_float3(vertex_[1].x + size_.x, vertex_[1].y, vertex_[1].z);
	vertex_[3] = make_float3(vertex_[0].x + size_.x, vertex_[0].y, vertex_[0].z);
}

void RectangleHelio::Cset_worldvertex()
{
	vertex_[0] = global_func::local2world(vertex_[0], normal_);
	vertex_[1] = global_func::local2world(vertex_[1], normal_);
	vertex_[2] = global_func::local2world(vertex_[2], normal_);
	vertex_[3] = global_func::local2world(vertex_[3], normal_);

	vertex_[0] = global_func::transform(vertex_[0], pos_);
	vertex_[1] = global_func::transform(vertex_[1], pos_);
	vertex_[2] = global_func::transform(vertex_[2], pos_);
	vertex_[3] = global_func::transform(vertex_[3], pos_);
}

void RectangleHelio::Cset_normal(const float3 focus_center)
{
	float3 local_center = make_float3(pos_.x, pos_.y + size_.y / 2, pos_.z);
	float3 dir = focus_center - local_center;
	normal_ = normalize(dir);
}