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

/// <summary>
/// abstract class to read files from diffrent types
/// </summary>
class AbstractLevelDataReader
{
public:
	/// <summary>
	/// returns vector of levelData first element is the modelPath,
	/// secend element is the maze image Path
	/// third element is a player gameObject
	/// all other elements are diffrent gameObject types
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	virtual std::vector<LevelData_t> readData(const std::string& filePath) = 0;

};

/// <summary>
/// get the correct reader based on file type
/// </summary>
/// <param name="file"></param>
/// <returns>null if no suitable Reader was found else returns the reader</returns>
AbstractLevelDataReader* AbstractLevelReader_getReader(const std::string& file);
