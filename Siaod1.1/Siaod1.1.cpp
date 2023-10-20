#include <chrono>
#include <random>
#include <vector>
#include <iostream>
#include <bitset>
using namespace std;


bitset<16> toBinary16(int value) {
    return bitset<16>(value);
}
bitset<8> toBinary8(int value) {
    return bitset<8>(value);
}

struct MyStruct
{
public:
    int value;
    int result;
    int mask;
    int n;
    int i;
    void task1();
    void task2();
    void task3();
    void task4();
    void task5();
    void task6();
};


int main() {
    setlocale(LC_ALL, "Russian");
    int task;
    MyStruct obj;

    cout << "Choose task 1 to 6: ";
    cin >> task;

    switch (task)
    {
    case 1:
        obj.task1();
        break;
    case 2:
        obj.task2();
        break;
    case 3:
        obj.task3();
        break;
    case 4:
        obj.task4();
        break;
    case 5:
        obj.task5();
        break;
    case 6:
        obj.task6();
        break;
    }
    return 0;
}

void MyStruct::task1() {
    value = 0xA111;
    mask = (1 << 4) & (1 << 5) & (1 << 7) & (1 << 8);
    //mask = 0xF111;
    result = value | mask;   // ѕрименение поразр€дной операции »Ћ» дл€ установки битов в значение 1
    cout << "Value: " << value << "\nBinary: " << toBinary16(value) << endl;
    cout << "Result: " << result << "\nBinary: " << toBinary16(mask) << endl;
    //mask = ~(1 << 4) & ~(1 << 5) & ~(1 << 7) & ~(1 << 8);
}

void MyStruct::task2() {
    cin >> value;
    mask = ~(1 << 4) & ~(1 << 6); // ћаска, котора€ обнул€ет п€тый и седьмой справа биты
    result = value & mask;
    cout << "Value: " << value << "\nBinary: " << toBinary8(value) << endl;
    cout << "Result: " << result << "\nBinary: " << toBinary8(result) << endl;
}

void MyStruct::task3() {
    cin >> value;
    result = value << 5;
    cout << "Value: " << value << "\nBinary: " << toBinary16(value) << endl;
    cout << "Result: " << result << "\nBinary: " << toBinary16(result) << endl;
}

void MyStruct::task4() {
    cin >> value;
    result = value >> 5;
    cout << "Value: " << value << "\nBinary: " << toBinary16(value) << endl;
    cout << "Result: " << result << "\nBinary: " << toBinary16(result) << endl;
}

void MyStruct::task5() {
    cin >> value;
    cout << "Enter the bit number to reset (from 0 to 31): ";
    cin >> n;

    // —оздание маски с установленным битом n
    mask = 1;
    mask = 1 << n;
    // ќбнуление n-ого бита числа с использованием маски
    value = value & (~mask);
    cout << "Result: " << value << "\nBinary: " << toBinary16(value) << endl;
    cout << "Mask: " << mask << "\nBinary: " << toBinary16(mask) << endl;
}

void MyStruct::task6() {
    int size = 9999999, num_of_values;
    cout << "Array size: ";
    cin >> num_of_values;

    vector<int> array_of_values(num_of_values);
    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<int> distribution(1000000, 9999999);
    for (int i = 0; i < num_of_values; i++) {
        array_of_values[i] = distribution(generator);  // јвтоматическое заполнение массива 7-значными случайными числами
    }
    /*   for (int i = 0; i < num_of_values; i++) {        // дл€ ручного ввода
           cout << "Array element " << i << ": ";
           cin >> array_of_values[i];
           if (array_of_values[i] > size) {
               size = array_of_values[i];
           }
       }     */

    vector<int> bit_array(size + 1, 0); //заполн€ем массив нул€ми
    for (int i = 0; i < num_of_values; i++) {
        bit_array[array_of_values[i]] = 1;
    }

    cout << "Sorted array: ";
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i <= size; i++) { // устанавливаем 1 в соответстующем индексе
        if (bit_array[i] == 1) {
            cout << i << " ";
        }
    }
    auto end = chrono::high_resolution_clock::now();  // «асекаем врем€ после сортировки
    chrono::duration<double> duration = end - start;  // ¬ычисл€ем продолжительность выполнени€

    cout << "\nTime: " << duration.count() << " sec" << endl;
}