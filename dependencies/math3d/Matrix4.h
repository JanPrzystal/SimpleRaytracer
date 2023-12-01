#pragma once

#include "Defs.h"
static NUMBER PI = 3.14159f;

struct Matrix4 {
	NUMBER matrix[4][4];

	Matrix4();

	Matrix4(Matrix4 &matrix);

	Matrix4(NUMBER m00, NUMBER m11, NUMBER m22, NUMBER m33);

	static Matrix4 getCameraMatrix(NUMBER aspectRatio, NUMBER nearPlane, NUMBER farPlane, NUMBER fov);
};
