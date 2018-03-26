#include "common_var.h"


//sun ray related default value
//float3 solarenergy::sun_dir = make_float3(0.0f, 0.0f, 1.0f);
//float3 solarenergy::sun_dir = make_float3(0.306454f, -0.790155f, 0.530793f);
//float3 solarenergy::sun_dir = make_float3(-0.9077f, -0.3538f, 0.2254f);

// real 1
//float3 solarenergy::sun_dir = make_float3(0.5774143f, -0.8072694f, -0.1221013f);

// real 2
//float3 solarenergy::sun_dir = make_float3(0.743285f, -0.6628814f, -0.090079f);

float3 solarenergy::sun_dir = make_float3(0.0f, -0.5f, 0.866025404f);

float solarenergy::dni = 1000.0f;
float solarenergy::csr = 0.1f;
float solarenergy::num_sunshape_groups = 1;
float solarenergy::num_sunshape_lights_per_group = 256;

float solarenergy::helio_pixel_length = 0.01;
float solarenergy::receiver_pixel_length = 0.01;
float solarenergy::reflected_rate = 0.88;
float solarenergy::disturb_std = 0.001;

//default scene file
string  solarenergy::scene_filepath = "../userData/scene/helioField_smallheliostat_yAdjust.scn";
//string  solarenergy::scene_filepath = "../userData/scene/example.scn";