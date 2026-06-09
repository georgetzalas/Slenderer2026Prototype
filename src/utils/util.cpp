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

std::string Util::ReadFileContents(const std::string& path)
{
    std::string contents = "";
    std::string line;
    std::ifstream file(path);

    if(file.good())
    {
        while(getline(file, line))
        {
            contents += line;
            contents += "\n";
        }
    }
    else
    {
        std::cerr << "[UTIL ERROR] Couldnt find file " << path << std::endl;
    }

    file.close();

    return contents;
}
