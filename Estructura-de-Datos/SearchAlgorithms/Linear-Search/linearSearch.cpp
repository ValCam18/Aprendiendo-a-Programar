#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
using namespace std;

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
void showTopRatedBooks(const string &inventory, int numberTop);
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
        cout << "\nMenu:\n";
        cout << "1. Find a book\n";
        cout << "2. Top rated books\n";
        cout << "3. Wishlist\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        getline(cin, input);

        try
        {
            choice = stoi(input);
            adminChoice = stoi(input);
        }
        catch (const exception &)
        {
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            // Buscar un libro
            string searchTerm;
            cout << "Enter search term: ";
            getline(cin, searchTerm);
            vector<Book> searchResult;

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
                    cout << "-----------------------------------" << endl;
                }
            }
            cout << "Books found: " << searchResult.size() << endl;
            cout << "-----------------------------------" << endl;
            break;
        }
        case 2:
        {
            int numberTop;
            cout << "How many top books would you like to see? ";
            cin >> numberTop;
            cin.ignore();
            showTopRatedBooks(inventory, numberTop);
            break;
        }
        case 3:
            addWishList(wishlist);
            break;
        case 4:
            cout << "Exiting the program.\n";
            break;
        case 88:
            cout << "-----------------------------------" << endl;
            cout << "Admin's Menu" << endl;
            cout << "Enter admin's password: " << endl;
            getline(cin, adminPassword);

            if (adminPassword == "adminpass")
            {
                do
                {
                    cout << "-----------------------------------" << endl;
                    cout << "1. Add a book to inventory" << endl;
                    cout << "2. Remove a book from inventory" << endl;
                    cout << "3. Show Wishlist" << endl;
                    cout << "4. Remove a book from Wishlist" << endl;
                    cout << "5. Back to the main menu." << endl;
                    cout << "Enter your choice: ";
                    cin >> adminChoice;
                    cin.ignore();

                    switch (adminChoice)
                    {
                    case 1:
                    {
                        // Agregar un libro
                        Book newBook;
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

                        addBookToCSV(inventory, newBook);
                        break;
                    }
                    case 2:
                    {
                        // Eliminar un libro
                        string searchTerm;
                        cout << "Enter the search term (could be part of any field): ";
                        getline(cin, searchTerm);

                        deleteBookFromCSV(inventory, searchTerm);
                        break;
                    }
                    case 3:
                        // Show Wishlist
                        showWishlist(wishlist);

                        break;
                    case 4:
                    {
                        // Remove a book from Wishlist
                        string searchTerm;
                        cout << "Enter the search term (could be part of any field): ";
                        getline(cin, searchTerm);

                        removeWishList(wishlist, searchTerm);
                        break;
                    }
                    case 5:
                        cout << "-----------------------------------" << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                        break;
                    }
                } while (adminChoice != 5);
            }
            else
            {
                cout << "Invalid password. Try again." << endl;
            }
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 4);
}

void findBookInCSV(const string &inventory, const string &searchTerm, vector<Book> &searchResult)
{
    ifstream file(inventory);
    if (!file)
    {
        cerr << "Error: Unable to open file.\n";
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

void showTopRatedBooks(const string &inventory, int numberTop)
{
    ifstream file(inventory);
    if (!file)
    {
        cerr << "Error: Unable to open file.\n";
        return;
    }

    string line;
    vector<Book> booksToRate;
    vector<pair<int, float>> indexQualificationPairs;
    int index = 0;

    bool isFirstLineHeader = true;
    while (getline(file, line))
    {
        if (isFirstLineHeader)
        {
            isFirstLineHeader = false;
            continue;
        }

        Book book = mapLineToBook(line);

        float qualification = stof(book.qualification);

        // Agregar pares al vector
        indexQualificationPairs.push_back(make_pair(index, qualification));

        booksToRate.push_back(book);
        index++;
    }
    file.close();

    sort(indexQualificationPairs.begin(), indexQualificationPairs.end(),
         [](const pair<int, float> &a, const pair<int, float> &b)
         {
             return a.second > b.second; // Ordenar de mayor a menor por 'second' (float)
         });

    int topMax = booksToRate.size() < numberTop ? booksToRate.size() : numberTop;

    cout << "\n-----Top Rated Books-----\n";

    for (int i = 0; i < topMax; i++)
    {
        int index = indexQualificationPairs[i].first;
        Book book = booksToRate[index];
        cout << "Top " << i + 1 << ":" << endl;
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

void addWishList(const string &wishList)
{
    cout << "You can add a book to your wish list.\n";

    Book desiredBook;
    cout << "Enter book title: ";
    getline(cin, desiredBook.title);
    cout << "Enter author: ";
    getline(cin, desiredBook.author);
    cout << "Enter genre: ";
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
        cout << "Book added to your wish list successfully.\n";

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
        cout << "Book added successfully." << endl;

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
        cout << "No book found with the search term: " << searchTerm << endl;
        return false;
    }

    // Mostrar los libros encontrados
    cout << "Found " << booksFound.size() << " book(s):\n";
    for (size_t i = 0; i < booksFound.size(); ++i)
    {
        Book book = mapLineToBook(booksFound[i]);
        cout << i + 1 << ". ";
        if (book.ISBN != "")
        {
            cout << "ISBN: " << book.ISBN << " | ";
        }
        cout << "Title: " << book.title << " | Author: " << book.author << endl;
    }

    // Leer selección del usuario
    cout << "\nEnter the number(s) of the book(s) you want to delete (separated by spaces): ";
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
                cerr << "Invalid selection: " << selection << endl;
            }
        }
        catch (const exception &)
        {
            cerr << "Invalid input: " << selection << endl;
        }
    }

    if (booksToRemove.empty())
    {
        cout << "No valid books selected for deletion.\n";
        return false;
    }

    if (!confirmAction("Are you sure you want to delete the selected book(s)?"))
    {
        cout << "Book(s) not deleted.\n";
        return false;
    }

    // Reescribir el archivo
    ofstream outFile(inventory, ios::trunc);
    if (!outFile)
    {
        cerr << "Error: Unable to open file for writing.\n";
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
    cout << "Book(s) deleted successfully." << endl;
    return true; // Aseguramos que se retorna 'true' cuando los libros han sido eliminados con éxito.
}

void showWishlist(const string &wishList)
{
    cout << "The following wishlists have been registered:";

    ifstream file(wishList);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open wish list file.\n";
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
        cout << "Title: " << title << "\n";
        cout << "Author: " << author << "\n";
        cout << "Genre: " << genre << "\n\n";
    }

    file.close();
}

void removeWishList(const string &wishList, const string &keyword)
{
    // Llamamos a la función deleteBookFromCSV para manejar la eliminación
    bool result = deleteBookFromCSV(wishList, keyword);

    if (!result)
    {
        cout << "No books were deleted.\n";
    }
    else
    {
        cout << "Books matching the keyword '" << keyword << "' have been deleted from your wish list.\n";
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
    cout << message << " (y/n): ";
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
