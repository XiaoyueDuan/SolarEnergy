#include <iostream>


#include "common_var.h"
#include "solar_scene.h"
#include "Gtest.cuh"

using namespace std;

int main() {
	cout <<"filepath: "<< solarenergy::scene_filepath << endl;

	// Step 1: Load files
	cout << solarenergy::disturb_std << endl;
	SolarScene *solar_scene;
	solar_scene = SolarScene::GetInstance();

	// Step 2: Initialize the content in the scene
	solar_scene->InitContent();

	// Step 3: 

	test(*solar_scene);

	// Finally, destroy solar_scene
	solar_scene->~SolarScene();
	system("pause");
	return 0;
}