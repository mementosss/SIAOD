#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>

void inFile(std::ofstream& fout, const char* inputFileName);
void fileOutput(const char* inputFileName);
void addNewLine(std::ofstream& fout, const char* inputFileName);
void findNumbers(const char* inputFileName);
void length_file(const char* inputFileName);
void divideOddNumbersByAverage(const char* inputFileName, const char* outputFileName);

#endif