#include "AbstractLevelDataReader.hpp"
#include "LevelDataReaderJson.hpp"
#include "LevelDataReaderRaw.hpp"

#include "stringUtil.hpp"

typedef struct {
    AbstractLevelDataReader* reader;
    std::string suffix;
} readerByExtension;

const std::vector<readerByExtension> Readers = {
    {new LevelDataRaw(), ".txt"},
    {new LevelDataJson(), ".json"}
};

AbstractLevelDataReader* AbstractLevelReader_getReader(const std::string& file)
{
    for (auto &readerBySuffix : Readers)
    {
        if (stringEndsWith(file, readerBySuffix.suffix))
            return readerBySuffix.reader;
    }

    return nullptr;
}
