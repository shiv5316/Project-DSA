#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <list>

using namespace std;

struct Book {
    string title;
    string author;
    string isbn;
    bool isAvailable;

    Book(string bookTitle, string bookAuthor, string bookIsbn) : title(bookTitle), author(bookAuthor), isbn(bookIsbn), isAvailable(true) {}
};

class Library {
private:
    list<Book> bookList; // Linked list for maintaining the list of books
    queue<string> waitlist; // Queue for managing the waitlist for borrowed books

    // Function to find a book by ISBN
    list<Book>::iterator findBookByIsbn(const string& isbn) {
        return find_if(bookList.begin(), bookList.end(), [&isbn](const Book& book) {
            return book.isbn == isbn;
        });
    }

    // Function to check if a book is available
    bool isBookAvailable(const string& isbn) {
        auto it = findBookByIsbn(isbn);
        return it != bookList.end() && it->isAvailable;
    }

public:
    // Add a book to the library
    void addBook(const string& title, const string& author, const string& isbn) {
        Book newBook(title, author, isbn);
        bookList.push_back(newBook);
    }

    // Remove a book from the library
    void removeBook(const string& isbn) {
        auto it = findBookByIsbn(isbn);
        if (it != bookList.end()) {
            bookList.erase(it);
        } else {
            cout << "Book not found." << endl;
        }
    }

    // Display all books in the library
    void displayBooks() {
        for (const auto& book : bookList) {
            cout << "Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.isbn << ", Availability: " << (book.isAvailable ? "Available" : "Not Available") << endl;
        }
    }

    // Search for a book by title
    void searchBookByTitle(const string& title) {
        for (const auto& book : bookList) {
            if (book.title == title) {
                cout << "Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.isbn << ", Availability: " << (book.isAvailable ? "Available" : "Not Available") << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    // Search for a book by author
    void searchBookByAuthor(const string& author) {
        for (const auto& book : bookList) {
            if (book.author == author) {
                cout << "Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.isbn << ", Availability: " << (book.isAvailable ? "Available" : "Not Available") << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    // Search for a book by ISBN
    void searchBookByIsbn(const string& isbn) {
        auto it = findBookByIsbn(isbn);
        if (it != bookList.end()) {
            cout << "Title: " << it->title << ", Author: " << it->author << ", ISBN: " << it->isbn << ", Availability: " << (it->isAvailable ? "Available" : "Not Available") << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }

    // Borrow a book
    void borrowBook(const string& isbn, const string& borrower) {
        auto it = findBookByIsbn(isbn);
        if (it != bookList.end() && it->isAvailable) {
            it->isAvailable = false;
            cout << "Book borrowed by " << borrower << "." << endl;
        } else {
            waitlist.push(borrower);
            cout << "Book is not available. You have been added to the waitlist." << endl;
        }
    }

    // Return a book
    void returnBook(const string& isbn) {
        auto it = findBookByIsbn(isbn);
        if (it != bookList.end() && !it->isAvailable) {
            it->isAvailable = true;
            if (!waitlist.empty()) {
                string nextBorrower = waitlist.front();
                waitlist.pop();
                it->isAvailable = false;
                cout << "Book returned. Next borrower is " << nextBorrower << "." << endl;
            } else {
                cout << "Book returned." << endl;
            }
        } else {
            cout << "Book is already available or not found." << endl;
        }
    }

    // Sort books by title
    void sortBooksByTitle() {
        bookList.sort([](const Book& a, const Book& b) { return a.title < b.title; });
    }

    // Sort books by author
    void sortBooksByAuthor() {
        bookList.sort([](const Book& a, const Book& b) { return a.author < b.author; });
    }

    // Display waitlist
    void displayWaitlist() {
        cout << "Waitlist:" << endl;
        queue<string> temp = waitlist;
        while (!temp.empty()) {
            cout << temp.front() << endl;
            temp.pop();
        }
    }
};

int main() {
    Library lib;
    int choice;
    string title, author, isbn, borrower;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Display Books\n";
        cout << "4. Search Book by Title\n";
        cout << "5. Search Book by Author\n";
        cout << "6. Search Book by ISBN\n";
        cout << "7. Borrow Book\n";
        cout << "8. Return Book\n";
        cout << "9. Sort Books by Title\n";
        cout << "10. Sort Books by Author\n";
        cout << "11. Display Waitlist\n";
        cout << "12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                cout << "Enter book ISBN: ";
                getline(cin, isbn);
                lib.addBook(title, author, isbn);
                break;
            case 2:
                cout << "Enter book ISBN: ";
                cin >> isbn;
                lib.removeBook(isbn);
                break;
            case 3:
                lib.displayBooks();
                break;
            case 4:
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                lib.searchBookByTitle(title);
                break;
            case 5:
                cout << "Enter book author: ";
                cin.ignore();
                getline(cin, author);
                lib.searchBookByAuthor(author);
                break;
            case 6:
                cout << "Enter book ISBN: ";
                cin >> isbn;
                lib.searchBookByIsbn(isbn);
                break;
            case 7:
                cout << "Enter book ISBN: ";
                cin >> isbn;
                cout << "Enter borrower name: ";
                cin.ignore();
                getline(cin, borrower);
                lib.borrowBook(isbn, borrower);
                break;
            case 8:
                cout << "Enter book ISBN: ";
                cin >> isbn;
                lib.returnBook(isbn);
                break;
            case 9:
                lib.sortBooksByTitle();
                break;
            case 10:
                lib.sortBooksByAuthor();
                break;
            case 11:
                lib.displayWaitlist();
                break;
            case 12:
                cout << "Exiting system." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 12);

    return 0;
}
