#include "LevelDataRaw.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
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

std::shared_ptr<std::vector<LevelData>> LevelDataRaw::getData(const std::string& filePath)
{
	std::ifstream pFile(filePath.c_str());

	
	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << filePath << std::endl;

		return nullptr;
	}

	std::shared_ptr<std::vector<LevelData>> data = std::make_shared<std::vector<LevelData>>();

	std::string line;
	std::getline(pFile, line);
	//todo check escape characters

	LevelData levelData = LevelData();
	strncpy_s(levelData.modelFolderPath, line.c_str(), line.size());
	data->push_back(levelData);

	while (!pFile.eof())
	{
		std::getline(pFile, line);

		line = toLowerCase(line);

		//skip empty lines
		if (line == "")
			continue;

		if (line[0] == 'b') {
			std::vector<std::string> coordinates = split(line, " ");
			
			//validate data
			if (coordinates.size() == 7) {
				int px = std::stoi(coordinates[1]);
				int py = std::stoi(coordinates[2]);
				int pz = std::stoi(coordinates[3]);


				int cx = std::stoi(coordinates[4]);
				int cy = std::stoi(coordinates[5]);
				int cz = std::stoi(coordinates[6]);

				InteractiveObject object = {
					nullptr, //todo create button object
					glm::vec3(cx, cy, cz)
				};

				levelData = LevelData();
				levelData.object = object;
				data->push_back(levelData);
			}

			continue;
		}

	}

	return data;
}
