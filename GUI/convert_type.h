#pragma once

#include <QtWidgets/QTreeWidget>
#include "../ClassedSunRay/solar_scene.h"

enum DataType{
	TYPE_NONE,
	TYPE_INT,
	TYPE_INT2,
	TYPE_INT3,
	TYPE_FLOAT,
	TYPE_FLOAT2,
	TYPE_FLOAT3,
	TYPE_DOUBLE,
	TYPE_DOUBLE2,
	TYPE_DOUBLE3,
	TYPE_BOOL,
	TYPE_STREING
};





QString int2_to_string(int2 vec);
QString float3_to_string(float3 vec);
QString float2_to_string(float2 vec);