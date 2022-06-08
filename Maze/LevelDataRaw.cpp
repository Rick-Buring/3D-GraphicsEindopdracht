#include "LevelDataRaw.hpp"
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

/**
* Turns a string to lowercase
*/
static inline std::string toLowerCase(std::string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}

std::shared_ptr<std::vector<LevelData_t>> LevelDataRaw::getData(const std::string& filePath)
{
	std::ifstream pFile(filePath.c_str());


	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << filePath << std::endl;
		return nullptr;
	}

	std::shared_ptr<std::vector<LevelData_t>>  data = std::make_shared<std::vector<LevelData_t>>();

	//read model folder path
	std::string line;
	std::getline(pFile, line);

	auto levelData = LevelData_t();
	strncpy_s(levelData.path, line.c_str(), line.size());
	data->push_back(levelData);

	//read maze file path
	std::getline(pFile, line);

	levelData = LevelData_t();
	strncpy_s(levelData.path, line.c_str(), line.size());
	data->push_back(levelData);

	while (!pFile.eof())
	{
		std::getline(pFile, line);

		line = toLowerCase(line);

		//skip empty lines
		if (line == "")
			continue;

		std::vector<std::string> coordinates = split(line, " ");

		//validate data
		if (line.size() < 8)
			continue;

		auto type = line[0];
		auto position = glm::vec3(std::stoi(coordinates[1]), std::stoi(coordinates[2]), std::stoi(coordinates[3]));
		auto Linkedposition = glm::vec3(std::stoi(coordinates[4]), std::stoi(coordinates[5]), std::stoi(coordinates[6]));
		auto linkedWithType = line[7];
		auto action = glm::vec3(0);

		if (line.size() >= 11)
			action = glm::vec3(std::stoi(coordinates[8]), std::stoi(coordinates[9]), std::stoi(coordinates[10]));

		auto object = levelData_s{
			type,
			position,
			Linkedposition,
			linkedWithType,
			action
		};

		levelData = LevelData_t();
		levelData.data = object;
		data->push_back(levelData);
	}

	if (data->size() < 2) {
		std::cout << "file data incomplete " << filePath << std::endl;
		return nullptr;
	}

	return data;
}
