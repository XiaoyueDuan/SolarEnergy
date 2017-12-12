#include "common_var.h"


//sun ray related default value
//float3 solarenergy::sun_dir = make_float3(0.0f, 0.0f, 1.0f);
//float3 solarenergy::sun_dir = make_float3(0.306454f, -0.790155f, 0.530793f);
//float3 solarenergy::sun_dir = make_float3(-0.9077f, -0.3538f, 0.2254f);

// real 1
//float3 solarenergy::sun_dir = make_float3(0.5774143f, -0.8072694f, -0.1221013f);

// real 2
//float3 solarenergy::sun_dir = make_float3(0.743285f, -0.6628814f, -0.090079f);

float3 solarenergy::sun_dir = make_float3(0.0f, -0.08715574f, 0.996194698f);
float solarenergy::csr = 0.1f;
float solarenergy::receiver_pixel_length = 0.04f;
float solarenergy::disturb_std = 0.001;
string  solarenergy::scene_filepath = "../userData/scene/check_the_paper_small.scn";

float solarenergy::dni = 981.0f;
//float solarenergy::csr = 0.2f;
float solarenergy::num_sunshape_groups = 8;
float solarenergy::num_sunshape_lights_per_group = 1024;

float solarenergy::helio_pixel_length = 0.01;
//float solarenergy::receiver_pixel_length = 0.01;
float solarenergy::reflected_rate = 0.88;
//float solarenergy::disturb_std = 0.002;

//default scene file
//string  solarenergy::scene_filepath = "../userData/check_with_real_data/sandun.scn";
//string  solarenergy::scene_filepath = "../userData/scene/example.scn";