#pragma once

#include <vector>
#include "ObjectLoader.hpp"

std::shared_ptr<std::vector<Model3D_t>> buildCube(const glm::vec3& p, const glm::vec3& s, const glm::vec4& color);

std::shared_ptr<std::vector<Model3D_t>> createPlane(float width, float height);
