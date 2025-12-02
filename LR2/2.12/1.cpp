#include <iostream>
#include <string>

using namespace std;

class Sales {
protected:
    float sales[3]; // Sales for last 3 months

public:
    virtual void getSalesData() {
        cout << "Enter sales for last 3 months: " << endl;
        for (int i = 0; i < 3; i++) {
            cout << "Month " << i + 1 << ": ";
            cin >> sales[i];
        }
        cin.ignore();
    }

    virtual void putSalesData() const {
        cout << "Sales for last 3 months: ";
        for (int i = 0; i < 3; i++) {
            cout << sales[i];
            if (i < 2) cout << ", ";
        }
    }

    virtual ~Sales() {}
};

class Publication {
protected:
    string title;
    float price;
    
public:
    virtual void getdata() {
        cout << "Enter title: ";
        getline(cin, title);
        cout << "Enter price: ";
        cin >> price;
        cin.ignore();
    }
    
    virtual void putdata() const {
        cout << "Title: " << title << endl;
        cout << "Price: " << price << " USD" << endl;
    }
    
    virtual ~Publication() {}
};

class Book : public Publication, public Sales {
private:
    int pages;
    
public:
    void getdata() override {
        Publication::getdata();
        cout << "Enter number of pages: ";
        cin >> pages;
        cin.ignore();
        Sales::getSalesData();
    }
    
    void putdata() const override {
        Publication::putdata();
        cout << "Pages: " << pages << endl;
        Sales::putSalesData();
    }
};

class Type : public Publication, public Sales {
private:
    float time;
    
public:
    void getdata() override {
        Publication::getdata();
        cout << "Enter recording time (minutes): ";
        cin >> time;
        cin.ignore();
        Sales::getSalesData();
    }
    
    void putdata() const override {
        Publication::putdata();
        cout << "Recording time: " << time << " minutes" << endl;
        Sales::putSalesData();
    }
};

int main() {
    Book book;
    Type audio;
    
    cout << "=== Enter Book Data ===" << endl;
    book.getdata();
    
    cout << "\n=== Enter Audio Type Data ===" << endl;
    audio.getdata();
    
    cout << "\n=== Book Information ===" << endl;
    book.putdata();
    
    cout << "\n=== Audio Type Information ===" << endl;
    audio.putdata();
    
    return 0;
}
