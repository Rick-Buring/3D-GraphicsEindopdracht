#pragma once
#include "AbstractLevelDataReader.hpp"

class LevelDataJson : public AbstractLevelDataReader
{
	// Inherited via AbstractLevelData

	/// <summary>
	/// no implementation
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	virtual std::vector<LevelData_t> readData(const std::string& filePath) override;
};