#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Типы книг
enum BookType {
    ART,    
    TECHNICAL  
};

class Book {
private:
    string author;
    string title;
    BookType type;

public:
    Book(string a, string t, BookType ty) : author(a), title(t), type(ty) {
        if (a.empty() || t.empty()) {
            cout << "Error" << endl;
            exit(1);
        }
    }

    // Геттеры
    string getAuthor() const { return author; }
    string getTitle() const { return title; }
    BookType getType() const { return type; }
};

// Функция для вывода статистики с использованием switch
void printStatsWithSwitch(const vector<Book>& library) {
    int artCount = 0;
    int technicalCount = 0;

    for (const auto& book : library) {
        switch (book.getType()) {
            case ART:
                artCount++;
                break;
            case TECHNICAL:
                technicalCount++;
                break;
        }
    }

    cout << "\n Stat (with switch):" << endl;
    cout << "Art Books: " << artCount << endl;
    cout << "Technical Books: " << technicalCount << endl;
}

// Функция для вывода статистики без использования switch
void printStatsWithoutSwitch(const vector<Book>& library) {
    int artCount = 0;
    int technicalCount = 0;

    for (const auto& book : library) {
        if (book.getType() == ART) {
            artCount++;
        } else {
            technicalCount++;
        }
    }

    cout << "\nStat (no with switch):" << endl;
    cout << "Art Books: " << artCount << endl;
    cout << "Technical Books: " << technicalCount << endl;
}

int main() {
    // Создаем библиотеку
    vector<Book> library;

    // Наполняем библиотеку книгами
    library.push_back(Book("Turgenev", "Fathers and sons", ART));
    library.push_back(Book("Anton Chekhov", "Chamber №6", ART));
    library.push_back(Book("Whip", "The Art of Programming", TECHNICAL));
    library.push_back(Book("Orwell", "1984", ART));
    library.push_back(Book("Tanenbaum", "Modern Operating Systems", TECHNICAL));

    // Выводим все книги
    cout << "Books" << endl;
    for (size_t i = 0; i < library.size(); i++) {
        string typeStr = (library[i].getType() == ART) ? "Art" : "Technical";
        cout << i+1 << ". " << library[i].getAuthor() << " - \"" 
             << library[i].getTitle() << "\" (" << typeStr << ")" << endl;
    }

    // Выводим статистику двумя способами
    printStatsWithSwitch(library);
    printStatsWithoutSwitch(library);

    // Память автоматически освобождается благодаря vector
    return 0;
}


