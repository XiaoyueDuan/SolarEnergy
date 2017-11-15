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

bool string_to_int(QString str, int &vec);
bool string_to_int2(QString str,int2 &vec);
bool string_to_float3(QString str,float3 &vec);
bool string_to_float2(QString str,float2 &vec);