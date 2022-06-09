#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "GameObject.hpp"


struct levelData_s {
	char type[10];
	glm::vec3 position;
	glm::vec3 Linkedposition;
	char linkedWithType[10];
	glm::vec3 action;
};

typedef union levelData_u {
	char path[50];
	levelData_s data;
} LevelData_t;

class AbstractLevelDataReader
{
public:
	virtual std::vector<LevelData_t> readData(const std::string& filePath) = 0;

};

AbstractLevelDataReader* getReader(const std::string& file);