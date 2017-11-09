#include "convert_type.h"

QString float3_to_string(float3 vec) {
	QString str;
	str += QString::number(vec.x);
	str += " ";
	str += QString::number(vec.y);
	str += " ";
	str += QString::number(vec.z);
	return str;
}

QString int2_to_string(int2 vec) {
	QString str;
	str += QString::number(vec.x);
	str += " ";
	str += QString::number(vec.y);
	return str;
}


QString float2_to_string(float2 vec) {
	QString str;
	str += QString::number(vec.x);
	str += " ";
	str += QString::number(vec.y);
	return str;
}

bool string_to_int2() {

	return true;
}

bool string_to_float2() {
	return true;
}

bool string_to_float3() {
	return true;
}