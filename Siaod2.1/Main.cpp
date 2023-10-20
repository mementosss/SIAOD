#include <iostream>
#include <fstream>
#include "Header.h"

int main() {
    setlocale(LC_ALL, "Russian");
    const char* inputFileName = "input.txt";
    const char* outputFileName = "output.txt";

    std::ofstream fout;

    inFile(fout, inputFileName);
    fileOutput(inputFileName);
    addNewLine(fout, inputFileName);
    findNumbers(inputFileName);
    length_file(inputFileName);
    divideOddNumbersByAverage(inputFileName, outputFileName);

    return 0;
}