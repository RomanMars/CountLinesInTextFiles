// #pragma once
#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream> // std::cin, std::cout
#include <fstream>  // std::ofstream

#include <string>

#include <cstdint>

#include <vector>

#include <filesystem> //filesize

#include <mio/mmap.hpp>

uint64_t ProcessTextFile(std::string txtpath) // return type uint64_t CalcLinesInTextFiles
{
  /////

  uint64_t CalcLinesInTextFiles = 0;
  auto t1 = std::chrono::high_resolution_clock::now();
  /// mmap_source read mmap_sink rwrite
  mio::mmap_source mmap(txtpath, 0, mio::map_entire_file); // this is r.w mmap -> can use read
  for (auto &c : mmap)
  {
    if (c == '\n')
    {
      CalcLinesInTextFiles++;
    }
  }

  auto t2 = std::chrono::high_resolution_clock::now();
  auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "7.2 mmap funct read :" << CalcLinesInTextFiles << "\n";
  std::cout << "perf :" << time_span.count() << "\n";
  mmap.unmap();

  return CalcLinesInTextFiles;

  /////
}
uint64_t ProcessTextFileChunk(std::string txtpath, uint64_t lowerbound, uint64_t mmapchunksize)
{

  /// can swap filesyste size to -> int length =  filelength(fd);

  /////

  uint64_t CalcLinesInTextFiles = 0;
  auto t1 = std::chrono::high_resolution_clock::now();
  /// mmap_source read mmap_sink rwrite
  mio::mmap_source mmap(txtpath, lowerbound, mmapchunksize); // this is r.w mmap -> can use read
  for (auto &c : mmap)
  {
    if (c == '\n')
    {
      CalcLinesInTextFiles++;
    }
  }

  auto t2 = std::chrono::high_resolution_clock::now();
  auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "7.2 mmap funct r chunk :" << CalcLinesInTextFiles << "\n";
  std::cout << "perf :" << time_span.count() << "\n";
  mmap.unmap();

  return CalcLinesInTextFiles;

  /////
}

