#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <limits.h>
#include <stdexcept>
#include <algorithm>

using namespace std;

void selection_sort(vector<int>& vec)
{
    vector<int>::iterator it = vec.begin();
    vector<int>::iterator start = vec.begin();
    vector<int>::iterator min;

    for (; it != vec.end() - 1;it++)
    {
        min = min_element(it,vec.end());
        swap(*it,*min);
    }
}

int main(int ac, char *av[])
{
    vector<int> arr;
    try
    {
        if (ac < 3)
            throw invalid_argument("enter at least 2 numbers as argement for sorting");
        arr.reserve(ac - 1);
        for (size_t i = 1; i < ac; i++)
        {
            string tmp = av[i];
            char* rest;
            long nb = strtol(tmp.c_str(), &rest, 10);
            if (rest && *rest != '\0')
                throw invalid_argument("invalid input it must be number");
            if (nb > INT_MAX || nb < INT_MIN)
                throw invalid_argument("number cannot be INT_MAX or INT_MIN");
            arr.push_back(nb);
        }
    }
    catch (const exception &e)
    {
        cerr << e.what() << "\n";
        return 1;
    }
    selection_sort(arr);
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << '\t';
    }
    cout << endl;
    
    return 0;
}