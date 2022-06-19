#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "tigl.h"
#include <vector>
#include "Texture.hpp"

typedef struct {
	std::vector<tigl::Vertex> container;
	tigl::VBO* vbo;
	std::string texturePath;
	Texture* texture;
} Model3D_t;

typedef struct {
	std::string modelName;
	std::shared_ptr<std::vector<Model3D_t>> model;
} NamedModel3D_t;

/// <summary>
/// loads a single object file
/// </summary>
/// <param name="filename">path to the object file</param>
/// <returns>a shared pointer to the created object</returns>
std::shared_ptr<std::vector<Model3D_t>> ObjectLoader_loadObject(const std::string& filename);

/// <summary>
/// loads all object files recursively in a directory
/// </summary>
/// <param name="fileName">directory path where all the object files are located</param>
/// <returns>vector of all created objects sorted by name</returns>
std::vector<NamedModel3D_t> ObjectLoader_loadObjects(const std::string& fileName);

