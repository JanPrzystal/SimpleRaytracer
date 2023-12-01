#pragma once
#include <string>
#include "Defs.h"
#include "Matrix4.h"

struct Vector4 {
	NUMBER x, y, z, w;

	void setValues(NUMBER x, NUMBER y, NUMBER z, NUMBER w);

	Vector4(NUMBER x, NUMBER y, NUMBER z, NUMBER w);

	//Vector4(Vector3 vec3, DECIMAL w) {
	//	Vector4(vec3.x, vec3.y, vec3.z, w);
	//}

	Vector4();

	NUMBER operator * (Vector4& vec);

	Vector4 operator + (NUMBER number);

	Vector4 operator / (NUMBER number);


	static Vector4* fillArrayFromMatrix(Matrix4& m, Vector4 arr[]);

	std::string toString();

	Vector4 operator * (Matrix4& matrix);

};
