#include "Header.h"

void inFile(std::ofstream& fout, const char* inputFileName) {
    std::cout << "Открытие и заполнение первого файла\n";
    fout.open(inputFileName, std::ios::out | std::ios::trunc); //если файл уже существует, его содержимое будет удалено, а если файл не существует, будет создан новый файл.
    for (int i = 1; i <= 10; i++) {
        fout << i << std::endl;
    }
    if (fout.good()) {
        std::cout << "  Ошибок не возникло\n";
    }
    else {
        std::cout << "   Ошибки возникли\n";
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
    std::cout << "Введите элемент, который хотите добавить: ";
    std::cin >> x;
    fout.open(inputFileName, std::ios::out | std::ios::app); // все данные будут добавляться в конец файла
    fout << x;
    if (fout.good()) {
        std::cout << "  Ошибок не возникло\n";
    }
    else {
        std::cout << "   Ошибки возникли\n";
    }
    fout.close();
}

void findNumbers(const char* inputFileName) {
    int nums = 0;
    std::cout << "Введите порядковый номер в файле: ";
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
        std::cout << "  Ошибок не возникло\n";
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
        fout >> x; //cчитывание значения из файла и присваивание его переменной x
        fout.get(); //переход на новую строку
        n++;
    }
    std::cout << "Количество чисел: " << n << std::endl;
    fout.close();
}

void divideOddNumbersByAverage(const char* inputFileName, const char* outputFileName) {
    std::cout << "  Открытие и заполнение второго файла: \n";
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        std::cout << "Ошибка открытия исходного файла\n";
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

    // Переходим к началу файла
    inputFile.clear(); //clear() позволяет сбросить любые флаги ошибок или состояния файла, чтобы файл снова стал доступным для чтения
    //используется std::ios::beg второй аргумент, чтобы указать, что позиция должна быть установлена в начало файла
    //Первый аргумент 0 указывает на смещение относительно начала файла
    inputFile.seekg(0, std::ios::beg);

    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        std::cout << "Ошибка открытия файла для записи\n";
        inputFile.close();
        return;
    }

    while (inputFile >> number) {
        // Если число нечетное по абсолютной величине, делим его на среднее арифметическое и записываем в новый файл
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
        std::cout << "\n  Ошибок не возникло\n";
    }
    else {
        std::cout << "   Ошибки возникли\n";
    }
    inputFile.close();
    outputFile.close();
    std::cout << "\n///Завершение программы///\n";
}
