#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <cctype>
using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
struct Book
{
    string title;
    string author;
    string genre;
    string year;
    string ISBN;
    string keywords;
    string qualification;
    string link;
};

// Main functions
void showMenu(const string &inventory);
void findBookInCSV(const string &inventory, const string &searchTerm, vector<Book> &searchResult);
void showTopRatedBooks(const string &inventory);
void addWishList(const string &wishList);
void addBookToCSV(const string &inventory, const Book &book);
bool deleteBookFromCSV(const string &inventory, const string &searchTerm);
void showWishlist(const string &wishList);
void removeWishList(const string &wishList, const string &keyword);
// Auxiliary functions
bool containsSearchTerm(Book book, string searchTerm);
bool confirmAction(const string &message);
Book mapLineToBook(const string &line);
string toLowerCase(const string &input);
vector<string> parseCSVline(const string &line);
// Dyes the console with colors
void color(int color);

int main()
{
    string inventory = "inventory.csv"; // Ruta al archivo CSV
    showMenu(inventory);
    return 0;
}

// Main functions
void showMenu(const string &inventory)
{
    string wishlist = "wishlist.csv";

    int choice, adminChoice;
    string input, adminPassword;
    do
    {
        // Mostrar menú de opciones
        color(11); cout << "----- Nomada's Virtual Library -----\n"; color(15);
        cout << "1. Find a book\n";
        cout << "2. Top rated books\n";
        cout << "3. Wishlist\n";
        color(8); cout << "4. Exit\n"; color(15);
        color(11); cout << "Enter your choice: "; color(15);
        getline(cin, input);

        try
        {
            choice = stoi(input);
            adminChoice = stoi(input);
        }
        catch (const exception &)
        {
            color(12); cout << "Invalid input. Please enter a number.\n"; color(15);
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            // Buscar un libro
            string searchTerm;
            color(14); cout << "Enter search term: "; color(15);
            getline(cin, searchTerm);
            vector<Book> searchResult;
            color(8); cout << "------------------------------------" << endl; color(15);
            findBookInCSV(inventory, searchTerm, searchResult);
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
                    color(8); cout << "------------------------------------" << endl; color(15);
                }
            }
            color(14); cout << "Books found: " ; color(15);
            cout << searchResult.size() << endl;
            color(8); cout << "------------------------------------" << endl; color(15);
            break;
        }
        case 2:
            showTopRatedBooks(inventory);
            break;
        case 3:
            addWishList(wishlist);
            break;
        case 4:
            color(5); cout << "Exiting the program.\n"; color(15);
            break;
        case 88:
            color(8); cout << "\n------------------------------------" << endl; color(15);
            color(1); cout << "------- Admin's section ONLY -------" << endl; color(15);
            color(6); cout << "Enter admin's password: "; color(15);
            getline(cin, adminPassword);

            if (adminPassword == "adminpass")
            {
                do
                {
                    color(8); cout << "------------------------------------" << endl; color(15);
                    color(1); cout << "----------- Admin's Menu -----------" << endl; color(15);
                    cout << "1. Add a book to inventory" << endl;
                    cout << "2. Remove a book from inventory" << endl;
                    cout << "3. Show Wishlist" << endl;
                    cout << "4. Remove a book from Wishlist" << endl;
                    color(8); cout << "5. Back to the main menu." << endl; color(15);
                    color(14); cout << "Enter your choice: "; color(15);
                    cin >> adminChoice;
                    cin.ignore();

                    switch (adminChoice)
                    {
                    case 1:
                    {
                        color(8); cout << "------------------------------------" << endl; color(15);
                        // Agregar un libro
                        Book newBook;
                        color(7);
                        cout << "Enter book title: ";
                        getline(cin, newBook.title);
                        cout << "Enter author: ";
                        getline(cin, newBook.author);
                        cout << "Enter genre: ";
                        getline(cin, newBook.genre);
                        cout << "Enter year: ";
                        getline(cin, newBook.year);
                        cout << "Enter ISBN: ";
                        getline(cin, newBook.ISBN);
                        cout << "Enter keywords: ";
                        getline(cin, newBook.keywords);
                        cout << "Enter qualification: ";
                        getline(cin, newBook.qualification);
                        cout << "Enter link: ";
                        getline(cin, newBook.link);
                        color(15);
                        addBookToCSV(inventory, newBook);
                        break;
                    }
                    case 2:
                    {
                        // Eliminar un libro
                        string searchTerm;
                        color(8);
                        cout << "------------------------------------" << endl;
                        cout << "Enter the search term (could be part of any field): ";
                        color(15);
                        getline(cin, searchTerm);

                        deleteBookFromCSV(inventory, searchTerm);
                        break;
                    }
                    case 3:
                        showWishlist(wishlist);
                        break;
                    case 4:
                    {
                        string searchTerm;
                        cout << "Enter the search term (could be part of any field): ";
                        getline(cin, searchTerm);

                        removeWishList(wishlist, searchTerm);
                        break;
                    }
                    case 5:
                        color(7); cout << "-----------------------------------" << endl; color(15);     
                        break;
                    default:
                        color(12); cout << "Invalid choice. Please try again.\n"; color(15);
                        break;
                    }
                } while (adminChoice != 5);
            }
            else
            {
                color(12); cout << "Invalid password. Try again." << endl; color(15);
                color(8); cout << "------------------------------------" << endl; color(15);
            }
            break;
        default:
            color(12); cout << "Invalid choice. Please try again.\n"; color(15);
            break;
        }
    } while (choice != 4);
}

