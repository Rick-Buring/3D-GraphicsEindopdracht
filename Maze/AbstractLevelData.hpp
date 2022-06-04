#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>

typedef struct {
	void* object;
	glm::vec3 position;
} InteractiveObject;

typedef union {
	char modelFolderPath[50];
	InteractiveObject object;
} LevelData;

class AbstractLevelData
{
public:
	virtual std::shared_ptr<std::vector<LevelData>> getData(const std::string& filePath) = 0;

};