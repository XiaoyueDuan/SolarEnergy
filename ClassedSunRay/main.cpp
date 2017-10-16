#include <iostream>


#include "common_var.h"
#include "solar_scene.h"
#include "Gtest.cuh"

using namespace std;

int main() {
	cout <<"filepath: "<< solarenergy::scene_filepath << endl;

	SolarScene *solar_scene;
	solar_scene = SolarScene::GetInstance();

	test(*solar_scene);

	system("pause");
	return 0;
}