void findBookInCSV(const string &inventory, const string &searchTerm, vector<Book> &searchResult)
{
    ifstream file(inventory);
    if (!file)
    {
        color(12); cerr << "Error: Unable to open file.\n"; color(15);
        return;
    }

    string line;
    Book book;
    string lowerSearchTerm = toLowerCase(searchTerm);

    while (getline(file, line))
    {
        vector<string> fields = parseCSVline(line); // Usamos parseCSVLine aquí también

        // Asignamos los campos del CSV a un libro
        if (fields.size() != 8)
        {
            continue; // Si la línea no tiene los campos correctos, la ignoramos
        }

        book.title = fields[0];
        book.author = fields[1];
        book.genre = fields[2];
        book.year = fields[3];
        book.ISBN = fields[4];
        book.keywords = fields[5];
        book.qualification = fields[6];
        book.link = fields[7];

        if (containsSearchTerm(book, searchTerm))
        {
            searchResult.push_back(book); // Si coincide con el término de búsqueda, lo agregamos a los resultados
        }
    }

    file.close();
}

void showTopRatedBooks(const string &inventory)
{
    ifstream file(inventory);
    if (!file)
    {
        color(12); cerr << "Error: Unable to open file.\n"; color(15);
        return;
    }

    string line;
    Book book;
    vector<string> validQualifications = {"4.6", "4.7", "4.8", "4.9", "5"};
    vector<Book> topRatedBooks;

    while (getline(file, line))
    {
        vector<string> fields = parseCSVline(line);

        if (fields.size() != 8)
        {
            continue;
        }

        book.title = fields[0];
        book.author = fields[1];
        book.genre = fields[2];
        book.year = fields[3];
        book.ISBN = fields[4];
        book.keywords = fields[5];
        book.qualification = fields[6];
        book.link = fields[7];

        if (find(validQualifications.begin(), validQualifications.end(), book.qualification) != validQualifications.end())
        {
            topRatedBooks.push_back(book);
        }
    }

    file.close();

    // Mostrar los libros encontrados
    if (topRatedBooks.empty())
    {
        color(12); cout << "No books found with a qualification higher than 4.5.\n"; color(15);
    }
    else
    {
        color(10); cout << "\n------------- TOP BOOKS ------------\n"; color(15);
        color(8); cout << "------------------------------------" << endl; color(15);
        for (const auto &book : topRatedBooks)
        {
            color(7);
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "Qualification: " << book.qualification << endl;
            color(15);
            color(8); cout << "------------------------------------" << endl; color(15);
        }
        color(14); cout << "Total books found: "; color(15);
        cout << topRatedBooks.size() << endl;
        color(8); cout << "------------------------------------" << endl; color(15);
    }
}

