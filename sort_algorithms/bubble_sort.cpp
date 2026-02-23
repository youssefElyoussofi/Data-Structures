#include <vector>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <limits.h>
#include <algorithm>

using namespace std;

void parsing(char **av, vector<int>& vec)
{
    char *rest = NULL;
    for (size_t i = 1; av[i]; i++)
    {
        long nb = strtol(av[i],&rest,10);
        if (rest && *rest != '\0')
            throw invalid_argument("invalid input");
        if (nb < INT_MIN || nb > INT_MAX)
            throw invalid_argument("number out of integer range MAX and MIN");
        vec.push_back(static_cast<int>(nb));
    }
}

void bubble_sort(vector<int>& array)
{
    size_t len = array.size();
    for (size_t n = 0; n < len; n++)
    {
        for (size_t i = 0; i < len - n; i++)
        {
            if (i + 1 < len && array[i] > array[i + 1])
            {
                int tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
            }
        }
    }
}

int main(int ac, char *av[])
{
    vector<int> vec;
    try
    {
        if (ac < 3)
            throw invalid_argument("enter at least 2 numbers");
        vec.reserve(ac-1);
        parsing(av,vec);
        bubble_sort(vec);
        if (is_sorted(vec.begin(),vec.end()))
            cout << "array sorted successfully\n";
        else
            cout << "array not sorted\n";
    }
    catch (const exception &e)
    {
        cout << e.what() << '\n';
    }
}