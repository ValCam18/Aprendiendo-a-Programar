//Ejercicio 2: Implementa el algoritmo para ordenar una lista de cadenas según su longitud.
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Word {
    string text;
    int length;
};

void selectionSort(vector<Word>& words) {
    int size = words.size();
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < size; ++j) {
            if (words[j].length < words[minIndex].length) {
                minIndex = j;
            }
        }
        Word temp = words[i];
        words[i] = words[minIndex];
        words[minIndex] = temp;
    }
}

int main() {
    vector<Word> words;
    string text;
    int size;

    cout << "Enter the number of words: ";
    cin >> size;

    cout << "Enter the words:" << endl;
    for (int i = 0; i < size; ++i) {
        cin >> text;
        Word word;
        word.text = text;
        word.length = text.length();
        words.push_back(word);
    }

    selectionSort(words);

    cout << "Words sorted by length: "<< endl;;
    for (const Word& word : words) {
        cout << word.text << endl;
    }
    return 0;
}
