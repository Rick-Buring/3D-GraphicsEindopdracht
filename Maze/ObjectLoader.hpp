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

std::vector<Model3D_t> loadObject(const std::string& filename);

