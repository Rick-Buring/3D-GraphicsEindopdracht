#pragma once

#include <vector>
#include "ObjectLoader.hpp"

/// <summary>
/// creates a cube Model
/// </summary>
/// <param name="p">local offset</param>
/// <param name="s">size of the cube</param>
/// <param name="color">color of the cube</param>
/// <returns></returns>
std::shared_ptr<std::vector<Model3D_t>> utills_buildCube(const glm::vec3& p, const glm::vec3& s, const glm::vec4& color);

/// <summary>
/// creates a cube Sphere
/// </summary>
/// <param name="p">local offset</param>
/// <param name="s">size of the cube</param>
/// <param name="color">color of the cube</param>
/// <returns></returns>
std::shared_ptr<std::vector<Model3D_t>> utills_buildSphere(const glm::vec3& p, const glm::vec3& s, const glm::vec4& color);

/// <summary>
/// creates a cube plane
/// </summary>
/// <param name="width">width of the plane</param>
/// <param name="height">height of the plane</param>
/// <returns></returns>
std::shared_ptr<std::vector<Model3D_t>> utills_createPlane(float width, float height);
