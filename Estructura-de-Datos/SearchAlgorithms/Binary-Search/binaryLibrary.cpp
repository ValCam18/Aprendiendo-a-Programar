#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;


const string PASSWORD = "admin00";

struct Library{
    string code;
    string title;
    string author;
    string genre;
    string publicationYear;
};

//Todas las funciones
vector<Library> csvData(const string &bookslist);
void showBooks(const vector<Library> &books);
bool adminAccess(string &password);
void addBook(vector<Library> &books);
void editBook(vector<Library> &books);
void deleteBook(vector<Library> &books);
void exportBooksByGenre(const vector<Library>& books, const string& genre);
void binarySearch(const vector<Library>& books, const string& code);
void quicksort(vector<Library>& books, int low, int high);


int main(){
    string filename = "bookslist.csv", password;
    vector<Library> books = csvData(filename);
    quicksort(books, 0, books.size() - 1);
    string value;
    string genre;
    int option;

    do{
        cout << "\n**************Welcome to your library***************" << endl;
        cout << "\n1. Login as a user\n2. Login as an admin\n3. Exit" << endl;
        cout << "\nChoose your option: ";
        cin >> option;
        cin.ignore();

        if(cin.fail()){
            cout << "Fail, try an accepted option" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (option){
        case 1: {
            int optionUsers;
            bool back = true;
            
            while(back){
                cout << "\nUsers menu\n1. Show all books\n2. Search book\n3. Return\nChoose an option: " << endl;
                cin >> optionUsers;
                cin.ignore();

                if(cin.fail()){
                    cout << "Fail, try an accepted option" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                switch (optionUsers){
                case 1:
                    showBooks(books);
                    break;
                case 2:
                    cout << "Enter the book to search: ";
                    cin >> value;
                    binarySearch(books, value);
                    break;    
                case 3:
                    cout << "Returning..." << endl;
                    back = false;
                    system("cls");
                    break;
                default:
                    cout << "Only options from 1 to 3 are accepted" << endl;
                    break;
                }
            }
        }
            break;
        case 2:{
            adminAccess(password);
            int optionAdmin;
            bool back = true;
            
            while(back){
                cout << "\nAdmin menu\n1. Show all books\n2. Search book\n3. Add books\n4. Edit information\n5. Delete information\n6. Export books\n7. Return \nChoose an option: " << endl;
                cin >> optionAdmin;
                cin.ignore();

                if(cin.fail()){
                    cout << "Error al leer los datos" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                switch (optionAdmin){
                case 1:
                    showBooks(books);
                    break;
                case 2:
                    cout << "Enter the book to search: ";
                    cin >> value;
                    binarySearch(books, value);
                    break; 
                    break;
                case 3:
                    addBook(books);
                    break;
                case 4:
                    editBook(books);
                    break;
                case 5:
                    deleteBook(books);
                    break;
                case 6:
                    cout << "Enter the genre to export: ";
                    cin >> genre; 
                    exportBooksByGenre(books, genre);
                    break;    
                case 7:
                    cout << "Returning..." << endl;
                    back = false;
                    system("cls");
                    break;
                default:
                    cout << "Only options from 1 to 3 are accepted" << endl;
                    break;
                }
            }
        }
        break;
        case 3:
            cout << "Goodbye and thank you for reading books :)" << endl;
            break;
        default:
            cout << "Only options from 1 - 3 are accepted" << endl;
            break;
        }
    } while (option != 3);

return 0;
}

vector<Library> csvData(const string &bookslist){
    vector<Library> books;
    ifstream file(bookslist);
    string line;

    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);
        Library book;

        getline(ss, book.code, ',');
        getline(ss, book.title, ',');
        getline(ss, book.author, ',');
        getline(ss, book.genre, ',');
        getline(ss, book.publicationYear, ',');

        books.push_back(book);  
    }
    file.close();
    return books;
}

void showBooks(const vector<Library> &books){
    for(const auto &book : books){
        cout << "\n--------------------------------------------------------------------------------------" 
             << "\nCode's book: " << book.code << "\nTitle: " << book.title 
             << "\n--------------------------------------------------------------------------------------" << endl; 
    }
}

bool adminAccess(string &password){
    cout << "Enter password (or enter 'r' to return): ";
    cin >> password;

    while (password != PASSWORD) { 
        if (password == "R" || password == "r") { 
            cout << "R" << endl; 
            return false;
        } 
        cout << "Incorrect password, please try again (or enter 'r' to cancel): "; 
        cin >> password; 
    }
    return true;
}

void addBook(vector<Library> &books){
    Library newBook;

    cout<<"Enter the code of the book: ";
    cin>>newBook.code;
    cin.ignore();

    //validar si el codigo existe ya

    for(const auto &book : books){
        if(newBook.code == book.code){
            cout<<"The code already exists"<<endl;
            return;
        }
    }
    
    cout<<"Enter the title of the book: ";
    getline(cin, newBook.title);

    cout<<"Enter the author of the book: ";
    getline(cin, newBook.author);

    cout<<"Enter the genre of the book: ";
    getline(cin, newBook.genre);

    cout<<"Enter the publication year of the book: ";
    cin >> newBook.publicationYear;

    books.push_back(newBook);
    cout<<"Book added successfully!"<<endl;

}


void editBook(vector<Library> &books){
    string code;
    bool found = false;
    int size = books.size();
    cout<<"Enter the code of the book you want to edit: ";
    cin>>code;

    for(int i=0; i<size; i++){
        if(books[i].code == code){
            cout<<"Editing book: "<<books[i].title<<endl;
            cout<<"Enter the new title: ";
            cin.ignore();
            getline(cin, books[i].title);

            cout<<"Enter the new author (current: "<<books[i].author<<"): ";
            getline(cin, books[i].author);
            
            cout<<"Enter the new genre (current: "<<books[i].genre<<"): ";
            getline(cin, books[i].genre);

            cout<<"Enter the new publication year (current: "<<books[i].publicationYear<<"): ";
            cin>>books[i].publicationYear;

            found = true;
            break;
        }
    }

    if(!found){
        cout<<"Book with code "<<code<<" not found"<<endl;
    }
}



void deleteBook(vector<Library> &books) {
    string code;
    bool found = false;
    int size = books.size();
    cout << "Enter the code of the book you want to delete: ";
    cin >> code;

    for (int i = 0; i < books.size(); i++) {
        if (books[i].code == code) {  
            found = true;

            string answer;
            cout << "Are you sure you want to delete the book with code " << code << "? (y/n): ";
            cin >> answer;

            if (answer == "y") {  // delete
                books.erase(books.begin() + i);  
                cout << "Book deleted successfully!" << endl;
            } else if (answer == "n") { //no delete
                cout << "Returning..." << endl;
            } else {  
                cout << "Invalid option. Returning..." << endl;
            }
            return;  
        }
    }

    if (!found) {
        cout << "Book with code " << code << " not found." << endl;
    }
}
void quicksort(vector<Library>& books, int low, int high) {
    if (low < high) {
        string pivot = books[high].code;
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (books[j].code <= pivot) {
                ++i;
                swap(books[i], books[j]);
            }
        }
        swap(books[i + 1], books[high]);
        int pivotIndex = i + 1;

        quicksort(books, low, pivotIndex - 1);
        quicksort(books, pivotIndex + 1, high);
    }
}

