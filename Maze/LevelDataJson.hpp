#pragma once
#include "AbstractLevelData.hpp"

class LevelDataJson : public AbstractLevelData
{
	// Inherited via AbstractLevelData
	virtual std::shared_ptr<std::vector<LevelData>> getData(const std::string& filePath) override;
};