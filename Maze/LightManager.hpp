#pragma once

#include <glm/glm.hpp>

typedef struct lightStruct {
	int lightId;
	bool isDirectional;
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffusion;
	glm::vec3 specular;
	void setLight();
} lightInfo;

void addLight(lightInfo* out);
void removeLight(lightInfo* lightID);
