/// All naming, code, words and all functions - writed for this programm, worked only for this programm
/// name example: CoreFileSystem LineCounter LineCounterCore

///
#ifndef LINECOUNTER_H
#define LINECOUNTER_H

#include <iostream> // std::cin, std::cout
#include <fstream>  // std::ofstream

#include <string>

#include <cstdint>

#include <vector>

#include <filesystem> //filesize

#include <algorithm> // std::sort

#include <FilesInFolder.h>

#include <TextFileProcessor.h>

#include <mio/mmap.hpp>

#include <omp.h>

#define D_Value_Threshold 1024 // 1024*1000 -> check file small or large

/// to use fixed chunk size-> replace line generatetasks func : Tasks.emplace_back(f, Lc , Type, mmaplowerbound, (BaseChunkSize*1024);
#define D_BaseChunkSize 1024 // 1024*1000 -> define base chunksize(can vary or same)

/// used now?
enum class Types
{
  File = 'f',
  Chunk = 'c',
  LargeFile = 'l',
  SmallFile = 's'
};

/////
struct File
{
  std::string Path;
  uint64_t size;
  char type = 's'; // Types::LargeFile; /// l->large, s -> small
  File(std::string Path = "1.txt", uint64_t size = 0, char type = 'l')
  {
    this->Path = Path;
    this->size = size;
    this->type = type;
  }
  /// for sorting:
  // bool operator < (const File& rhs) const {
  bool operator()(const File &f1, const File &f2)
  {
    return f1.size < f2.size;
  } // std::sort

  bool operator<(const File &rhs)
  {
    // std::cout << "size: " << size << "rhs.size: " << rhs.size << "b sort " << size << rhs.size << std::endl;
    return size < rhs.size;
  } // std::sort
};

struct Task
{
  File file;
  uint64_t lc = 0; // line count
  char type = 'f'; /// can create enum f->file, c -> chunk
  uint64_t lowerbound = 0;
  uint64_t chunksize = 0; // upperbound
  Task(File file, uint64_t lc = 0, char type = 'f', uint64_t lowerbound = 0, uint64_t chunksize = 0)
  {
    this->file = file;
    this->lc = lc;
    this->type = type;
    if (this->type == 'c')
    { // Types::Chunk) {
      this->lowerbound = lowerbound;
      /// if i -> last index in loop, chunksize = mipmapwholefile
      this->chunksize = chunksize;
    }
  }
  // Task (File cfile)
};

class LineCounter
{ // (std::string Path) {

public:
  std::vector<File> Files;
  std::vector<Task> Tasks;

  std::vector<std::string> PathToFilesArr;

  // uint64_t Value_Threshold = 1024*1000; ///example value
  uint64_t Value_Threshold = D_Value_Threshold * 1000; /// example value

  /// -> can be just equal to value treshold OR other size
  /// can create all chunks, except last wih same size, or with nearly equal size
  // uint64_t BaseChunkSize = 1024*1000;//128;//1024;
  uint64_t BaseChunkSize = D_BaseChunkSize * 1000; // 128;//1024;

  /// global glc = glc + lc
  uint64_t GlobalLineCounter = 0;

  /// constructor
  LineCounter(std::string FolderPathToProcess, bool RelativeToExePath = true);

  // Parse?
  bool ProcessFolder(std::string Path, bool RelativeToExePath = true); // {

  /// used file operator
  // bool FilesSortfunction (const File &File1, const File &File2);// {
  // bool FilesSortfunction1 (std::vector<File>::iterator it1, std::vector<File>::iterator it2);
  //

  bool SortFiles();

  bool ProcessFiles();
  bool GenerateTasks();
  uint64_t ProcessTasks();

  /////// can add
  /////
  bool ProcessFile(); // 1 file
  /// add func for tests and etc from notes

}; // class LineCounter

/////

// std::vector<std::string> PathToFilesArr;
LineCounter::LineCounter(std::string FolderPathToProcess, bool RelativeToExePath)
{

  /// base class work explanation:

  /// read folder
  /// get text files
  /// sort files by size
  /// generate tasks
  /// process tasks(OpenMP)

  // bool ProcessFolder(FolderPathToProcess, RelativeToExePath);// {
  // bool ProcessFiles();
  // bool SortFiles();
  // bool GenerateTasks();
  // uint64_t ProcessTasks();
  ProcessFolder(FolderPathToProcess, RelativeToExePath); // {

  ProcessFiles();

  SortFiles();

  std::cout << "GenerateTasks();" << GenerateTasks() << std::endl;
  // GenerateTasks();
  uint64_t GlobalLineCounter = ProcessTasks();

  std::cout << "GlobalLineCounter: " << GlobalLineCounter << std::endl;
}

bool LineCounter::ProcessFolder(std::string Path, bool RelativeToExePath)
{ // = true ) {

  if (PathToFilesInFolder(Path, PathToFilesArr, RelativeToExePath))
  {
    return true;
  }
  else
  {
    /// not directory
    return false;
  }
}

bool LineCounter::ProcessFiles()
{

  /// PathToFilesArr arr with files paths

  // std::vector<File> Files;
  ///? if -> win32 std filesystem, if other boost\custom

  // if filesystem file:
  // std::filesystem::path p = std::filesystem::current_path() / txtpath;
  // std::cout << "file size :" << std::filesystem::file_size(p) << "\n";
  std::string Path;
  uint64_t Size = 0;
  char Type = 's';

  std::filesystem::path cwd;

  for (auto p : PathToFilesArr)
  {
    Path = p;
    cwd = Path;
    Size = std::filesystem::file_size(cwd);

    if (Size > Value_Threshold)
    {
      Type = 'l'; // Large ///Types::LargeFile;
    }
    else
    {
      Type = 's'; // Small
    }

    Files.emplace_back(Path, Size, Type); /// Push_back()
  }
}

