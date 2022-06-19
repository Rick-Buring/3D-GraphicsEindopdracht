#pragma once

#include <string>
/// <summary>
/// function to check if a string ands in a suffix
/// </summary>
/// <param name="string">the string to be checked if containt suffix</param>
/// <param name="suffix">the suffix that should be checked</param>
/// <returns>returns true if sting ends with the given suffix else false</returns>
bool stringEndsWith(const std::string& string, const std::string& suffix);
