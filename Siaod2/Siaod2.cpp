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
    void bitSort(vector<int>& arr);
};


int main() {
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
    mask = 0xF111;
    result = value | mask;   // Применение поразрядной операции ИЛИ для установки битов в значение 1
    cout << "Value: " << value << "\nBinary: " << toBinary16(value) << endl;
    cout << "Result: " << result << "\nBinary: " << toBinary16(mask) << endl;
}

void MyStruct::task2() {
    cin >> value;
    mask = ~(1 << 4) & ~(1 << 6); // Маска, которая обнуляет пятый и седьмой справа биты
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

    // Создание маски с установленным битом n
    mask = 1;
    mask = 1 << n;
    // Обнуление n-ого бита числа с использованием маски
    value = value & (~mask);
    cout << "Result: " << value << "\nBinary: " << toBinary16(value) << endl;
    cout << "Mask: " << mask << "\nBinary: " << toBinary16(mask) << endl;
}

void MyStruct::task6() {
    n;
    cout << "Array size: ";
    cin >> n;

    vector<int> arr(n);
    for (i = 0; i < n; i++) {
        cout << "Array element " << i << ": ";
        cin >> arr[i];
    }

    cout << "Array: ";
    for (i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    cout << "\nSorted array: ";
    bitSort(arr);
}

void MyStruct::bitSort(vector<int>& arr) {
    const int maxNum = 1000000; // Максимальное значение чисел в массиве
    bitset<maxNum> bitSet;

    for (i = 0; i < arr.size(); i++) {
        bitSet.set(arr[i]); // Устанавливаем бит для каждого числа в массиве
    }

    for (i = 0; i < maxNum; i++) {
        if (bitSet.test(i)) {
            cout << i << " "; // Выводим числа в отсортированном порядке
        }
    }
}