// bool LineCounter::FilesSortfunction (const File &File1, const File &File2) {
// std::cout << "FilesSortfunction : " << (File1.size < File2.size) << std::endl;
// return (File1.size < File2.size);
// }
// bool LineCounter::FilesSortfunction1 (std::vector<File>::iterator it1, std::vector<File>::iterator it2) {
// return (it1->size < it2->size);
// }

bool LineCounter::SortFiles()
{

  /////
  /// sort by size

  std::sort(Files.begin(), Files.end()); //, [](const File& p1, const File& p2){ return p1.size < p2.size; });

  // for (std::vector<File>::iterator it=Files.begin(); it!=Files.end(); ++it) {
  //   std::cout << ' ' << *it.size;
  // }
}

bool LineCounter::GenerateTasks()
{

  std::string Path;
  uint64_t Size = 0;
  char Type = 'f';

  std::filesystem::path cwd = Path;
  uint64_t Lc = 0;
  // Type = 'f';
  uint64_t Lowerbound = 0;
  uint64_t Chunksize = 0; // upperbound

  for (auto &f : Files)
  {

    if (f.type == 's')
    {
      Type = 'f';

      Tasks.emplace_back(f, Lc, Type, 0, mio::map_entire_file);
    }
    else
    {

      // uint64_t Value_Threshold = 1024*1000; ///example value
      // uint64_t BaseChunkSize = 1024*1000;//128;//1024;

      float mmappartsf = f.size / (float)BaseChunkSize; // / 1024; //num of chunks
      unsigned int mmapparts = std::ceil(mmappartsf);   // / 1024; //num of chunks

      /// int / int = round to 0 : 3.5->3
      // back(last) chunk:
      // mmaplowerbound, mio::map_entire_file

      /// for this programm
      uint64_t mmaplowerbound = 0; // can add in func body
      // uint64_t mmapupperbound = 0;//can add in func body

      // mmaparr.reserve(mmapparts);//?
      uint64_t mmapchunksize = f.size / mmapparts;
      // Type = 'c';
      for (size_t i = 0; i < mmapparts; i++)
      {

        mmaplowerbound = mmapchunksize * i;
        // mmapupperbound

        if (i == mmapparts - 1)
        {
          Type = 'c';
          Tasks.emplace_back(f, Lc, Type, mmaplowerbound, mio::map_entire_file);
        }
        else
        {
          Type = 'c';
          // Tasks.emplace_back(f, Lc , Type, Lowerbound, Chunksize);
          Tasks.emplace_back(f, Lc, Type, mmaplowerbound, mmapchunksize);
        }

      } // for
    }   // else

  } // files arr

  if (Tasks.size() > 0)
  {
    return true;
  }
  else
  {
    return false;
  }

} // file

uint64_t LineCounter::ProcessTasks()
{

// for (auto t : Tasks) {
#pragma omp parallel for
  for (int i = 0; i < Tasks.size(); ++i)
  {
    if (Tasks[i].type == 'f')
    {
      Tasks[i].lc = ProcessTextFile(Tasks[i].file.Path);
    }
    else
    {
      // if (t.type == 'c')
      Tasks[i].lc = ProcessTextFileChunk(Tasks[i].file.Path, Tasks[i].lowerbound, Tasks[i].chunksize);
    }
  }

  // ///tests
  for (auto f : Files)
  {
    std::cout << "file Path : " << f.Path << std::endl;
    std::cout << "file size : " << f.size << std::endl;
    std::cout << "file type : " << f.type << std::endl;
  }
  //

  // #pragma omp parallel for
  for (auto t : Tasks)
  {

    // #pragma omp critical //LogUpdate
    // {
    GlobalLineCounter = GlobalLineCounter + t.lc;
    // }

    /// tests
    std::cout << "task  t.file.Path: " << t.file.Path << std::endl;
    std::cout << "task  t.file.size: " << t.file.size << std::endl;
    std::cout << "task  t.file.type: " << t.file.type << std::endl;
    std::cout << "task  t.type: " << t.type << std::endl;
    std::cout << "task  t.lc: " << t.lc << std::endl;
    std::cout << "task  t.lowerbound: " << t.lowerbound << std::endl;
    std::cout << "task  t.chunksize: " << t.chunksize << std::endl;
    std::cout << "\n";
    //
  }
  /////
  return GlobalLineCounter;
}
/////

#endif /// LINECOUNTER_H

/////

// //////

// // enum { map_entire_file = 0 };
// // enum class access_mode
// // {
// //     read,
// //     write
// // };
// // namespace CmdLine
// // {
// // enum class EType : std::size_t
// // {

// #endif /// LINECOUNTER_H

// /// 1 4 2 6 // 2 1 6 3 //6? 2 5 1 3 // 2 wrong ans
// /// 5 txt 336 0 // 1 txt 3495084 0.437025 // 100 txt 34948409 5.04729
// /// 5 txt 248 0.002 // 1 txt 0 0.111 // 100 txt 0 1.16407
// /// 5 txt 336 0.011 // 1 txt 3495084 4.06223 // 100 txt 34948409 39.6253
// /// 5 txt 336 0.001 // 1 txt 3495084 5.00929 // 100 txt 34948409 52.138
// /// 5 txt 336 1024 1024 // 1 txt 3495084 // 100 txt 34948409 4.78727
// /////
// /// 5 txt 336 0 // 1 txt 3495084 0.602035

// /// map -> now best perfomance

// /// on release build -> reserved size vector -> best perfomance(check again)

// /// map read -> now best perfomance
