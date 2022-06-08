#pragma once

#include "glm/glm.hpp"

static inline glm::vec3 calculatePosition(float angle) {
	return glm::vec3(glm::cos(angle), glm::sin(angle), glm::sin(angle) / 10);
}

static inline glm::vec3 operator*(const glm::vec3& v1, const float& v2) {
	return glm::vec3(v1.x * v2, v1.y * v2, v1.z * v2);
}