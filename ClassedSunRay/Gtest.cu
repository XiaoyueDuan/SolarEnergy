#include "Gtest.cuh"
 
void test(SolarScene &solar_scene)
{
	//Heliostat *h = new RectangleHelio[4];
	// Receiver
	//solar_scene.receivers[0]->normal_ = make_float3(1.0f, 0.0f, 0.0f);
	solar_scene.receivers[0]->CInit(100);
	
	float3 dir = make_float3(0.0f, 0.0f, - 1.0f);
	float3 orig = make_float3(4.0f, 104.0f, 100.0f);

	float t, u, v;
	solar_scene.receivers[0]->GIntersect(orig, dir, t, u, v);
	
	// Heliostat
	RectangleHelio *rectangle_helio =dynamic_cast<RectangleHelio *>(solar_scene.heliostats[1]);
	rectangle_helio->normal_ = make_float3(0, 0, 1);
	rectangle_helio->Cset_sub_row_col(0.01f);
	rectangle_helio->Cinit(solar_scene.receivers[0]->pos_);

	// Grid
	RectGrid *rectgrid = dynamic_cast<RectGrid *>(solar_scene.grid0s[0]);
	rectgrid->CGridHelioMatch(solar_scene.heliostats);
}