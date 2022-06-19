//#define CONFIG_CATCH_MAIN
#ifdef TEST

#include "catch.hpp"
#include "stringUtil.hpp"

TEST_CASE("First Test") {
    REQUIRE(6 * 7 == 42);
}

TEST_CASE("String suffix is larger than string returns false") {
    std::string testString = "test", suffix = "TestingSuffixSize";
    bool result = stringEndsWith(testString, suffix);
    REQUIRE(result == false);
}

TEST_CASE("String suffix is within string but not last in string returns false") {
    std::string testString = "suffixtest", suffix = "suffix";
    bool result = stringEndsWith(testString, suffix);
    REQUIRE(result == false);
}

TEST_CASE("String suffix is within string and last in string returns true") {
    std::string testString = "testsuffix", suffix = "suffix";
    bool result = stringEndsWith(testString, suffix);
    REQUIRE(result == true);
}

#endif // TEST
