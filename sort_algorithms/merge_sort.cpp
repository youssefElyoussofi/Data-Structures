#include <vector>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <limits.h>
#include <algorithm>

using namespace std;

void parsing(char **av, vector<int> &arr)
{
    char *rest = NULL;
    for (size_t i = 1; av[i]; i++)
    {
        long nb = strtol(av[i], &rest, 10);
        if (rest == av[i] && *rest != '\0')
            throw invalid_argument("invalid input");
        if (nb < INT_MIN || nb > INT_MAX)
            throw invalid_argument("number out of integer range MAX and MIN");
        arr.push_back(static_cast<int>(nb));
    }
}

void merge_sort(vector<int> arr)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << ',';
    }
    cout << endl;
    if (arr.size() > 1)
    {
        size_t m = arr.size() / 2;
        // if (m % 2 != 0)
        //     m++;
        vector<int> first(arr.begin(),arr.begin() + m);
        vector<int> second(arr.begin()+ m ,arr.end());
        merge_sort(first);
        merge_sort(second);
    }
    
}

int main(int ac, char *av[])
{
    vector<int> arr;
    try
    {
        if (ac < 3)
            throw invalid_argument("enter at least 2 numbers");
        parsing(av, arr);
        merge_sort(arr);
        if (is_sorted(arr.begin(), arr.end()))
            cout << "array sorted successfully\n";
        else
            cout << "array not sorted\n";
    }
    catch (const exception &e)
    {
        cout << e.what() << '\n';
    }
}