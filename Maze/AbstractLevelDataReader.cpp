#include "AbstractLevelDataReader.hpp"
#include "LevelDataReaderJson.hpp"
#include "LevelDataReaderRaw.hpp"

AbstractLevelDataReader* getReader(const std::string& file)
{
    //todo implement logic
    return new LevelDataRaw();
}
