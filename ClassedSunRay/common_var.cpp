#include "common_var.h"


//sun ray related default value
float3 solarenergy::sun_dir = make_float3(0.306454, -0.790155, 0.530793);
float solarenergy::dni = 1000.0;
float solarenergy::csr = 0.1;
float solarenergy::num_sunshape_groups = 8;
float solarenergy::num_sunshape_lights_per_group = 1024;

//default scene file
string  solarenergy::scene_filepath = "../userData/scene/example.scn";