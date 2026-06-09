#include <utils/util.h>

std::string Util::GetFileNameFromPath(const std::string& path)
{
    size_t pos = path.find_last_of('/') + 1;
    size_t len = path.find_last_of('.') - pos;
    return path.substr(pos, len);
}

std::string Util::GetDirectoryFromPath(const std::string& path)
{
    size_t len = path.find_last_of('/') + 1;
    return path.substr(0, len);
}