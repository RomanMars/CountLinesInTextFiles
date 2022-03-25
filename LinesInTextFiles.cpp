#include <string>
#include <iostream>
// #include <filesystem>

#include <fstream>
// #include <SSVUtils\SSVUtils.hpp>

#include <FilesInFolder.h>
#include <FileGenerator.h>
#include <TextFileProcessor.h>

#include <LineCounter.h>

#include <CTPL\ctpl_stl.h>

#include <future>

#include <filesystem>

// #ifdef _OPENMP
// #include <omp.h>
// #endif
#include <omp.h>

/// for tests FILE fgetc
#include <stdio.h>
#include <iterator> // std::istream_iterator

#include <mio/mmap.hpp>


/// size in kb
#define GenerateRandomTextFilesNum 10
#define GenerateRandomTextFilesMinSize 128
#define GenerateRandomTextFilesMaxSize 2048

#define OtherTests 1
#ifdef OtherTests
#endif




// #  if __cplusplus >= 201703L && __has_include(<filesystem>)
// #    include <filesystem>
//      namespace fs = std::filesystem;
// std::cout << "C++ 17 " << "\n";
// # else
// // const fs::path sandbox{"sandbox"};
// std::cout << " C++ not 17 " << "\n";
// #include boost

// #  endif

int main(int argc, char **argv) // main()
{

  /// cout to dec;
  std::cout << std::dec << '\n';

  // ///std::vector<std::string> filesinfolderv;

  // /// #ifdef _WIN32

  // ///read_directory("../libs", filesinfolderv);

  // /// #endif

  // ///// thread_pool
  //     ctpl::thread_pool p(2 /* two threads in the pool */);

  /////cout -> some reason work in hex mode, set to dec
  // int n = 70;
  // std::cout << std::dec << n << '\n';
  /////

  /////

  /// TESTS
  /// generate files for tests 1,10,100+ mb
  // std::cout << "lines in 1.txt(10+mb): " << "\n";
  //     ProcessTextFilePerfomanceTests("1.txt");
  // std::cout << "lines in 100.txt(100+mb): " << "\n";
  //     ProcessTextFilePerfomanceTests("100.txt");

  ///// TESTS
  /// tests 1,10,100+ mb
  // ProcessTextFile("100.txt");
  // ProcessTextFileChunk("100.txt", 0 , mio::map_entire_file);

  /////

  /// argv
  std::string args;
  std::vector<std::string> argstrv;
  // args.length
  if (argc > 1)
  {
    for (int i = 0; i < argc; ++i)
    {
      std::cout << "argvnum " << i << " : " << argv[i] << std::endl;
      argstrv.push_back(argv[i]);
    }
    if (argc >= 3)
    {
      for (auto c : argstrv[2])
      {
        if (c == '\x1f')
        {
          c = '/';
          // exmpl: D:/Cpp/LinesInTextFiles/build/TextFiles1"
        }
      }
    }

    std::cout << "argc : " << argc << std::endl;

    if (argstrv[1] == "linecounter" && argstrv[2].length() >= 3)
    {
      if (argstrv[3] == "pathrelative")
      {
        LineCounter lcArg(argstrv[2]);
        std::cout << "GlobalLineCounter : " << lcArg.GlobalLineCounter << std::endl;
      }
      if (argstrv[1] == "linecounter" && argc == 3)
      {
        LineCounter lcArg(argstrv[2], false);
        std::cout << "GlobalLineCounter : " << lcArg.GlobalLineCounter << std::endl;
      }
    }

    if (argstrv[1] == "perftests")
    {

      ///// Test process textfile 5.txt

      // std::cout << "/* Test process textfile 5 txt */" << std::endl;
      // ProcessTextFile(testpath1); //  testpath1 = "5.txt";
      std::cout << "/* Test process textfile 5 txt */" << std::endl;
      std::string testpath1 = "5.txt"; // already   testpath1 = "5.txt";
      std::cout << "lines in 5.txt(1+kb): "
                << "\n";
      ProcessTextFilePerfomanceTests(testpath1);
    }

    if (argstrv[1] == "generate")
    {
      /// path, create, generate - > tests

      std::string txtpath = "TextFiles1";
      std::filesystem::path cwd = std::filesystem::current_path() / txtpath;
      txtpath = cwd.string();
      std::cout << "root(build)/TextFiles1 fold: " << txtpath << "\n";
      std::cout << "root(build)/TextFiles1 create dir: " << std::endl;
      std::filesystem::create_directory(txtpath);
      std::cout << "GenerateRandomTextFiles" << std::endl;
      auto t1 = std::chrono::high_resolution_clock::now();
      // GenerateRandomTextFiles(10, 128, 2048, txtpath);
      GenerateRandomTextFiles(GenerateRandomTextFilesNum, GenerateRandomTextFilesMinSize, GenerateRandomTextFilesMaxSize, txtpath);

      auto t2 = std::chrono::high_resolution_clock::now();
      auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

      std::cout << "/* duration1 */" << time_span.count() << std::endl;
    }
    if (argstrv[1] == "generateandcountlines")
    {

      /// path, create, generate - > tests

      std::string txtpath = "TextFiles1";
      std::filesystem::path cwd = std::filesystem::current_path() / txtpath;
      txtpath = cwd.string();
      std::cout << "root(build)/TextFiles1 fold: " << txtpath << "\n";
      std::cout << "root(build)/TextFiles1 create dir: " << std::endl;
      std::filesystem::create_directory(txtpath);

      std::cout << "GenerateRandomTextFiles" << std::endl;
      auto t1 = std::chrono::high_resolution_clock::now();

      // GenerateRandomTextFiles(10, 128, 2048, txtpath);
      GenerateRandomTextFiles(GenerateRandomTextFilesNum, GenerateRandomTextFilesMinSize, GenerateRandomTextFilesMaxSize, txtpath);

      auto t2 = std::chrono::high_resolution_clock::now();
      auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

      std::cout << "/* duration1 */" << time_span.count() << std::endl;
      /////

      /// here is simple work example -> without chunks
      std::vector<std::string> PathToFilesArr;

      std::string Path123 = "TextFiles1";

      /////
      /// here is simple work example -> without chunks:

      PathToFilesInFolder(Path123, PathToFilesArr, true);

      uint64_t globallinecounter = 0;
      // #pragma omp parallel for //comment for tests
      for (auto Path : PathToFilesArr)
      {
        std::cout << Path << "\n";
        //     #pragma omp critical //LogUpdate
        // {
        globallinecounter = globallinecounter + ProcessTextFile(Path);
        // }
      }
      std::cout << "globallinecounter : " << globallinecounter << std::endl;
    }

    if (argstrv[1] == "linecountertests")
    {

      /// path, create, generate - > tests

      std::string txtpath = "TextFiles1";
      std::filesystem::path cwd = std::filesystem::current_path() / txtpath;
      txtpath = cwd.string();
      std::cout << "root(build)/TextFiles1 fold: " << txtpath << "\n";
      std::cout << "root(build)/TextFiles1 create dir: " << std::endl;
      std::filesystem::create_directory(txtpath);

      std::cout << "GenerateRandomTextFiles" << std::endl;
      auto t1 = std::chrono::high_resolution_clock::now();

      // GenerateRandomTextFiles(10, 128, 2048, txtpath);
      GenerateRandomTextFiles(GenerateRandomTextFilesNum, GenerateRandomTextFilesMinSize, GenerateRandomTextFilesMaxSize, txtpath);

      auto t2 = std::chrono::high_resolution_clock::now();
      auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

      std::cout << "/* duration1 */" << time_span.count() << std::endl;
      /////
      /// work example LineCounter class
      LineCounter lc(txtpath);
      std::cout << "GlobalLineCounter : " << lc.GlobalLineCounter << std::endl;
    }

    /////  Command line examples:

    ///some Command line use: .\ at start of arg

    // linecounter <path-to-a-directory>
    // LinesInTextFiles.exe linecounter D:\Cpp\LinesInTextFiles\build\TextFiles1

    // linecounter <relative-to-exec-root_path-to-a-directory>
    // LinesInTextFiles.exe linecounter TextFiles1 pathrelative

    // Read, write files perfomance tests
    //  LinesInTextFiles.exe perftests

    // Generate folder with text files (default: TextFiles1)
    // LinesInTextFiles.exe generate

    // Generate folder with text files. And count lines in generated text files.(default: TextFiles1)
    // LinesInTextFiles.exe generateandcountlines

    // Generate folder with text files. And count lines -> use LineCounterClass generated txt files.
    // LinesInTextFiles.exe linecountertests
  }
  std::cin.get();
}

