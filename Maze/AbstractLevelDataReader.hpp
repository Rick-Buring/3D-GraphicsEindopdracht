#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "GameObject.hpp"


typedef struct {
	char type[10];
	glm::vec3 position;
	glm::vec3 Linkedposition;
	char linkedWithType[50];
	glm::vec3 action;
} levelData_st;

typedef union levelData_u {
	char path[50];
	levelData_st data;
} LevelData_t;

class AbstractLevelDataReader
{
public:
	virtual std::vector<LevelData_t> readData(const std::string& filePath) = 0;

};

AbstractLevelDataReader* getReader(const std::string& file);