#include <list>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <limits.h>
#include <algorithm>

using namespace std;

void parsing(char **av, list<int> &arr)
{
    char *rest = NULL;
    for (size_t i = 1; av[i]; i++)
    {
        long nb = strtol(av[i], &rest, 10);
        if (rest && *rest != '\0')
            throw invalid_argument("invalid input");
        if (nb < INT_MIN || nb > INT_MAX)
            throw invalid_argument("number out of integer range MAX and MIN");
        arr.push_back(static_cast<int>(nb));
    }
}

void insertion_sort(list<int>& arr)
{
    list<int>::iterator it = arr.begin();
    list<int>::iterator curr, tmp;

    while (it != arr.end())
    {
        curr = it;
        for (tmp = arr.begin(); tmp != it;)
        {
            if(*curr < *tmp)
            {
                arr.splice(tmp,arr,curr);
                break;
            }
            ++tmp;
        }
        ++it;
    }
}

int main(int ac, char *av[])
{
    list<int> arr;
    try
    {
        if (ac < 3)
            throw invalid_argument("enter at least 2 numbers");
        parsing(av, arr);
        insertion_sort(arr);
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