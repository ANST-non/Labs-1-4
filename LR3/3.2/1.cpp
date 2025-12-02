#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <ctime>

using namespace std;

// Предварительное объявление
class Base;
class Derived;

// Фабричные функции
unique_ptr<Base> createBase();
unique_ptr<Base> createDerived();

// Базовый класс
class Base {
protected:
    Base() = default;
    Base(const Base&) = default;
    
    // Фабричные функции
    friend unique_ptr<Base> createBase();
    friend unique_ptr<Base> createDerived();

public:
    virtual ~Base() = default;
    
    virtual void showType() const {
        cout << "This is an object of type Base" << endl;
    }
    
    virtual int calculate() const {
        return 1;
    }
    
    virtual unique_ptr<Base> clone() const {
        return unique_ptr<Base>(new Base(*this));
    }
};

// Производный класс
class Derived : public Base {
protected:
    Derived() = default;
    Derived(const Derived&) = default;
    
    // Фабричные функции
    friend unique_ptr<Base> createDerived();

public:
    void showType() const override {
        cout << "This is an object of type Derived" << endl;
    }
    
    int calculate() const override {
        return 2;
    }
    
    unique_ptr<Base> clone() const override {
        return unique_ptr<Base>(new Derived(*this));
    }
};

// Реализация фабричных функций
unique_ptr<Base> createBase() {
    return unique_ptr<Base>(new Base());
}

unique_ptr<Base> createDerived() {
    return unique_ptr<Base>(new Derived());
}

// Хранилище объектов
vector<unique_ptr<Base>> storage;

// Функция для добавления объектов в хранилище
void add(unique_ptr<Base> obj) {
    storage.push_back(move(obj));
}

int main() {
    mt19937 gen(time(nullptr));
    uniform_int_distribution<int> dist(1, 10);
    
    cout << "Creating objects:" << endl;
    cout << "==================" << endl;
    
    for (int i = 0; i < 5; ++i) {
        int randomValue = dist(gen);
        unique_ptr<Base> newObj;
        
        if (randomValue % 2 == 0) {
            newObj = createBase();
            cout << "Created Base (random number: " << randomValue << ")" << endl;
        } else {
            newObj = createDerived();
            cout << "Created Derived (random number: " << randomValue << ")" << endl;
        }
        
        add(newObj->clone());
    }
    
    cout << "\nDemonstration of polymorphic behaviour:" << endl;
    cout << "====================================" << endl;
    
    for (size_t i = 0; i < storage.size(); ++i) {
        cout << "Object " << i + 1 << ":" << endl;
        storage[i]->showType();
        cout << "Result calculate(): " << storage[i]->calculate() << endl;
        cout << "------------------------" << endl;
    }
    
    cout << "Freeing up resources..." << endl;
    storage.clear();
    
    return 0;
}