void binarySearch(const vector<Library>& books, const string& code) {
    int low = 0;
    int high = books.size() - 1;
    bool found = false;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (books[mid].code == code) {
            cout << "Book found:\n";
            cout << "Code: " << books[mid].code << "\n";
            cout << "Title: " << books[mid].title << "\n";
            cout << "Author: " << books[mid].author << "\n";
            cout << "Genre: " << books[mid].genre << "\n";
            cout << "Publication Year: " << books[mid].publicationYear << "\n";
            found = true;
            break;
        } else if (books[mid].code < code) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        cout << "Book with code " << code << " not found.\n";
    }
}

void exportBooksByGenre(const vector<Library>& books, const string& genre) {
    static int fileCount = 1; 
    bool found = false;

    for (const auto& book : books) {
        if (book.genre == genre) {
            stringstream filename;
            filename << "exported-file-" << fileCount++ << ".csv";

            ofstream file(filename.str());

            if (file.is_open()) {
                file << "Code,Title,Author,Genre,PublicationYear\n";
                file << book.code << "," << book.title << "," << book.author << ","
                     << book.genre << "," << book.publicationYear << "\n";
                file.close();
                cout << "Book exported successfully to " << filename.str() << "!\n";
            } else {
                cout << "Error opening file " << filename.str() << " for writing.\n";
            }
            found = true;
        }
    }
    if (!found) {
        cout << "No books found with genre " << genre << ".\n";
    }
}


