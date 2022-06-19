#pragma once

#include "glm/glm.hpp"

/// <summary>
/// calculate unit circle position along a certain angle
/// </summary>
/// <param name="angle"></param>
/// <returns>position along a the unit circle</returns>
static inline glm::vec3 glmUtils_calculatePosition(float angle) {
	return glm::vec3(glm::cos(angle), glm::sin(angle), glm::sin(angle) / 10);
}

/// <summary>
/// function multiplies all members of a vector with the float parameter
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns>a new vector with magnitude of v1 multiplied by v2</returns>
static inline glm::vec3 operator*(const glm::vec3& v1, const float& v2) {
	return glm::vec3(v1.x * v2, v1.y * v2, v1.z * v2);
}