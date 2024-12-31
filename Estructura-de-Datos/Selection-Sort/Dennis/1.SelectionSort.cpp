#include <iostream>
#include <list>

using namespace std;

struct Node
{
    int data;
    Node *next;
};

void insertNode(Node *&head, int value);
void printList(Node *head);
void selectionSort(Node *&head);

int main()
{

    Node *list = nullptr;
    int num, value;

    cout << "Cuantos números deseas almacenar en la lista: ";
    cin >> num;

    for (int i = 0; i < num; i++)
    {
        cout << "Ingresa el numero " << i + 1 << ": ";
        cin >> value;
        insertNode(list, value);
    }

    cout << "Elementos de la lista: ";
    printList(list);

    selectionSort(list);
    cout << "Elementos ordenados: ";
    printList(list);

    return 0;
}

void insertNode(Node *&head, int value)
{
    Node *newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node *aux = head;
        while (aux->next != nullptr)
        {
            aux = aux->next;
        }
        aux->next = newNode;
    }
}

void printList(Node *head)
{
    Node *aux = head;
    while (aux != nullptr)
    {
        cout << aux->data << " -> ";
        aux = aux->next;
    }
    cout << "nullptr" << endl;
}

void selectionSort(Node *&head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    Node *current = head;
    while (current != nullptr)
    {
        Node *minNode = current;
        Node *nextNode = current->next;

        while (nextNode != nullptr)
        {
            if (nextNode->data < current->data)
            {
                minNode = nextNode;
            }
            nextNode = nextNode->next;
        }
        swap(current->data, minNode->data);
        current = current->next;
    }
}
