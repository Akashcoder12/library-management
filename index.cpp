#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book {
public:
    int bookID;
    string title;
    string author;

    void input() {
        cout << "Enter Book ID: ";
        cin >> bookID;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Book Author: ";
        getline(cin, author);
    }

    void display() {
        cout << "\nBook ID: " << bookID
             << "\nTitle: " << title
             << "\nAuthor: " << author << "\n";
    }
};

void addBook() {
    Book b;
    ofstream file("library.txt", ios::app | ios::binary);
    b.input();
    file.write((char*)&b, sizeof(b));
    file.close();
    cout << "Book added successfully!\n";
}

void displayBooks() {
    Book b;
    ifstream file("library.txt", ios::binary);
    while (file.read((char*)&b, sizeof(b))) {
        b.display();
    }
    file.close();
}

void searchBook(int id) {
    Book b;
    bool found = false;
    ifstream file("library.txt", ios::binary);
    while (file.read((char*)&b, sizeof(b))) {
        if (b.bookID == id) {
            cout << "Book found:\n";
            b.display();
            found = true;
            break;
        }
    }
    file.close();
    if (!found) cout << "Book not found.\n";
}

void deleteBook(int id) {
    Book b;
    ifstream file("library.txt", ios::binary);
    ofstream temp("temp.txt", ios::binary);
    bool found = false;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.bookID == id) {
            found = true;
            continue; // skip this book
        }
        temp.write((char*)&b, sizeof(b));
    }

    file.close();
    temp.close();
    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (found)
        cout << "Book deleted successfully.\n";
    else
        cout << "Book ID not found.\n";
}

int main() {
    int choice, id;

    do {
        cout << "\n----- Library Management System -----\n";
        cout << "1. Add Book\n2. Display All Books\n3. Search Book\n4. Delete Book\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBook();
            break;
        case 2:
            displayBooks();
            break;
        case 3:
            cout << "Enter Book ID to search: ";
            cin >> id;
            searchBook(id);
            break;
        case 4:
            cout << "Enter Book ID to delete: ";
            cin >> id;
            deleteBook(id);
            break;
        case 5:
            cout << "Exiting the program...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
