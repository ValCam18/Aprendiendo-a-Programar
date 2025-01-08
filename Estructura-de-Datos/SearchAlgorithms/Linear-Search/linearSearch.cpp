#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
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

// Declaración de las funciones
void addBookToCSV(const string &inventory, const Book &book);
void findBookInCSV(const string &inventory, const string &searchTerm, vector<Book> &searchResult);
bool containsSearchTerm(Book book, string searchTerm);
bool deleteBookFromCSV(const string &inventory, const string &searchTerm);
void showMenu(const string &inventory);

int main()
{
    string inventory = "inventory.csv"; // Ruta al archivo CSV
    showMenu(inventory);
    return 0;
}

void addBookToCSV(const string &inventory, const Book &book)
{
    try
    {
        ofstream file(inventory, ios::app); // Abre el archivo en modo append
        if (file.is_open())
        {
            file << "\"" << book.title << "\","
                 << "\"" << book.author << "\","
                 << "\"" << book.genre << "\","
                 << "\"" << book.year << "\","
                 << "\"" << book.ISBN << "\","
                 << "\"" << book.keywords << "\","
                 << "\"" << book.qualification << "\","
                 << "\"" << book.link << "\"\n"; // Agrega la nueva línea para el libro
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

    /*string title = "Title: ";
    string author = "Author: ";
    string genre = "Genre: ";
    string year = "Year: ";
    string ISBN = "ISBN: ";
    string keywords = "Keywords: ";
    string qualification = "Qualification: ";
    string link = "Link: ";*/

    while (getline(file, line))
    {
        stringstream ss(line);
        string field;
        int column = 0;

        // Manejo de comillas
        bool inQuotes = false;
        string currentField = "";

        for (char c : line)
        {
            if (c == '"')
            {
                inQuotes = !inQuotes; // Toggle quotes
            }
            else if (c == ',' && !inQuotes)
            {
                // Si no estamos dentro de comillas, separamos por coma
                field = currentField;
                currentField.clear();

                // Asigna el campo correspondiente
                switch (column)
                {
                case 0:
                    book.title = field;
                    break;
                case 1:
                    book.author = field;
                    break;
                case 2:
                    book.genre = field;
                    break;
                case 3:
                    book.year = field;
                    break;
                case 4:
                    book.ISBN = field;
                    break;
                case 5:
                    book.keywords = field;
                    break;
                case 6:
                    book.qualification = field;
                    break;
                case 7:
                    book.link = field;
                    break;
                }

                column++;
            }
            else
            {
                currentField += c; // Acumula el carácter en el campo actual
            }
        }

        // Para el último campo
        if (!currentField.empty())
        {
            switch (column)
            {
            case 0:
                book.title = currentField;
                break;
            case 1:
                book.author = currentField;
                break;
            case 2:
                book.genre = currentField;
                break;
            case 3:
                book.year = currentField;
                break;
            case 4:
                book.ISBN = currentField;
                break;
            case 5:
                book.keywords = currentField;
                break;
            case 6:
                book.qualification = currentField;
                break;
            case 7:
                book.link = currentField;
                break;
            }

            column++;
        }
        if (containsSearchTerm(book, searchTerm))
        {
            searchResult.push_back(book);
        }
    }

    file.close();
}

bool containsSearchTerm(Book book, string searchTerm)
{
    // Verifica si la palabra de búsqueda aparece en cualquiera de los atributos
    vector<string> attributes = {book.title, book.author, book.genre, book.year, book.ISBN, book.keywords, book.qualification, book.link};
    for (const auto &attr : attributes)
    {
        if (attr.find(searchTerm) != string::npos)
            return true;
    }
    return false;
}

bool deleteBookFromCSV(const string &inventory, const string &searchTerm)
{
    ifstream file(inventory);
    if (!file)
    {
        cerr << "Error: Unable to open file.\n";
        return false;
    }

    vector<string> lines;
    string line;
    bool deleted = false;

    // Leer todas las líneas en un vector
    while (getline(file, line))
    {
        // Si la palabra de búsqueda no está en ninguna parte del libro, lo mantenemos
        if (line.find(searchTerm) == string::npos)
        {
            lines.push_back(line); // Si no coincide con el término de búsqueda, guardar la línea
        }
        else
        {
            deleted = true; // Marcamos que se eliminó el libro
        }
    }
    file.close();

    // Si se eliminó, reescribir el archivo sin el libro
    if (deleted)
    {
        ofstream outFile(inventory);
        for (const string &line : lines)
        {
            outFile << line << endl;
        }
        outFile.close();
        cout << "Book deleted successfully." << endl;
    }
    else
    {
        cout << "No book found with the search term: " << searchTerm << endl;
    }

    return deleted;
}

void showMenu(const string &inventory)
{
    int choice;
    do
    {
        // Mostrar menú de opciones
        cout << "\nMenu:\n";
        cout << "1. Add a Book\n";
        cout << "2. Find a Book\n";
        cout << "3. Delete a Book\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Limpiar el buffer de entrada

        switch (choice)
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
        case 3:
        {
            // Eliminar un libro
            string searchTerm;
            cout << "Enter the search term (could be part of any field): ";
            getline(cin, searchTerm);

            deleteBookFromCSV(inventory, searchTerm);
            break;
        }
        case 4:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}