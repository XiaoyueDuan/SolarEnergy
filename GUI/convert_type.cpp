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

bool string_to_int(QString str, int &vec) {
	bool ok = true;
	vec = str.toInt(&ok);
	return ok;
}

bool string_to_int2(QString str, int2 &vec) {
	QStringList strs = str.split(' ', QString::SkipEmptyParts);
	if (strs.size() != 2) {
		return false;
	}
	else {
		vec.x = strs[0].toInt();
		vec.y = strs[1].toInt();
	}
	return true;
}

bool string_to_float3(QString str, float3 &vec) {
	QStringList strs = str.split(' ', QString::SkipEmptyParts);
	if (strs.size() != 3) {
		return false;
	}
	else {
		vec.x = strs[0].toFloat();
		vec.y = strs[1].toFloat();
		vec.z = strs[2].toFloat();
	}
	return true;
}

bool string_to_float2(QString str, float2 &vec) {
	QStringList strs = str.split(' ', QString::SkipEmptyParts);
	if (strs.size() != 2) {
		return false;
	}
	else {
		vec.x = strs[0].toFloat();
		vec.y = strs[1].toFloat();
	}
	return true;
}

