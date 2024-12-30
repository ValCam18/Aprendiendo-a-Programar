#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Function declaration
void bubleSortOptimized(vector<int> &arr);
int findSecondLargest(const vector<int> &arr);

int main()
{
    vector<int> numbers;
    int n, element;

    cout << "Enter the numbers of elements: ";
    cin >> n;

    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> element;
        numbers.push_back(element);
    }

    bubleSortOptimized(numbers);

    int secondLargest = findSecondLargest(numbers);
    if (secondLargest != numeric_limits<int>::min())
    {
        cout << "The second largest number is: " << secondLargest << endl;
    }

    return 0;
}

void bubleSortOptimized(vector<int> &arr)
{
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; ++i)
    {
        swapped = false; // Reset the flag for each pass

        for (int j = 0; j < n - 1 - i; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) // Evaluate after completing the inner loop
        {
            break;
        }
    }
}

int findSecondLargest(const vector<int> &arr)
{
    int n = arr.size();
    if (n < 2)
    {
        cerr << "Error: The list must contain at least two elements." << endl;
        return numeric_limits<int>::min();
    }

    // Find the largest number
    int largest = arr[n - 1];

    for (int i = n - 2; i >= 0; --i)
    {
        if (arr[i] < largest)
        {
            return arr[i];
        }
    }

    cerr << "Error: No second largest number found  (all elements are equal)" << endl;
    return numeric_limits<int>::min();
}