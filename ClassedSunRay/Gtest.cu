#include "Gtest.cuh"

__global__ void add(float u, float v)
{

}
 
void test(SolarScene &solar_scene)
{
	// test receiver.cuh
	//solar_scene.receivers[0]->normal_ = make_float3(1.0f, 0.0f, 0.0f);
	solar_scene.receivers[0]->CInit(100);
	
	float3 dir = make_float3(0.0f, 0.0f, - 1.0f);
	float3 orig = make_float3(4.0f, 104.0f, 100.0f);

	// CPU
	float t, u, v;
	solar_scene.receivers[0]->GIntersect(orig, dir, t, u, v);
	
	// 
	RectangleHelio *rectangle_helio =dynamic_cast<RectangleHelio *>(solar_scene.heliostats[0]);
	rectangle_helio->Cset_sub_row_col(0.01f);
	rectangle_helio->init(solar_scene.receivers[0]->pos_);
}