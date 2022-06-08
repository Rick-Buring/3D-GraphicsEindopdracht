#pragma once

#include "AbstractLevelData.hpp"

class LevelDataRaw : public AbstractLevelData
{
	// Inherited via AbstractLevelData
	std::shared_ptr<std::vector<LevelData_t>>  getData(const std::string& filePath) override;
};