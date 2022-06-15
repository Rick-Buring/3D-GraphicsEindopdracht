#include "stringUtil.hpp"

bool stringEndsWith(const std::string& string, const std::string& suffix) {

    size_t suffixSize = suffix.size();
    size_t stringSize = string.size();

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
