#pragma once

#include <string>
#include <fstream>
#include <iostream>

class Util
{
public:
    static std::string GetFileNameFromPath(const std::string& path);
    static std::string GetDirectoryFromPath(const std::string& path);
    static std::string ReadFileContents(const std::string& path);
};