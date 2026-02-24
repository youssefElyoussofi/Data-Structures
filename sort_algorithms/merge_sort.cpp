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

void merge_sort(vector<int> &arr)
{
    if (arr.size() <= 1)
        return;
    size_t mid = arr.size() / 2;
    vector<int> first(arr.begin(), arr.begin() + mid);
    vector<int> second(arr.begin() + mid, arr.end());

    merge_sort(first);
    merge_sort(second);

    vector<int> sorted;
    sorted.reserve(first.size() + second.size());
    auto it1 = first.begin(), it2 = second.begin();
    while (it1 != first.end() && it2 != second.end())
    {
        if (*it1 < *it2)
        {
            sorted.push_back(*it1);
            it1++;
        }
        else
        {
            sorted.push_back(*it2);
            it2++;
        }
    }
    // no need to check for left data in our vectors
    // the insert is smart it's check if iterator __first same as iterator __last
    // do nothing
    sorted.insert(sorted.end(), it1, first.end());
    sorted.insert(sorted.end(), it2, second.end());
    arr = sorted;
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

    for (auto it = arr.begin(); it != arr.end(); it++)
    {
        cout << *it << ',';
    }
}