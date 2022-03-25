// #pragma once
#ifndef FILEGENERATOR_H
#define FILEGENERATOR_H

#include <iostream> // std::cin, std::cout
#include <fstream>  // std::ofstream

#include <string>

#include <stdlib.h> /* srand, rand */
#include <random>

#include <cstdint> // uint64_t support -> for large files

#ifdef _OPENMP
#include <omp.h>
#endif

static uint32_t get32rand()
{
  return (rand() ^ (rand() << 15) ^ (rand() << 30));
}

///// generate files of various size, parameter -> generate random array of files with different size(min max, at least 1 max)
void GenerateTextFile(std::string name, uint64_t NumOfChars)
{

  std::ofstream outfile(name);

  char ch;

  // std::cout << "/* fastrangeint(10, 10) */" << fastrangeint(10, 10) << std::endl;
  // std::cout << "/* fastrange32(100, 5) */" << fastrange32(100, 5) << std::endl;
  // std::cout << "/* fastrangesize(get64rand(), 5)) */" << fastrangesize(get32rand(), 5) << std::endl;

  ///

  std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

  // #pragma omp target teams distribute parallel for
  // #pragma omp parallel for
  for (uint32_t x = 0; x < NumOfChars; ++x)
  {

    // need (a-z,1-3 interval)+ txt
    // a-z 97-122
    // 0-9 48-57
    // 10 \n ->nl

    // ch = (char)std::uniform_int_distribution<int>(0, 128)(rng);

    ///// can improve perf. by creating precalc. random arrs[]

    int type = std::uniform_int_distribution<int>(1, 3)(rng);

    if (type == 1)
    {
      ch = (char)std::uniform_int_distribution<int>(97, 122)(rng);
    }
    if (type == 2)
    {
      ch = (char)std::uniform_int_distribution<int>(48, 57)(rng);
    }
    if (type == 3)
    {
      ch = 10;
    }
    outfile.put(ch);
  }

  /// after write flush data and close "r" file
  outfile.close();
}

void GenerateRandomTextFiles(int Num, int minKbSize, int maxKbSize, std::string path = "TextFiles") // 1kb = 1024 b
{

  std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  char ch;
  std::string name;
  uint64_t size;
  int NumOfChars;

  /// converter in for loop
  ///  byte -> kb conv
  minKbSize = minKbSize * 1024; // Convert bytes to kb
  maxKbSize = maxKbSize * 1024; // Convert bytes to kb

// ch = (char)std::uniform_int_distribution<int>(0, 128)(rng);

// need (a-z,1-3 interval)+ txt
//  a-z 97-122
//  0-9 48-57
//  10 \n ->nl

// #pragma omp parallel for num_threads(8)
// #pragma omp parallel for num_threads(Num) //fastest
// #pragma omp target teams distribute parallel for
#pragma omp parallel for
  for (int i = 0; i < Num; i++)
  {
    name = path + "\\" + std::to_string(i) + ".txt";

    size = minKbSize + std::uniform_int_distribution<int>(0, (maxKbSize - minKbSize))(rng);
    //   #pragma omp parallel for
    GenerateTextFile(name, size);
  }
}

#endif /// FILEGENERATOR_H