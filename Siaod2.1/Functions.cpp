#include "Header.h"

void inFile(std::ofstream& fout, const char* inputFileName) {
    std::cout << "�������� � ���������� ������� �����\n";
    fout.open(inputFileName, std::ios::out | std::ios::trunc); //���� ���� ��� ����������, ��� ���������� ����� �������, � ���� ���� �� ����������, ����� ������ ����� ����.
    for (int i = 1; i <= 10; i++) {
        fout << i << std::endl;
    }
    if (fout.good()) {
        std::cout << "  ������ �� ��������\n";
    }
    else {
        std::cout << "   ������ ��������\n";
    }
    fout.close();
}

void fileOutput(const char* inputFileName) {
    int x;
    std::ifstream fout;
    fout.open(inputFileName, std::ios::in);
    while (fout >> x) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    fout.close();
}
void addNewLine(std::ofstream& fout, const char* inputFileName) {
    int x = 0;
    std::cout << "������� �������, ������� ������ ��������: ";
    std::cin >> x;
    fout.open(inputFileName, std::ios::out | std::ios::app); // ��� ������ ����� ����������� � ����� �����
    fout << x;
    if (fout.good()) {
        std::cout << "  ������ �� ��������\n";
    }
    else {
        std::cout << "   ������ ��������\n";
    }
    fout.close();
}

void findNumbers(const char* inputFileName) {
    int nums = 0;
    std::cout << "������� ���������� ����� � �����: ";
    std::cin >> nums;
    std::ifstream fout;
    fout.open(inputFileName);
    int x;
    int i;
    std::cout << "> ";
    for (i = 0; (i < nums && (!fout.eof())); i++) {
        fout >> x;
        fout.get();
    }
    std::cout << x;

    if (fout.good()) {
        std::cout << "  ������ �� ��������\n";
    }
    fout.close();
}

void length_file(const char* inputFileName) {
    std::ifstream fout;
    fout.open(inputFileName);
    int n = 0;
    int x;
    std::cout << std::endl;
    while (!fout.eof()) {
        fout >> x; //c��������� �������� �� ����� � ������������ ��� ���������� x
        fout.get(); //������� �� ����� ������
        n++;
    }
    std::cout << "���������� �����: " << n << std::endl;
    fout.close();
}

void divideOddNumbersByAverage(const char* inputFileName, const char* outputFileName) {
    std::cout << "  �������� � ���������� ������� �����: \n";
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        std::cout << "������ �������� ��������� �����\n";
        return;
    }

    int number = 0;
    int count = 0;
    double sum = 0.0;

    while (inputFile >> number) {
        sum += number;
        count++;
    }
    double average = sum / count;

    // ��������� � ������ �����
    inputFile.clear(); //clear() ��������� �������� ����� ����� ������ ��� ��������� �����, ����� ���� ����� ���� ��������� ��� ������
    //������������ std::ios::beg ������ ��������, ����� �������, ��� ������� ������ ���� ����������� � ������ �����
    //������ �������� 0 ��������� �� �������� ������������ ������ �����
    inputFile.seekg(0, std::ios::beg);

    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        std::cout << "������ �������� ����� ��� ������\n";
        inputFile.close();
        return;
    }

    while (inputFile >> number) {
        // ���� ����� �������� �� ���������� ��������, ����� ��� �� ������� �������������� � ���������� � ����� ����
        if (std::abs(number) % 2 == 1) {
            double dividedValue = number / average;
            outputFile << dividedValue << " ";
            std::cout << dividedValue << " ";
        }
        else {
            outputFile << number << " ";
        }
    }
    if (outputFile.good()) {
        std::cout << "\n  ������ �� ��������\n";
    }
    else {
        std::cout << "   ������ ��������\n";
    }
    inputFile.close();
    outputFile.close();
    std::cout << "\n///���������� ���������///\n";
}