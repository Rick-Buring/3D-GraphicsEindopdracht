#pragma once
#include "AbstractLevelDataReader.hpp"

class LevelDataJson : public AbstractLevelDataReader
{
	// Inherited via AbstractLevelData
	virtual std::vector<LevelData_t> readData(const std::string& filePath) override;
};