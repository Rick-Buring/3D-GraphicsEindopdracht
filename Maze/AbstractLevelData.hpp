#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>

#include "GameObject.hpp"


struct levelData_s {
	char type;
	glm::vec3 position;
	glm::vec3 Linkedposition;
	char linkedWithType;
	glm::vec3 action;
};


typedef union levelData_u {
	char path[50];
	levelData_s data;
} LevelData_t;

class AbstractLevelData
{
public:
	virtual std::shared_ptr<std::vector<LevelData_t>> getData(const std::string& filePath) = 0;

};