void addWishList(const string &wishList)
{
    color(8); cout << "------------------------------------" << endl; color(15);
    color(14); cout << "You can add a book to your wish list.\n"; color(15);
    Book desiredBook;
    color(7); cout << "Enter book title: "; color(15);
    getline(cin, desiredBook.title);
    color(7); cout << "Enter author: "; color(15);
    getline(cin, desiredBook.author);
    color(7); cout << "Enter genre: "; color(15);
    getline(cin, desiredBook.genre);

    try
    {
        ofstream file(wishList, ios::app);
        if (!file.is_open())
        {
            throw runtime_error("Error: Unable to open wish list file.");
        }

        string bookLine = "\"" + desiredBook.title + "\",\"" +
                          desiredBook.author + "\",\"" +
                          desiredBook.genre + "\"\n";

        file << bookLine;
        color(10); cout << "Book added to your wish list successfully.\n"; color(15);
        color(8); cout << "------------------------------------" << endl; color(15);
        file.close();
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

void addBookToCSV(const string &inventory, const Book &book)
{
    try
    {
        ofstream file(inventory, ios::app); // Abre el archivo en modo 'append'
        if (!file.is_open())
        {
            throw runtime_error("Error: Unable to open file.");
        }

        // Construcción del libro como una línea CSV
        string bookLine = "\"" + book.title + "\","
                                              "\"" +
                          book.author + "\","
                                        "\"" +
                          book.genre + "\","
                                       "\"" +
                          book.year + "\","
                                      "\"" +
                          book.ISBN + "\","
                                      "\"" +
                          book.keywords + "\","
                                          "\"" +
                          book.qualification + "\","
                                               "\"" +
                          book.link + "\"\n";

        file << bookLine; // Agrega la nueva línea al archivo
        color(10); cout << "Book added successfully." << endl; color(15);

        file.close();
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

bool deleteBookFromCSV(const string &inventory, const string &searchTerm)
{
    ifstream file(inventory);
    if (!file)
    {
        cerr << "Error: Unable to open file.\n";
        return false;
    }

    string lowerSearchTerm = toLowerCase(searchTerm);
    vector<string> booksToKeep; // Libros a mantener
    vector<string> booksFound;  // Libros con coincidencia
    string line;

    // Leer todas las líneas en un vector
    while (getline(file, line))
    {
        if (toLowerCase(line).find(lowerSearchTerm) != string::npos)
        {
            booksFound.push_back(line);
        }
        else
        {
            booksToKeep.push_back(line);
        }
    }
    file.close();

    if (booksFound.empty())
    {
        color(12); cout << "No book found with the search term: " << searchTerm << endl; color(15);
        return false;
    }

    // Mostrar los libros encontrados
    color(10); cout << "Found "; color(15);
    cout << booksFound.size() << " book(s):\n";
    for (size_t i = 0; i < booksFound.size(); ++i)
    {
        Book book = mapLineToBook(booksFound[i]);
        color(3); cout << i + 1 << ". ";
        if (book.ISBN != "")
        {
            cout << "ISBN: "; color(15);
            cout << book.ISBN << " | ";
        }
        color(3); cout << "Title: "; color(15);
        cout << book.title;
        color(3); cout << " | Author: "; color(15);
        cout << book.author << endl;
    }

    // Leer selección del usuario
    color(8); cout << "\nEnter the number(s) of the book(s) you want to delete (separated by spaces): "; color(15);
    string userInput;
    getline(cin, userInput);

    vector<int> booksToRemove;
    stringstream ss(userInput);
    string selection;

    while (ss >> selection)
    {
        try
        {
            int index = stoi(selection) - 1;
            if (index >= 0 && index < booksFound.size())
            {
                booksToRemove.push_back(index);
            }
            else
            {
                color(12); cerr << "Invalid selection: " << selection << endl; color(15);
            }
        }
        catch (const exception &)
        {
            color(12); cerr << "Invalid input: " << selection << endl; color(15);
        }
    }

    if (booksToRemove.empty())
    {
        color(12); cout << "No valid books selected for deletion.\n"; color(15);
        return false;
    }

    if (!confirmAction("Are you sure you want to delete the selected book(s)?"))
    {
        color(2); cout << "Book(s) not deleted.\n"; color(15);
        return false;
    }

    // Reescribir el archivo
    ofstream outFile(inventory, ios::trunc);
    if (!outFile)
    {
        color(12); cerr << "Error: Unable to open file for writing.\n"; color(15);
        return false;
    }

    for (const string &line : booksToKeep)
    {
        outFile << line << endl;
    }

    // Escribir todos los libros a mantener
    for (size_t i = 0; i < booksFound.size(); ++i)
    {
        if (find(booksToRemove.begin(), booksToRemove.end(), i) == booksToRemove.end())
        {
            outFile << booksFound[i] << endl;
        }
    }

    outFile.close();
    color(8); cout << "Book(s) deleted successfully." << endl; color(15);
    return true; // Aseguramos que se retorna 'true' cuando los libros han sido eliminados con éxito.
}

void showWishlist(const string &wishList)
{
    color(8); cout << "------------------------------------" << endl; color(15);
    color(6); cout << "The following wishlists have been registered:\n" << endl; color(15);

    ifstream file(wishList);
    if (!file.is_open())
    {
        color(12); cerr << "Error: Unable to open wish list file.\n"; color(15);
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string title, author, genre;

        // Leer los campos separados por coma en el archivo CSV
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, genre, ',');

        // Mostrar los valores
        color(3); cout << "Title: "; color(15); cout << title << "\n";
        color(3); cout << "Author: "; color(15); cout << author << "\n";
        color(3); cout << "Genre: "; color(15); cout << genre << "\n\n";
    }

    file.close();
}

void removeWishList(const string &wishList, const string &keyword)
{
    // Llamamos a la función deleteBookFromCSV para manejar la eliminación
    bool result = deleteBookFromCSV(wishList, keyword);

    if (!result)
    {
        color(2); cout << "No books were deleted.\n"; color(15);
    }
    else
    {
        color(12); cout << "Books matching the keyword '"; color(15); cout << keyword; color(12); cout << "' have been deleted from your wish list.\n"; color(15);
    }
}

// Auxiliary functions
bool containsSearchTerm(Book book, string searchTerm)
{
    // Verifica si la palabra de búsqueda aparece en cualquiera de los atributos
    vector<string> attributes = {book.title, book.author, book.genre, book.year, book.ISBN, book.keywords, book.qualification, book.link};
    for (const auto &attr : attributes)
    {
        if (toLowerCase(attr).find(searchTerm) != string::npos)
            return true;
    }
    return false;
}

bool confirmAction(const string &message)
{
    char confirmation;
    color(12); cout << message << " (y/n): "; color(15);
    cin >> confirmation;
    cin.ignore(); // Limpiar buffer
    return confirmation == 'y' || confirmation == 'Y';
}

Book mapLineToBook(const string &line)
{
    Book book;
    vector<string> fields = parseCSVline(line); // parseCSVLine debe dividir la línea en campos correctamente.

    for (int i = 0; i < fields.size(); i++)
    {
        string field = fields[i];
        if (i == 0)
            book.title = field;
        else if (i == 1)
            book.author = field;
        else if (i == 2)
            book.genre = field;
        else if (i == 3)
            book.year = field;
        else if (i == 4)
            book.ISBN = field;
        else if (i == 5)
            book.keywords = field;
        else if (i == 6)
            book.qualification = field;
        else if (i == 7)
            book.link = field;
    }
    return book;
}

string toLowerCase(const string &input)
{
    string result = input;
    transform(result.begin(), result.end(), result.begin(), [](unsigned char c)
              { return tolower(c); });
    return result;
}

vector<string> parseCSVline(const string &line)
{
    vector<string> fields;
    string field;
    bool insideQuotes = false;

    for (char c : line)
    {
        if (c == '\"')
        {
            insideQuotes = !insideQuotes;
        }
        else if (c == ',' && !insideQuotes)
        {
            fields.push_back(field);
            field.clear();
        }
        else
        {
            field += c;
        }
    }
    fields.push_back(field); // Agrega el último campo
    return fields;
}

void color(int color)
{
    SetConsoleTextAttribute(hConsole, color);
}