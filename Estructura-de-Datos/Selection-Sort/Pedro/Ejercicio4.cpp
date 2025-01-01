#include <iostream>
#include <vector>

using namespace std;

void selectionSort(vector<double>& numbers) {
    int size = numbers.size();
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < size; ++j) {
            if (numbers[j] < numbers[minIndex]) {
                minIndex = j;
            }
        }
        swap(numbers[i], numbers[minIndex]);
    }
}

int main() {
    int size;
    cout << "Enter the number of elements: ";
    cin >> size;

    vector<double> numbers(size);
    cout << "Enter the numbers: ";
    for (int i = 0; i < size; ++i) {
        cin >> numbers[i];
    }

    selectionSort(numbers);
    cout << "List sorted in ascending order: ";
    for (int i = 0; i < size; ++i) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    cout << "List sorted in descending order: ";
    for (int i = size - 1; i >= 0; --i) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
}
