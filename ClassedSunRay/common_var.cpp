#include "common_var.h"


//sun ray related default value
float3 solarenergy::sun_dir = make_float3(0.0f, 0.0f, 1.0f);
//float3 solarenergy::sun_dir = make_float3(0.306454f, -0.790155f, 0.530793f);
float solarenergy::dni = 1000.0f;
float solarenergy::csr = 0.1f;
float solarenergy::num_sunshape_groups = 8;
float solarenergy::num_sunshape_lights_per_group = 1024;

float solarenergy::helio_pixel_length = 0.125;
float solarenergy::receiver_pixel_length = 0.02;
float solarenergy::reflected_rate = 0.88;
float solarenergy::disturb_std = 0.001;

//default scene file
string  solarenergy::scene_filepath = "../userData/scene/face2face_shadow.scn";
//string  solarenergy::scene_filepath = "../userData/scene/example.scn";