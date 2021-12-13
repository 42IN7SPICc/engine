#include "Utils/StringUtil.hpp"

using namespace spic;

bool StringUtil::EndsWith(const std::string& haystack, const std::string& needle)
{
    if (haystack.length() >= needle.length())
    {
        return (0 == haystack.compare(haystack.length() - needle.length(), needle.length(), needle));
    }

    return false;
}

bool StringUtil::StartsWith(const std::string& haystack, const std::string& needle)
{
    if (haystack.length() >= needle.length())
    {
        return haystack.rfind(needle, 0) == 0;
    }

    return false;
}

std::vector<std::string> StringUtil::Split(const std::string& string, const std::string& delimiter)
{
    std::vector<std::string> strings;
    std::string::size_type pos;
    std::string::size_type prev = 0;
    while ((pos = string.find(delimiter, prev)) != std::string::npos)
    {
        strings.push_back(string.substr(prev, pos - prev));
        prev = pos + 1;
    }

    strings.push_back(string.substr(prev));
    return strings;
}
