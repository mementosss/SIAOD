#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Railway {
    char number[11]; // ����� ������
    char out[10];    // ����� �����������
    char in[10];     // ����� ����������
    char time[6];    // ����� �����������
};

void ConvertToBinary(const char* textFileName, const char* binaryFileName) {
    ifstream inputFile(textFileName);
    if (!inputFile.is_open()) {
        cerr << "������ �������� ���������� �����" << endl;
        return;
    }

    ofstream outputFile(binaryFileName, ios::binary);
    if (!outputFile.is_open()) {
        cerr << "������ �������� ��������� �����" << endl;
        return;
    }

    Railway record;
    while (inputFile >> record.number >> record.out >> record.in >> record.time) {
        //reinterpret_cast ������������ ��� �������������� ��������� �� ������ record ���� Railway � ���� const char*.
        //��� �������� ��� ����, ����� ������� read � write ����� �������� � ������� ��������� Railway � ���� ������������������ ������.
        outputFile.write(reinterpret_cast<const char*>(&record), sizeof(Railway));
    }

    inputFile.close();
    outputFile.close();

    cout << "�������������� ���������" << endl;
}

void SaveToText(const char* binaryFileName, const char* textFileName) {
    ifstream inputFile(binaryFileName, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "������ �������� ��������� �����" << endl; //����� cerr �� ������������
        return;
    }

    ofstream outputFile(textFileName);
    if (!outputFile.is_open()) {
        cerr << "������ �������� ���������� �����" << endl;
        return;
    }

    Railway record;
    while (inputFile.read(reinterpret_cast<char*>(&record), sizeof(Railway))) {
        outputFile << record.number << " " << record.out << " " << record.in << " " << record.time << endl;
    }

    inputFile.close();
    outputFile.close();

    cout << "���������� � ��������� ���� ���������" << endl;
}

void PrintAllRecords(const char* binaryFileName) {
    ifstream inputFile(binaryFileName, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "������ �������� ��������� �����" << endl;
        return;
    }

    Railway record;
    while (inputFile.read(reinterpret_cast<char*>(&record), sizeof(Railway))) {
        cout << "����� ������: " << record.number << ", ����� �����������: " << record.out << ", ����� ����������: " << record.in << ", �����: " << record.time << endl;
    }

    inputFile.close();
}

void AccessRecordByIndex(const char* binaryFileName, int index) {
    ifstream inputFile(binaryFileName, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "������ �������� ��������� �����" << endl;
        return;
    }

    Railway record;
    //������� seekg ������������ ��� ����������� ��������� ������ � ����� �� ��������� ������.
    //��������� ������������ �� �������, ��������������� ����������� �� ������ ��������� Railway. ��� ��������� ��� ������� � ������ ������ � �����.
    inputFile.seekg(index * sizeof(Railway));

    if (inputFile.read(reinterpret_cast<char*>(&record), sizeof(Railway))) {
        cout << "����� ������: " << record.number << ", ����� �����������: " << record.out << ", ����� ����������: " << record.in << ", �����: " << record.time << endl;
    }
    else {
        cout << "������ � ��������� ������� �� �������" << endl;
    }

    inputFile.close();
}

void DeleteRecordByName(const char* binaryFileName, const char* outToDelete) {
    ifstream inputFile(binaryFileName, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "������ �������� ��������� �����" << endl;
        return;
    }
    ofstream tempFile("temp.dat", ios::binary);
    if (!tempFile.is_open()) {
        cerr << "������ �������� ���������� �����" << endl;
        return;
    }

    Railway record;
    bool recordFound = false;
    while (inputFile.read(reinterpret_cast<char*>(&record), sizeof(Railway))) {
        if (strcmp(record.number, outToDelete) == 0) {
            recordFound = true;
        }
        else {
            tempFile.write(reinterpret_cast<const char*>(&record), sizeof(Railway)); //���� ����� �� ���������, ������ ������������ �� ��������� ���� tempFile.
        }
    }

    inputFile.close();
    tempFile.close();

    if (recordFound) {
        remove(binaryFileName); //�������� �������� ���� ��������� � ������� remove � ��������� ���� ����������������� � �������� ���
        rename("temp.dat", binaryFileName);
        cout << "������ � ������ '" << outToDelete << "' �������" << endl;
    }
    else {
        remove("temp.dat");
        cout << "������ � ������ '" << outToDelete << "' �� �������" << endl;
    }
}

void ListRailsByIn(const char* binaryFileName, const char* in) {
    ifstream inputFile(binaryFileName, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "������ �������� ��������� �����" << endl;
        return;
    }

    Railway record;
    bool found = false;
    while (inputFile.read(reinterpret_cast<char*>(&record), sizeof(Railway))) {
        if (strcmp(record.in, in) == 0) {
            cout << "����� ������: " << record.number << ", ����� �����������: " << record.out << ", ����� ����������: " << record.in << ", �����: " << record.time << endl;
            found = true;
        }
    }

    inputFile.close();
    if (!found) {
        cout << "�������, �������������� � ��������� �����, �� �������" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    const char* binaryFileName = "Railway.dat";
    char textFileName[100]; // ����� ��� �������� ����� ���������� �����
    cout << "������� ��� ���������� �����: ";
    cin >> textFileName;
    int choice;
    while (true) {
        cout << "�������� ��������:" << endl;
        cout << "1. ������������� ��������� ���� � ��������" << endl;
        cout << "2. ��������� �������� ���� � ���������" << endl;
        cout << "3. ������� ��� ������ �� ��������� �����" << endl;
        cout << "4. ������ � ������ �� ������" << endl;
        cout << "5. ������� �������� �� ���������� ������" << endl;
        cout << "6. ������������ ������� �� �������, �������������� � ��������� ����� ����������" << endl;
        cout << "7. �����" << endl;
        cout << "������� ����� ��������: ";
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
            cout << "������� ����� ������: ";
            cin >> index;
            AccessRecordByIndex(binaryFileName, index);
            break;
        case 5:
            char outToDelete[50];
            cout << "������� ����� ������ ��� ��������: ";
            cin.ignore(); // ������� ������ ����� ����� ������� ������
            cin.getline(outToDelete, sizeof(outToDelete));
            DeleteRecordByName(binaryFileName, outToDelete);
            break;
        case 6:
            char in[3];
            cout << "������� ����� (5 ����): ";
            cin >> in;
            ListRailsByIn(binaryFileName, in);
            break;
        case 7:
            return 0;
        default:
            cout << "�������� �����. ����������, �������� �������� �� ������." << endl;
            break;
        }
        cout << endl;
    }
    return 0;
}