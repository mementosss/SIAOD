#include <iostream>

#include <fstream>
#include <string>

using namespace std;


struct Railway {
    char number[11]; // номер поезда
    char out[10];    // пункт отправления
    char in[10];     // пункт назначения
    char time[6];    // время отправления
};

void ConvertToBinary(const char* textFileName, const char* binaryFileName) {
    ifstream inputFile(textFileName);
    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия текстового файла" << endl;
        return;
    }

    ofstream outputFile(binaryFileName, ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Ошибка создания двоичного файла" << endl;
        return;
    }

    Railway record;
    while (inputFile >> record.number >> record.out >> record.in >> record.time) {
        //reinterpret_cast используется для преобразования указателя на объект record типа Railway к типу const char*.
        //Это делается для того, чтобы функции read и write могли работать с данными структуры Railway в виде последовательности байтов.
        outputFile.write(reinterpret_cast<const char*>(&record), sizeof(Railway));
    }

    inputFile.close();
    outputFile.close();

    cout << "Преобразование завершено" << endl;
}

void SaveToText(const char* binaryFileName, const char* textFileName) {
    ifstream inputFile(binaryFileName, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия двоичного файла" << endl; //Поток cerr не буферизуется
        return;
    }

    ofstream outputFile(textFileName);
    if (!outputFile.is_open()) {
        cerr << "Ошибка создания текстового файла" << endl;
        return;
    }

    Railway record;
    while (inputFile.read(reinterpret_cast<char*>(&record), sizeof(Railway))) {
        outputFile << record.number << " " << record.out << " " << record.in << " " << record.time << endl;
    }

    inputFile.close();
    outputFile.close();

    cout << "Сохранение в текстовый файл завершено" << endl;
}

void PrintAllRecords(const char* binaryFileName) {
    ifstream inputFile(binaryFileName, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия двоичного файла" << endl;
        return;
    }

    Railway record;
    while (inputFile.read(reinterpret_cast<char*>(&record), sizeof(Railway))) {
        cout << "Номер поезда: " << record.number << ", Пункт отправления: " << record.out << ", Пункт назначения: " << record.in << ", Время: " << record.time << endl;
    }

    inputFile.close();
}

void AccessRecordByIndex(const char* binaryFileName, int index) {
    ifstream inputFile(binaryFileName, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия двоичного файла" << endl;
        return;
    }

    Railway record;
    //Функция seekg используется для перемещения указателя чтения в файле на указанный индекс.
    //Указатель перемещается на позицию, соответствующую умноженному на размер структуры Railway. Это позволяет нам перейти к нужной записи в файле.
    inputFile.seekg(index * sizeof(Railway));

    if (inputFile.read(reinterpret_cast<char*>(&record), sizeof(Railway))) {
        cout << "Номер поезда: " << record.number << ", Пункт отправления: " << record.out << ", Пункт назначения: " << record.in << ", Время: " << record.time << endl;
    }
    else {
        cout << "Запись с указанным номером не найдена" << endl;
    }

    inputFile.close();
}


void DeleteRecordByName(const char* binaryFileName, const char* outToDelete) {
    fstream inputFile(binaryFileName, ios::in | ios::binary);
    if (!inputFile) {
        cerr << "Не удалось открыть файл" << endl;
        return;
    }

    // Найдите позицию записи с заданным ключом
    streampos position = -1;
    Railway record;
    streampos a = sizeof(record);
    while (inputFile.read(reinterpret_cast<char*>(&record), sizeof(record))) {
        if ((strcmp(record.number, outToDelete) != 0)) {
            position = inputFile.tellg() - a;
            break;
        }
    }

    // Перейдите к позиции записи, которую нужно удалить
    if (position >= 0) {
        inputFile.seekg(position);
        inputFile.seekp(position);

        // Прочтите последнюю запись файла и запомните ее позицию
        streampos lastPosition = inputFile.tellg();
        Railway lastRecord;
        inputFile.read(reinterpret_cast<char*>(&lastRecord), sizeof(lastRecord));

        // Запишите последнюю запись на позицию удаляемой записи
        inputFile.seekp(position);
        inputFile.write(reinterpret_cast<const char*>(&lastRecord), sizeof(lastRecord));

        // Увеличьте размер файла, чтобы отрезать последние записи
        inputFile.seekp(lastPosition);
        inputFile.close();
        ofstream truncateFile(binaryFileName, ios::trunc | ios::binary);
        truncateFile.close();
    }
    else {
        cout << "Запись с заданным ключом не найдена" << endl;
    }
}

void ListRailsByIn(const char* binaryFileName, const char* in) {
    ifstream inputFile(binaryFileName, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия двоичного файла" << endl;
        return;
    }

    Railway record;
    bool found = false;
    while (inputFile.read(reinterpret_cast<char*>(&record), sizeof(Railway))) {
        if (strcmp(record.in, in) == 0) {
            cout << "Номер поезда: " << record.number << ", Пункт отправления: " << record.out << ", Пункт назначения: " << record.in << ", Время: " << record.time << endl;
            found = true;
        }
    }

    inputFile.close();
    if (!found) {
        cout << "Поездов, отправляющихся в указанный пункт, не найдено" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    const char* binaryFileName = "Railway.dat";
    char textFileName[100]; // Буфер для хранения имени текстового файла
    cout << "Введите имя текстового файла: ";
    cin >> textFileName;
    int choice;
    while (true) {
        cout << "Выберите операцию:" << endl;
        cout << "1. Преобразовать текстовый файл в двоичный" << endl;
        cout << "2. Сохранить двоичный файл в текстовый" << endl;
        cout << "3. Вывести все записи из двоичного файла" << endl;
        cout << "4. Доступ к записи по номеру" << endl;
        cout << "5. Удалить сведения по указанному поезду" << endl;
        cout << "6. Сформировать справку по поездам, отправляющимся в указанный пункт назначения" << endl;
        cout << "7. Выход" << endl;
        cout << "Введите номер операции: ";
        cin >> choice;
        cout << endl;
        switch (choice) {
        case 1:
            ConvertToBinary(textFileName, binaryFileName);
            break;
        case 2:
            SaveToText(binaryFileName, textFileName);
            break;
        case 3:
            PrintAllRecords(binaryFileName);
            break;
        case 4:
            int index;
            cout << "Введите номер записи: ";
            cin >> index;
            AccessRecordByIndex(binaryFileName, index);
            break;
        case 5:
            char outToDelete[50];
            cout << "Введите номер поезда для удаления: ";
            cin.ignore(); // Очистка буфера ввода перед чтением строки
            cin.getline(outToDelete, sizeof(outToDelete));
            DeleteRecordByName(binaryFileName, outToDelete);
            break;
        case 6:
            char in[3];
            cout << "Введите пункт (5 букв): ";
            cin >> in;
            ListRailsByIn(binaryFileName, in);
            break;
        case 7:
            return 0;
        default:
            cout << "Неверный выбор. Пожалуйста, выберите действие из списка." << endl;
            break;
        }
        cout << endl;
    }
    return 0;
}