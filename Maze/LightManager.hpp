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

/// <summary>
/// adds a light to the tigl->shader
/// </summary>
/// <param name="out">pointer in whicht the id is recalculated</param>
void addLight(lightInfo* out);

/// <summary>
/// removes light from the tigl->shader.
/// updates all otherlights accordingly
/// </summary>
/// <param name="lightID"></param>
void removeLight(lightInfo* lightID);
