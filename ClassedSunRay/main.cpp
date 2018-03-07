#include <iostream>
#include "common_var.h"
#include "solar_scene.h"
#include "Gtest.cuh"

curandGenerator_t *RandomGenerator::gen;

using namespace std;

int main() {
	cout <<"filepath: "<< solarenergy::scene_filepath << endl;

	// Step 0: Initialize gen seed in RandomGenerator
	curandGenerator_t gen_test;
	curandCreateGenerator(&gen_test, CURAND_RNG_PSEUDO_DEFAULT);
	curandSetPseudoRandomGeneratorSeed(gen_test, time(NULL));
	RandomGenerator::gen = &gen_test;

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
	// destroy gen
	RandomGenerator::gen = nullptr;
	curandDestroyGenerator(gen_test);

	system("pause");

	return 0;
}