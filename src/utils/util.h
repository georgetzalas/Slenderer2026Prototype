#pragma once

#include <string>

class Util
{
public:
    static std::string GetFileNameFromPath(const std::string& path);
    static std::string GetDirectoryFromPath(const std::string& path);
};