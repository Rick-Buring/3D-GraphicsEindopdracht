#include "LevelDataReaderRaw.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Button.hpp"

/**
* Splits a string into substrings, based on a seperator
*/
static std::vector<std::string> split(std::string str, const std::string& seperator)
{
	std::vector<std::string> ret;
	size_t index;
	while (true)
	{
		index = str.find(seperator);
		if (index == std::string::npos)
			break;
		ret.push_back(str.substr(0, index));
		str = str.substr(index + 1);
	}
	ret.push_back(str);
	return ret;
}

std::vector<LevelData_t> LevelDataRaw::readData(const std::string& filePath)
{
	std::ifstream pFile(filePath.c_str());


	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << filePath << std::endl;
		return std::vector<LevelData_t>();
	}

	std::vector<LevelData_t>  data = std::vector<LevelData_t>();

	//read model folder path
	std::string line;
	std::getline(pFile, line);

	LevelData_t levelData = LevelData_t();
	strncpy_s(levelData.path, line.c_str(), line.size());
	data.push_back(levelData);

	//read maze file path
	std::getline(pFile, line);

	levelData = LevelData_t();
	strncpy_s(levelData.path, line.c_str(), line.size());
	data.push_back(levelData);

	while (!pFile.eof())
	{
		std::getline(pFile, line);

		//skip empty lines
		if (line == "")
			continue;

		std::vector<std::string> coordinates = split(line, " ");

		//validate data
		if (coordinates.size() < 4)
			continue;

		auto type = coordinates[0];
		auto position = glm::vec3(std::stoi(coordinates[1]), std::stoi(coordinates[2]), std::stoi(coordinates[3]));
		glm::vec3 Linkedposition = glm::vec3(0);
		std::string linkedWithType;
		glm::vec3 action = glm::vec3(0);
		if (coordinates.size() > 4)
		{
			linkedWithType = coordinates[4];
			if (type != "level") {
 				Linkedposition = glm::vec3(std::stoi(coordinates[5]), std::stoi(coordinates[6]), std::stoi(coordinates[7]));
				if (coordinates.size() >= 11) {
					action = glm::vec3(std::stoi(coordinates[8]), std::stoi(coordinates[9]), std::stoi(coordinates[10]));
				}
			}
		}

		auto object = levelData_st();
		strncpy_s(object.type, type.c_str(), type.size() < 10 ? type.size() : 10);
		object.position = position;
		object.Linkedposition = Linkedposition;
		strncpy_s(object.linkedWithType, linkedWithType.c_str(), linkedWithType.size());
		object.action = action;
			

		levelData = LevelData_t();
		levelData.data = object;
		data.push_back(levelData);
	}

	if (data.size() < 2) {
		std::cout << "file data incomplete " << filePath << std::endl;
		return std::vector<LevelData_t>();
	}

	return data;
}
