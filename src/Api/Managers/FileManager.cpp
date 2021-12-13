#include "Managers/FileManager.hpp"
#include "Utils/StringUtil.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace spic;

std::string FileManager::Load(const std::string& file)
{
    try
    {
        std::ifstream is(file);
        std::string contents((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
        is.close();

        return contents;
    }
    catch (std::exception&)
    {
        throw std::runtime_error(std::string{"Something went wrong handling `" + file + "` (reading)."});
    }
}

void FileManager::Save(const std::string& file, const std::string& contents)
{
    try
    {
        std::ofstream os;
        os.open(file, std::ofstream::out | std::ofstream::trunc);
        os << contents;
        os.close();
    }
    catch (std::exception&)
    {
        throw std::runtime_error(std::string{"Something went wrong handling `" + file + "` (writing)."});
    }
}

std::vector<FolderFile> FileManager::GetFolderFiles(const std::string& path, const std::string& extension)
{
    std::vector<FolderFile> result;

    for (const auto& entry: std::filesystem::directory_iterator(path))
    {
        std::string file{entry.path().string()};

        if (StringUtil::EndsWith(file, extension))
        {
            auto name = file.substr(path.size() + 1, file.size() - 1);
            for (int i = 0; i < extension.size(); ++i) name.pop_back();

            result.push_back(FolderFile{name, file});
        }
    }

    return result;
}
