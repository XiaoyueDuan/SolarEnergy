#include "heliostat.cuh"

void RectangleHelio::Cset_sub_row_col(const float &pixel_length)
{
	float sub_helio_col_length = (size_.x - gap_.x*(row_col_.y - 1))/ row_col_.y;
	float sub_helio_row_length = (size_.z - gap_.y*(row_col_.x - 1)) / row_col_.x;
	sub_row_col_.x = sub_helio_row_length / pixel_length;
	sub_row_col_.y = sub_helio_col_length / pixel_length;
}