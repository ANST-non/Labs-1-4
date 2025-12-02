#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// Базовый класс - Деталь
class Detail {
protected:
    string name;
    double weight;
    
    Detail(const string& n, double w) : name(n), weight(w) {}

public:
    virtual ~Detail() = default;
    
    virtual void showInfo() const {
        cout << "Detail: " << name << ", weight: " << weight << " kilo" << endl;
    }
    
    // Шаблонная функция для создания объектов
    template<typename T, typename... Args>
    friend shared_ptr<T> createObject(Args&&... args);
};

// Производный класс - Сборка
class Assembly : public Detail {
protected:
    int componentCount;
    
    Assembly(const string& n, double w, int count) 
        : Detail(n, w), componentCount(count) {}

public:
    void showInfo() const override {
        cout << "Assembly: " << name << ", weight: " << weight 
                  << " kilo, components: " << componentCount << endl;
    }
    
    // Доступ к шаблонной функции
    template<typename T, typename... Args>
    friend shared_ptr<T> createObject(Args&&... args);
};

// Шаблонная функция для создания объектов
template<typename T, typename... Args>
shared_ptr<T> createObject(Args&&... args) {
    // Используем protected конструкторы через дружественный доступ
    return shared_ptr<T>(new T(forward<Args>(args)...));
}

int main() {
    vector<shared_ptr<Detail>> storage;
    
    // Создаем объекты через функцию и помещаем в вектор
    storage.push_back(createObject<Detail>("Nut", 0.05));
    storage.push_back(createObject<Detail>("Bolt", 0.05));
    storage.push_back(createObject<Assembly>("Corps", 80.0, 25));
    storage.push_back(createObject<Assembly>("Engine ULTRA", 150.0, 50));
    
    // Выводим информацию о всех объектах
    cout << "Storage Contents:" << endl;
    for (const auto& item : storage) {
        item->showInfo();
    }
    
    return 0;
}
