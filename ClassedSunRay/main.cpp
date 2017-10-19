#include <iostream>


#include "common_var.h"
#include "solar_scene.h"
#include "Gtest.cuh"

using namespace std;

int main() {
	cout <<"filepath: "<< solarenergy::scene_filepath << endl;

	SolarScene *solar_scene;
	solar_scene = SolarScene::GetInstance();

	Heliostat *h = new RectangleHelio[4];
	RectangleHelio *rh = dynamic_cast<RectangleHelio *>(h);
	rh[1].init(make_float3(0, 1, 0));
	test(*solar_scene);

	system("pause");
	return 0;
}