void ProcessTextFilePerfomanceTests(std::string txtpath)
{

  /////

  /// count number of lines in given text files, in given programm
  uint64_t CalcLinesInTextFiles = 0;
  /// char to tore character, in given programm
  char c = '\n';

  // name = path + "\\" + std::to_string(i) + ".txt";
  std::ifstream infile(txtpath);

  int testint1;
  std::cout << "testint1 :" << testint1 << "\n";

  auto t1 = std::chrono::high_resolution_clock::now();

  while (infile.get(c))
  { // loop getting single characters
    if (c == '\n')
    {
      CalcLinesInTextFiles++;
    }
  }

  auto t2 = std::chrono::high_resolution_clock::now();
  auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

  std::cout << "1 lc getc :" << CalcLinesInTextFiles << "\n";
  std::cout << "perf :" << time_span.count() << "\n";
  /// 5 txt 336 0 // 1 txt 3495084 0.437025 // 100 txt 34948409 5.04729

  t1 = std::chrono::high_resolution_clock::now();

  std::ifstream in(txtpath, std::ifstream::ate | std::ifstream::binary);
  int sizep1 = in.tellg();
  std::cout << "file size std :" << sizep1 << "\n";
  t2 = std::chrono::high_resolution_clock::now();
  time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "perf :" << time_span.count() << "\n";

  t1 = std::chrono::high_resolution_clock::now();
  std::filesystem::path p = std::filesystem::current_path() / txtpath;
  // std::cout << "The size of " << p.u8string() << " is " <<
  //     std::filesystem::file_size(p) << " bytes.\n";
  std::cout << "file size :" << std::filesystem::file_size(p) << "\n";
  t2 = std::chrono::high_resolution_clock::now();
  time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "perf :" << time_span.count() << "\n";

  t1 = std::chrono::high_resolution_clock::now();
  std::ifstream instream(txtpath, std::ios::in | std::ios::binary);
  std::vector<uint8_t> textdata((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());

  std::cout << "vecotrized file size :" << textdata.size() << "\n";
  t2 = std::chrono::high_resolution_clock::now();
  time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "perf :" << time_span.count() << "\n";

  t1 = std::chrono::high_resolution_clock::now();

  CalcLinesInTextFiles = 0;
  std::ifstream infileb(txtpath, std::ios::in);

  // get size of file
  infileb.seekg(0, infileb.end);
  uint64_t size = infileb.tellg();
  infileb.seekg(0);

  std::cout << "file size :" << size << "\n";

  // allocate memory for file content
  char *buffer = new char[size];

  // read content of infile
  infile.read(buffer, size);
  // release dynamically-allocated memory
  int lcountbuf;

  for (uint64_t i = 0; i < size; i++)
  {
    // if (buffer[i]==(int)'\n') {
    if (buffer[i] == 10)
    {

      // lcountbuf++;
      CalcLinesInTextFiles++;
    }
  }
  t2 = std::chrono::high_resolution_clock::now();
  time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

  std::cout << "2 lc from buf :" << CalcLinesInTextFiles << "\n";
  std::cout << "perf :" << time_span.count() << "\n";
  /// 5 txt 248 0.002 // 1 txt 0 0.111 // 100 txt 0 1.16407

  delete[] buffer;

  /////

  t1 = std::chrono::high_resolution_clock::now();

  instream.close();

  CalcLinesInTextFiles = 0;
  instream.open(txtpath, std::ios::in | std::ios::binary);
  std::vector<uint8_t> vtextdata((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());

  // std::cout << "vecotrized file size :" << vtextdata.size() << "\n";
  /// C++ variable init
  uint64_t lcountvbuf; /// init work -> var from start is random garbage val
  int lcountint;
  unsigned int lcountvecint2;
  for (uint64_t i = 0; i < textdata.size(); i++)
  {

    // if (textdata[i]==(int)'\n') {
    if ((uint8_t)textdata[i] == 10)
    { //(uint64_t)textdata[i] // uint8_t

      lcountvbuf++;                // l = l +1
      lcountvbuf = lcountvbuf + 1; // l = l +1
      lcountint = lcountint + 1;
      lcountvecint2++;
      CalcLinesInTextFiles++;
    }
  }

  for (size_t i = 0; i < 2; i++)
  {
    std::cout << "textdata[i] :" << textdata[i] << "\n";
  }
  std::cout << "\n";

  for (size_t i = 0; i < 2; i++)
  {
    std::cout << "textdata[i] :" << (uint64_t)textdata[i] << "\n"; // uint8_t
  }
  std::cout << "\n";

  t2 = std::chrono::high_resolution_clock::now();
  time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

  std::cout << "3 lc from vec :" << CalcLinesInTextFiles << "\n"; // 1 txt 3495084 // 100 txt 34948409
  std::cout << "lcountint from vec :" << lcountint << "\n";       // 1 txt 3495085 // 100 txt 34948410
  std::cout << "lcountint 2 from vec :" << lcountint << "\n";     // 1 txt 3495085 // 100 txt 34948410
  std::cout << "perf :" << time_span.count() << "\n";
  /// 5 txt 336 0.011 // 1 txt 3495084 4.06223 // 100 txt 34948409 39.6253
  /////

  t1 = std::chrono::high_resolution_clock::now();

  instream.close();

  CalcLinesInTextFiles = 0;
  instream.open(txtpath, std::ios::in | std::ios::binary);
  std::vector<uint8_t> vtextdata1;
  vtextdata1.reserve(999999999); ///(std::vector::max_size);
  vtextdata1.assign((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());

  // std::cout << "vecotrized file size :" << vtextdata.size() << "\n";
  uint64_t lcountvbuf2;

  for (uint64_t i = 0; i < vtextdata1.size(); i++)
  {

    // if (vtextdata1[i]==(int)'\n') {
    if ((uint64_t)vtextdata1[i] == 10)
    { /// 336->387, some time work -> som times wrong values

      // lcountvbuf2++;
      CalcLinesInTextFiles++;
    }
  }

  t2 = std::chrono::high_resolution_clock::now();
  time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

  std::cout << "4 lc from reserve vec :" << CalcLinesInTextFiles << "\n";
  std::cout << "perf :" << time_span.count() << "\n";
  /// 5 txt 336 0.001 // 1 txt 3495084 5.00929 // 100 txt 34948409 52.138
  //////

  CalcLinesInTextFiles = 0;
  FILE *fd = NULL;
  int cnt, cha;

  fd = fopen(txtpath.c_str(), "r");
  if (fd == NULL)
  {
    perror(txtpath.c_str());
    exit(-1);
  }

  CalcLinesInTextFiles = 0;
  while (EOF != (cha = fgetc(fd)))
  {
    /*
     * int fgetc(FILE *) returns unsigned char cast to int
     * Because it has to return EOF or error also.
     */
    if (cha == '\n')
      ++cnt;
    CalcLinesInTextFiles++;
  }

  // printf("cnt line in %s is %d\n", "5.txt", cnt);

  // std::cout << "lines in 5.txt: " << "\n";
  std::cout << "5 Number of lines in text file from C: " << cnt << "\n"; // 336 // 495084 // 34948409
  std::cout << "5 lc from C: " << CalcLinesInTextFiles << "\n";          // 336,1024 // 10485760 // 104857600
  std::cout << "lc int from C: " << (int)CalcLinesInTextFiles << "\n";   // 336,1024 // 10485760 // 34948409
                                                                         /// 5 txt 336 1024 1024 // 1 txt 3495084 // 100 txt 34948409 4.78727
                                                                         /////

  CalcLinesInTextFiles = 0;
  std::ifstream infiletest2(txtpath);

  t1 = std::chrono::high_resolution_clock::now();

  while (infiletest2.get(c))
  { // loop getting single characters
    if (c == '\n')
    {
      CalcLinesInTextFiles++;
    }
  }

  t2 = std::chrono::high_resolution_clock::now();
  time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

  std::cout << "6 lc getc test2 :" << CalcLinesInTextFiles << "\n";
  std::cout << "perf :" << time_span.count() << "\n";
  /// 5 txt 336 0 // 1 txt 3495084 0.602035

  infiletest2.close(); // close file

  /////

  CalcLinesInTextFiles = 0;
  t1 = std::chrono::high_resolution_clock::now();
  mio::mmap_sink mmap1(txtpath, 0, mio::map_entire_file); // this is r.w mmap -> can use read
  for (auto &c : mmap1)
  {
    if (c == '\n')
    {
      CalcLinesInTextFiles++;
      // std::cout << "Got1";
    }
  }

  t2 = std::chrono::high_resolution_clock::now();
  time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "7 lc mmap1 :" << CalcLinesInTextFiles << "\n";
  std::cout << "perf :" << time_span.count() << "\n";
  mmap1.unmap();

  /////

  CalcLinesInTextFiles = 0;
  t1 = std::chrono::high_resolution_clock::now();
  mio::mmap_source mmap1r(txtpath, 0, mio::map_entire_file); // this is r.w mmap -> can use read
  for (auto &c : mmap1r)
  {
    if (c == '\n')
    {
      CalcLinesInTextFiles++;
    }
  }

  t2 = std::chrono::high_resolution_clock::now();
  time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "7 read lc mmap1r :" << CalcLinesInTextFiles << "\n";
  std::cout << "perf :" << time_span.count() << "\n";
  mmap1r.unmap();

  /////

  CalcLinesInTextFiles = 0;

  uint64_t mmapfilesize = std::filesystem::file_size(p);
  std::cout << "7.1 mmapfilesize :" << mmapfilesize << "\n";
  unsigned int mmapparts = 3; // num of chunks
  uint64_t mmapchunksize = mmapfilesize / mmapparts;
  std::cout << "7.1 lc mmapchunksize :" << mmapchunksize << "\n";

  std::vector<mio::mmap_source> mmaparr; // this is r.w mmap -> can use read

  mmaparr.reserve(mmapparts); //?

  uint64_t mmaplowerbound;
  uint64_t mmapupperbound;

  // mio::mmap_sink mmapN;
  // std::error_code error;
  // #pragma omp parallel for //-> dont work with i ///:0:453:2:0:453:0:0:453 // loop index dont work on lul and etc
  // #pragma omp parallel for private(i)
  /// for parralel create var i, i++ every loopc circle, and create critical section during i++
  // int i    for(i = 0; i < count; ++i)
  for (int i = 0; i < mmapparts; i++)
  {
    /// lowerbound = partsize *i(if i != 0 -> +1)
    /// upperbound = partsize *(i+1)int i;

    ///

    /// used?
    if (i != 0)
    {
      mmaplowerbound = (mmapchunksize * i) + 1;
    }
    else
    {
      mmaplowerbound = mmapchunksize * i;
    }

    if (i == mmapparts - 1)
    {
      mmapupperbound = mmapfilesize - 1;
    }
    else
    {
      mmapupperbound = mmapchunksize * (i + 1);
    }

    ///
    mmaplowerbound = mmapchunksize * i;

    std::cout << "7.1 mmaplowerbound :" << mmaplowerbound << "\n"
              << std::endl;
    std::cout << "7.1 mmapupperbound :" << mmapupperbound << "\n"
              << std::endl;
    std::cout << "7.1 loop indx :" << i << "\n"
              << std::endl;

    /// works
    if (i == mmapparts - 1)
    {
      mmaparr.emplace_back(txtpath, mmaplowerbound, mio::map_entire_file);
    }
    else
    {
      mmaparr.emplace_back(txtpath, mmaplowerbound, mmapchunksize);
    }
    /// if file size: 7 2 chunks 7/2 =3? 3, 3 where is 7th byte?!!!! Need tests
    // mmaparr.emplace_back(txtpath, mmaplowerbound, mmapchunksize);
  }

  CalcLinesInTextFiles = 0;
  /// used for calc lines in text file in this programm
  int CalcLinesInTextFilesInt = 0;
  int CharsinMaps = 0;

  std::cout << "7.1 CalcLinesInTextFiles :" << CalcLinesInTextFiles << "\n";
  t1 = std::chrono::high_resolution_clock::now();
  // for (auto &m : mmaparr) // i<mmapparts
  // #pragma omp parallel for
  for (uint64_t i = 0; i < mmaparr.size(); i++) // i<mmapparts /// can try int
  {
    // for (auto &c : mmaparr[i])
    for (uint64_t j = 0; j < mmaparr[i].size(); j++)
    {
      // #pragma omp critical //LogUpdate
      // {
      CharsinMaps++;
      // }
      // if (c == '\n')
      if (mmaparr[i][j] == '\n')
      {
        // std::cout << mmaparr[i][j] << std::endl;
        // #pragma omp critical //LogUpdate
        // {
        CalcLinesInTextFiles++;
        CalcLinesInTextFilesInt++;
        // }
      }
    }
  }

  t2 = std::chrono::high_resolution_clock::now();
  time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  std::cout << "7.1 lc chunks mmap :" << CalcLinesInTextFiles << "\n";
  std::cout << "7.1 lc chunks mmap int :" << CalcLinesInTextFilesInt << "\n";
  std::cout << "7.1 CharsinMaps :" << CharsinMaps << "\n";
  std::cout << "perf :" << time_span.count() << "\n";
}

//////

///// openMP chunks wih multymap with mutex -> huge perfomance boost
///// perfomance debug and release tests in txt file

/////

// debug:
// 1 336 0.001, 2 327 0, 3 336 0.014, 4 336 0, 6 336 0, 7 336 0, 7 read 336 0, 7.1 306(296)(wrong ans) 0.006(perf with a lot of cout)
// file size perf 0.001
// 1 3495084 0.566, 2 0 0.105, 3 3495084(0 index only correct) 3.46, 4 3495084 4.354, 6 3495084 0.44, 7 3495084 0.178, 7 read 3495084 0.181, 7.1 err

// debug:
// 1 336 0.025, 327 0.001, 336 0.003, 4 336 0.01, 6 336 0,7 336 0, 7 read 336 0, 326(327) 0.015
// 1 3495084 6.043, 2 0 0.11, 3 3495084(3495085) 4.109, 4 3495084 4.811, 6 3495084 0.474, 7 3495084 0.221, 7 r 3495084 0.198, 7.1 3204815(3180126) 0.77
// 1 34948409 34.747, 2 0, 3 34948409(34948410) 77.227, 4 34948409 45.8566, 6 634948409 4.37125, 7 34948409 1.784, 7 r 34948409 1.856, 7.1 28353750(27879777) 8.44648

#endif /// FILEPROCESSOR_H
