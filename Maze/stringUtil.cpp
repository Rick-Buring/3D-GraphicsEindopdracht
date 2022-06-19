#include "stringUtil.hpp"

/// <summary>
/// function to check if a string ands in a suffix
/// </summary>
/// <param name="string">the string to be checked if containt suffix</param>
/// <param name="suffix">the suffix that should be checked</param>
/// <returns>returns true if sting ends with the given suffix else false</returns>
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
