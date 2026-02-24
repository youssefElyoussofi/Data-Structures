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

void recursion_sort(vector<pair<int,int>>& pairs)
{

}

void merge_insertion_sort(vector<int> &arr)
{
    vector<pair<int,int>> pairs;
    int tmp;
    bool struggler = false;
    vector<pair<int,int>>::iterator it;
    for (size_t i = 0; i < arr.size(); ++i)
    {
        if (i + 1 < arr.size())
        {
            pair<int,int> p;
            p.first = arr[i];
            p.second = arr[i + 1];
            pairs.push_back(p);
        }
        else
        {
            tmp = arr[i];
            struggler = true;
        }
    }
    for (size_t i = 0; i < pairs.size(); i++)
    {
        cout << '['<< pairs[i].first << ',' << pairs[i].second << ']' << '\t';
    }
    cout << endl;
}

int main(int ac, char *av[])
{
    vector<int> arr;
    try
    {
        if (ac < 3)
            throw invalid_argument("enter at least 2 numbers");
        parsing(av, arr);
        merge_insertion_sort(arr);
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