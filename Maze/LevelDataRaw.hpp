#pragma once

#include "AbstractLevelData.hpp"

class LevelDataRaw : public AbstractLevelData
{
	// Inherited via AbstractLevelData
	std::shared_ptr<std::vector<levelData_u<GameObject>>> getData(const std::string& filePath) override;
};