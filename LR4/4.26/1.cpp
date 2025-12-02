#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

using namespace std;

// Базовый класс
class Vehicle {
public:
    string name;
    Vehicle(string n) : name(n) {}
    virtual void info() {
        cout << "Vehicle: " << name << endl;
    }
};

// Производные классы
class Bicycle : public Vehicle {
public:
    Bicycle(string n) : Vehicle(n) {}
    void info() override {
        cout << "Bicycle: " << name << endl;
    }
};

class Car : public Vehicle {
public:
    Car(string n) : Vehicle(n) {}
    void info() override {
        cout << "Car: " << name << endl;
    }
};

class Truck : public Vehicle {
public:
    Truck(string n) : Vehicle(n) {}
    void info() override {
        cout << "Truck: " << name << endl;
    }
};

// Шаблонный класс для массива указателей
template<class T>
class PointerArray {
    vector<T*> arr;
public:
    // Перегруженный оператор []
    T*& operator[](int index) {
        if (index < 0 || index >= arr.size()) {
            throw domain_error("Invalid index");
        }
        return arr[index];
    }
    
    // Добавление объекта в массив
    void add(T* obj) {
        arr.push_back(obj);
    }
    
    // Получение размера массива
    int size() {
        return arr.size();
    }
};

// Функция с domain_error
void checkSpeed(int speed) {
    if (speed > 200) {
        throw domain_error("Speed too high!");
    }
    cout << "Speed OK: " << speed << " km/h" << endl;
}

int main() {
    // Создаем массив указателей
    PointerArray<Vehicle> transport;
    
    // Добавляем объекты
    transport.add(new Bicycle("Bicycle"));
    transport.add(new Car("BMW"));
    transport.add(new Truck("Volvo"));
    
    // Работа с оператором []
    cout << "=== Vehicle Information ===" << endl;
    for (int i = 0; i < transport.size(); i++) {
        transport[i]->info();
    }
    
    // Обработка исключений
    cout << "\n=== Exception Testing ===" << endl;
    
    try {
        checkSpeed(180);  // Нормальная скорость
        checkSpeed(250);  // Вызываем исключение
    } catch (const domain_error& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    try {
        transport[5]->info();  // Ошибка с неверным индексом
    } catch (const domain_error& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    return 0;
}
