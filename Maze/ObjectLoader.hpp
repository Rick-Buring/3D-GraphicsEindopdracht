#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "tigl.h"
#include <vector>

class Texture;

typedef struct {
	tigl::VBO* vbo;
	Texture* texture;
} Model3D_t;

typedef struct {
	std::string modelName;
	std::shared_ptr<std::vector<Model3D_t>> model;
} NamedModel3D_t;

std::shared_ptr<std::vector<Model3D_t>> loadObject(const std::string& filename);

std::vector<NamedModel3D_t> loadObjects(const std::string& fileName);

