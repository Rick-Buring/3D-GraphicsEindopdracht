#include "AbstractLevelDataReader.hpp"
#include "LevelDataReaderJson.hpp"
#include "LevelDataReaderRaw.hpp"

typedef struct {
    AbstractLevelDataReader* reader;
    std::string suffix;
} readerByExtension;

const std::vector<readerByExtension> Readers = {
    {new LevelDataRaw(), ".txt"},
    {new LevelDataJson(), ".json"}
};

static bool stringEndsWith(const std::string& string, const std::string& suffix) {

    int suffixSize = suffix.size();
    int stringSize = string.size();

    if (stringSize <= suffixSize) {
        return false;
    }
    for (size_t i = 0; i < suffixSize; i++)
    {
        if (string[(stringSize - suffixSize) + i] != suffix[i]) {
            return false;
        }
    }
    return true;
}

AbstractLevelDataReader* getReader(const std::string& file)
{
    for (auto readerBySuffix : Readers)
    {
        if (stringEndsWith(file, readerBySuffix.suffix))
            return readerBySuffix.reader;
    }

    return nullptr;
}
