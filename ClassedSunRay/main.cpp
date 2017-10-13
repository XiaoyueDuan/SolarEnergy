#include <iostream>


#include "common_var.h"
#include "solar_scene.h"

using namespace std;

int main() {
	cout <<"filepath: "<< solarenergy::scene_filepath << endl;

	SolarScene *solar_scene;
	solar_scene = SolarScene::GetInstance();
		
	solar_scene->receivers[0]->CInit();

	system("pause");
	return 0;
}