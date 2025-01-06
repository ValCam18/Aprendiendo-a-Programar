#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

struct Book {
    string title;
    string author;
    string genre;
    string year;
    string ISBN;
    string keywords;
    string qualification;
    string link;
};

void addBook(const string &inventory, const Book &bookdetails);
bool searchBook(const string &inventory, const string &title, Book &foundBook);

int main() {

    int choice;
    Book bookdetails, foundBook;
    string inventory = "inventory.txt";
    string searchTitle;
    
    do {

        cout << "----Virtual Library----" << endl;
        cout << "1. Search for a book" << endl;
        cout << "2. Add a book" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        
        cin >> choice;
        cin.ignore();

        if(cin.fail()) {
            cout << "Invalid entry." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice){
            case 1: 
                cout << "Enter the title of the book to search: ";
                getline(cin, searchTitle);
                if (searchBook(inventory, searchTitle, foundBook)){
                    cout << "Book found." << endl;
                    cout << "Title: " << foundBook.title << endl;
                    cout << "Author: " << foundBook.author << endl;
                    cout << "Genre: " << foundBook.genre << endl;
                    cout << "Year: " << foundBook.year << endl;
                    cout << "ISBN: " << foundBook.ISBN << endl;
                    cout << "Keywords: " << foundBook.keywords << endl;
                    cout << "Qualification: " << foundBook.qualification << endl;
                    cout << "Link: " << foundBook.link << endl;
                    cout << "-----------------------------------" << endl;
                } else {
                    cout << "Book not found." << endl;
                }
                cout << "-----------------------------------" << endl;
                break;
            case 2: 
                cout << "Enter the title of the book: ";
                getline(cin, bookdetails.title);
                cout << "Enter the author of the book: ";
                getline(cin, bookdetails.author);
                cout << "Enter the genre of the book: ";
                getline(cin, bookdetails.genre);
                cout << "Enter the year of the book: ";
                getline(cin, bookdetails.year);
                cout << "Enter the ISBN of the book: ";
                getline(cin, bookdetails.ISBN);
                cout << "Enter the keywords of the book: ";
                getline(cin, bookdetails.keywords);
                cout << "Enter the qualification of the book: ";
                getline(cin, bookdetails.qualification);
                cout << "Enter the link of the book: ";
                getline(cin, bookdetails.link);
                addBook(inventory, bookdetails);
                cout << "-----------------------------------" << endl;
                break;
            case 3:
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
    } while (choice != 3);
    
return 0;
}

void addBook(const string &inventory, const Book &bookdetails){
    
    try{
       ofstream file(inventory, ios::app);
       if (file.is_open()){
       file << "Title: " << bookdetails.title << endl;
       file << "Author: " << bookdetails.author << endl;
       file << "Genre: " << bookdetails.genre << endl;
       file << "Year: " << bookdetails.year << endl;
       file << "ISBN: " << bookdetails.ISBN << endl;
       file << "Keywords: " << bookdetails.keywords << endl;
       file << "Qualification: " << bookdetails.qualification << endl;
       file << "Link: " << bookdetails.link << endl << endl;
       file.close();
       cout << "Book added successfully." << endl;
       } else {
       throw runtime_error("Error: Unable to open file.");
       }
    } catch(const exception& e){
       cerr << "Error: " << e.what() << endl;
    }
}

bool searchBook(const string &inventory, const string &title, Book &foundBook) {
    ifstream file(inventory);
    if (!file) {
        cerr << "Error: Unable to open file.\n";
        return false;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.find("Title: ") == 0 && line.substr(7) == title) { // Busca el título
            found = true;
            foundBook.title = title;
            // Extrae el resto de los campos
            while (getline(file, line) && !line.empty()) {
                if (line.find("Author: ") == 0)
                    foundBook.author = line.substr(8);
                else if (line.find("Genre: ") == 0)
                    foundBook.genre = line.substr(7);
                else if (line.find("Year: ") == 0)
                    foundBook.year = line.substr(6);
                else if (line.find("ISBN: ") == 0)
                    foundBook.ISBN = line.substr(6);
                else if (line.find("Keywords: ") == 0)
                    foundBook.keywords = line.substr(10);
                else if (line.find("Qualification: ") == 0)
                    foundBook.qualification = line.substr(14);
                else if (line.find("Link: ") == 0)
                    foundBook.link = line.substr(6);
            }
            break;
        }
    }

    file.close();
    return found;
}
