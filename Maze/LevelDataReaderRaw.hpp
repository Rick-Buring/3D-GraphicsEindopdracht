#pragma once

#include "AbstractLevelDataReader.hpp"

class LevelDataRaw : public AbstractLevelDataReader
{
	// Inherited via AbstractLevelData
	std::vector<LevelData_t>  readData(const std::string& filePath) override;
};