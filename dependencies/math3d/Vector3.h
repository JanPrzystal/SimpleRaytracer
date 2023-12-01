#pragma once
#include "Defs.h"
#include "Vector4.h"
#include "Matrix4.h"

struct Vector3 {
	NUMBER x, y, z;

	void setValues(NUMBER x, NUMBER y, NUMBER z);

	Vector3(NUMBER x, NUMBER y, NUMBER z);

	Vector3(const Vector3& vec);

	Vector3();

	NUMBER magnitude();

	Vector4 toVector4();

	Vector3 operator + (NUMBER number);

	Vector3 operator / (NUMBER number);

	Vector3 operator * (NUMBER number);

	NUMBER operator * (Vector3& vec);

	Vector3 operator * (Matrix4& matrix);

	Vector3 operator + (Vector3& vec);

	Vector3 operator - (Vector3& vec);

	Vector3 cross(Vector3& vec);

	Vector3 normalize();
};