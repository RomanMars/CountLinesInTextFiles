# CountLinesInTextFiles
Readme for this program.

This program count total number of lines, in all text files - in a given directory. Assume that files found in the given directory are text files.
Count only ascii, no utf-8 or 16 support now(will add).

Program use multiply treads, to generate files, and count lines in text files.
lib: OpenMP

Small files count in one process.
Large files count in chunks.

Use all avaliable cores.

Usage:
linecounter <path-to-a-directory>
examples:
//  LinesInTextFiles.exe linecounter D:\Cpp\LinesInTextFiles\build\TextFiles1
//  LinesInTextFiles.exe linecounter TextFiles1 pathrelative

For tests(will generate folder, process and do tests):
linecountertests

For textfile generation:
generate

Read files perfomance tests(root\5.txt -> for tests):
perftests


/////

For calculation - used memory map:
faster than io file streams, vectors, and other - file read approaches.
tests: PerfomanceTests.txt

Tested on windows os. Used libs are cross platform.(can work on linux)

///base work explanation:

///read folder
///get text files
///sort files by size
///generate tasks
///process tasks(openMP)

/////

Defines:

LineCounter.h
#define D_Value_Threshold 1024//1024*1000 -> check file small or large
#define D_BaseChunkSize 1024//1024*1000 -> define base chunksize(can vary or same)

/// to use fixed chunk size-> replace line generatetasks func : Tasks.emplace_back(f, Lc , Type, mmaplowerbound, (BaseChunkSize*1024);

LinesInTextFiles.cpp
#define GenerateRandomTextFilesNum 10
#define GenerateRandomTextFilesMinSize 128
#define GenerateRandomTextFilesMaxSize 2048

/////

Usage Examples:


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


