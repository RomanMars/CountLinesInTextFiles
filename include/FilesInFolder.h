/// rename FileSystem.h?
#ifndef FILESINFOLDER_H
#define FILESINFOLDER_H

#include <vector>
#include <string>

#include <filesystem>

enum class FSType
{
    ItsFile = 'f',
    ItsFolder = 'd',
    Exist = 'e',
    NotFound = 'n'
};

typedef std::vector<std::string> stringvec;
/////

FSType FileSystemTypeEnum(std::string Path)
{
    if (std::filesystem::exists(Path))
    {

        if (std::filesystem::is_regular_file(Path))
        {
            return FSType::ItsFile;
        }

        if (std::filesystem::is_directory(Path))
        {
            return FSType::ItsFolder;
        }
    }
    return FSType::NotFound;
}

/////

/// Path is relative to root folder(exec folder, Add swithch on char Path -> rel to root Gloabal Path -> system Path)
bool PathToFilesInFolder(std::string Path, std::vector<std::string> &PathToFilesArr, bool RelativeToExeRoot = true)
{

    std::filesystem::path cwd = Path;
    if (RelativeToExeRoot == true)
    {
        cwd = std::filesystem::current_path() / Path;
        Path = (std::filesystem::current_path() / Path).string();
    }

    if (1)
    // if (std::filesystem::exists(cwd.string()) && std::filesystem::is_directory(cwd.string()))
    {
        for (const auto &entry : std::filesystem::directory_iterator(Path))
        {
            if (1)
            // if (std::filesystem::exists(cwd.string()) && std::filesystem::is_regular_file(cwd.string()))
            {
                // std::cout << entry.path() << "\n";
                PathToFilesArr.emplace_back(entry.path().string());
            }
        } // for
        return true;
    }
    else
    {
        return false;
    }
}

#ifdef _WIN32
#include <windows.h>

void read_directory(const std::string &name, stringvec &v)
{
    std::string pattern(name);
    pattern.append("\\*");
    WIN32_FIND_DATA data;
    HANDLE hFind;
    if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE)
    {
        do
        {
            v.push_back(data.cFileName);
        } while (FindNextFile(hFind, &data) != 0);
        FindClose(hFind);
    }
}
#else
#include <sys/types.h>
#include <dirent.h>

void read_directory(const std::string &name, stringvec &v)
{
    DIR *dirp = opendir(name.c_str());
    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL)
    {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
}
#endif

/////

#endif /// FILESINFOLDER_H
