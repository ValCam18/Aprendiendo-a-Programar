#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
using namespace std;

struct Book
{
    string title;
    string author;
    string genre;
    int year;
    string ISBN;
    string keywords;
    string qualification;
    string link;
};

void addBook(const string &inventory, const Book &bookdetails);
void searchBook(const string &inventory, const string &searchTerm, vector<Book> &searchResult);
bool containsSearchTerm(Book book, string searchTerm);

int main()
{

    int choice;
    Book bookdetails, foundBook;
    string inventory = "inventory.txt";
    string searchTerm;
    vector<Book> searchResult;

    do
    {

        cout << "----Virtual Library----" << endl;
        cout << "1. Search for a book" << endl;
        cout << "2. Add a book" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore();

        if (cin.fail())
        {
            cout << "Invalid entry." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            cout << "Enter the term to search: ";
            getline(cin, searchTerm);

            searchResult = vector<Book>(); // Cleaning searchResult vector

            searchBook(inventory, searchTerm, searchResult);
            if (searchResult.size() > 0)
            {
                for (Book book : searchResult)
                {
                    cout << "Title: " << book.title << endl;
                    cout << "Author: " << book.author << endl;
                    cout << "Genre: " << book.genre << endl;
                    cout << "Year: " << book.year << endl;
                    cout << "ISBN: " << book.ISBN << endl;
                    cout << "Keywords: " << book.keywords << endl;
                    cout << "Qualification: " << book.qualification << endl;
                    cout << "Link: " << book.link << endl;
                    cout << "-----------------------------------" << endl;
                }
            }
            cout << "Books found: " << searchResult.size() << endl;
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
            cin >> bookdetails.year;
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

void addBook(const string &inventory, const Book &bookdetails)
{

    try
    {
        ofstream file(inventory, ios::app);
        if (file.is_open())
        {
            file << "Title: " << bookdetails.title << endl;
            file << "Author: " << bookdetails.author << endl;
            file << "Genre: " << bookdetails.genre << endl;
            file << "Year: " << bookdetails.year << endl;
            file << "ISBN: " << bookdetails.ISBN << endl;
            file << "Keywords: " << bookdetails.keywords << endl;
            file << "Qualification: " << bookdetails.qualification << endl;
            file << "Link: " << bookdetails.link << endl
                 << endl;
            file.close();
            cout << "Book added successfully." << endl;
        }
        else
        {
            throw runtime_error("Error: Unable to open file.");
        }
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

void searchBook(const string &inventory, const string &searchTerm, vector<Book> &searchResult)
{
    ifstream file(inventory);
    if (!file)
    {
        cerr << "Error: Unable to open file.\n";
        return;
    }

    string line;
    Book book;

    string title = "Title: ";
    string author = "Author: ";
    string genre = "Genre: ";
    string year = "Year: ";
    string ISBN = "ISBN: ";
    string keywords = "Keywords: ";
    string qualification = "Qualification: ";
    string link = "Link: ";

    while (getline(file, line))
    {
        if (line.find(title) == 0)
        {
            book.title = line.substr(title.size());
        }
        else if (line.find(author) == 0)
            book.author = line.substr(author.size());
        else if (line.find(genre) == 0)
            book.genre = line.substr(genre.size());
        else if (line.find(year) == 0)
        {
            string y = line.substr(year.size());
            book.year = stoi(y);
        }
        else if (line.find(ISBN) == 0)
            book.ISBN = line.substr(ISBN.size());
        else if (line.find(keywords) == 0)
            book.keywords = line.substr(keywords.size());
        else if (line.find(qualification) == 0)
            book.qualification = line.substr(qualification.size());
        else if (line.find(link) == 0)
            book.link = line.substr(link.size());
        else if (line.empty() && containsSearchTerm(book, searchTerm))
        {
            searchResult.push_back(book);
        }
    }
    if (containsSearchTerm(book, searchTerm))
    {
        if (searchResult.size() == 0)
        {
            searchResult.push_back(book);
        }
        else
        {
            Book lastElement = searchResult.back();
            if (lastElement.ISBN != book.ISBN)
            {
                searchResult.push_back(book);
            }
        }
    }
    file.close();
}

bool containsSearchTerm(Book book, string searchTerm)
{
    if (book.title.find(searchTerm) != string::npos)
    {
        return true;
    }
    if (book.author.find(searchTerm) != string::npos)
    {
        return true;
    }
    if (book.genre.find(searchTerm) != string::npos)
    {
        return true;
    }
    string y = to_string(book.year);
    if (y.find(searchTerm) != string::npos)
    {
        return true;
    }
    if (book.ISBN.find(searchTerm) != string::npos)
    {
        return true;
    }
    if (book.keywords.find(searchTerm) != string::npos)
    {
        return true;
    }
    if (book.qualification.find(searchTerm) != string::npos)
    {
        return true;
    }
    if (book.link.find(searchTerm) != string::npos)
    {
        return true;
    }
    return false;
}