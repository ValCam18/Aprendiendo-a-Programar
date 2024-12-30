//Exercise 10 Selection Sort
//Use the algorithm to sort a list of dates.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Date {
    int year;
    int month;
    int day;
};

bool compare(const Date& d1, const Date& d2);
void selectionSort(vector<Date>& dates);

int main() {
    int size;
    cout << "Enter the size: ";
    cin >> size;
    
    vector<Date> dates(size);
    
    for (int i = 0; i < size; i++) {
        cout << "Enter the date separated by a space (day month year): ";
        cin >> dates[i].day >> dates[i].month >> dates[i].year;
    }
    
    selectionSort(dates);
    
    cout << "Sorted dates:" << endl;
    for (const auto& date : dates) {
        cout << (date.day < 10 ? "0" : "") << date.day << "-" << (date.month < 10 ? "0" : "") << date.month << "-" << date.year << endl;
    }
    
    return 0;
}

bool compare(const Date& d1, const Date& d2) {
    if (d1.year != d2.year) {
        return d1.year < d2.year;
    }
    if (d1.month != d2.month) {
        return d1.month < d2.month;
    }
    return d1.day < d2.day;
}

void selectionSort(vector<Date>& dates) {
    int n = dates.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (compare(dates[j], dates[min_idx])) {
                min_idx = j;
            }
        }
        swap(dates[i], dates[min_idx]);
    }
}
