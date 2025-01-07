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
bool findBookInCSV(const string &inventory, const string &searchTerm, Book &foundBook);
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

bool findBookInCSV(const string &inventory, const string &searchTerm, Book &foundBook)
{
    ifstream file(inventory);
    if (!file)
    {
        cerr << "Error: Unable to open file.\n";
        return false;
    }

    string line;
    bool found = false;

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
                    foundBook.title = field;
                    break;
                case 1:
                    foundBook.author = field;
                    break;
                case 2:
                    foundBook.genre = field;
                    break;
                case 3:
                    foundBook.year = field;
                    break;
                case 4:
                    foundBook.ISBN = field;
                    break;
                case 5:
                    foundBook.keywords = field;
                    break;
                case 6:
                    foundBook.qualification = field;
                    break;
                case 7:
                    foundBook.link = field;
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
                foundBook.title = currentField;
                break;
            case 1:
                foundBook.author = currentField;
                break;
            case 2:
                foundBook.genre = currentField;
                break;
            case 3:
                foundBook.year = currentField;
                break;
            case 4:
                foundBook.ISBN = currentField;
                break;
            case 5:
                foundBook.keywords = currentField;
                break;
            case 6:
                foundBook.qualification = currentField;
                break;
            case 7:
                foundBook.link = currentField;
                break;
            }

            column++;
        }

        // Verifica si la palabra de búsqueda aparece en cualquiera de los atributos
        if (foundBook.title.find(searchTerm) != string::npos ||
            foundBook.author.find(searchTerm) != string::npos ||
            foundBook.genre.find(searchTerm) != string::npos ||
            foundBook.year.find(searchTerm) != string::npos ||
            foundBook.ISBN.find(searchTerm) != string::npos ||
            foundBook.keywords.find(searchTerm) != string::npos ||
            foundBook.qualification.find(searchTerm) != string::npos ||
            foundBook.link.find(searchTerm) != string::npos)
        {
            found = true;
            break;
        }
    }

    file.close();
    return found;
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

            Book foundBook;
            bool found = findBookInCSV(inventory, searchTerm, foundBook);

            if (found)
            {
                cout << "Book found: \n";
                cout << "Title: " << foundBook.title << "\n";
                cout << "Author: " << foundBook.author << "\n";
                cout << "Genre: " << foundBook.genre << "\n";
                cout << "Year: " << foundBook.year << "\n";
                cout << "ISBN: " << foundBook.ISBN << "\n";
                cout << "Keywords: " << foundBook.keywords << "\n";
                cout << "Qualification: " << foundBook.qualification << "\n";
                cout << "Link: " << foundBook.link << "\n";
            }
            else
            {
                cout << "Book not found.\n";
            }
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
