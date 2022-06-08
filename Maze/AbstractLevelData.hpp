#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>

#include "GameObject.hpp"


template<class T = GameObject>
struct levelData_s {
	<T>* object;
	glm::vec3 position;
};


template<class T = GameObject>
union levelData_u {
	char path[50];
	levelData_s<T> levelData;
};

class AbstractLevelData
{
public:
	virtual std::shared_ptr<std::vector<levelData_u<GameObject>>> getData(const std::string& filePath) = 0;

};