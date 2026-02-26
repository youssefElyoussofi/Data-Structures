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
    if (pairs.size() <= 1)
        return;
    size_t mid = pairs.size() / 2;
    
    vector<pair<int,int>> left(pairs.begin(),pairs.begin()+mid);
    vector<pair<int,int>> right(pairs.begin()+mid,pairs.end());
    recursion_sort(left);
    recursion_sort(right);

    vector<pair<int,int>>::iterator it, it1 ,it2;
    it = pairs.begin();
    it1 = left.begin();
    it2 = right.begin();
    while (it1 != left.end() && it2 != right.end())
    {
        if (it1->first < it2->first)
            *it++ = *it1++;
        else
            *it++ = *it2++;
    }
    if (it1 != left.end())
    {
        while (it1 != left.end() && it != pairs.end())
            *it++ = *it1++;
    }
    if (it2 != right.end())
    {
        while (it2 != right.end() && it != pairs.end())
            *it++ = *it2++;
    }
}

bool compare(const pair<int,int>& elem,const pair<int,int>& tmp_elem)
{
    return elem.first < tmp_elem.first;
}

void insertion(vector<pair<int,int>>& pairs)
{
    vector<pair<int,int>> losers;

    losers = pairs;

    vector<int> jacobstal(22);
    jacobstal[0] = 0;
    jacobstal[1] = 1;
    for (size_t i = 2; i < 20; i++)
    {
        jacobstal[i] = jacobstal[i - 1] + (jacobstal[i - 2] * 2);
    }
    
    int currIndex = 0;
    int jacobIndex = 2;
    int oldIndex = 0;
    while (currIndex < losers.size() - 1)
    {
        pair<int,int> tmp;
        vector<pair<int,int>>::iterator target, insert_pos;
        if (jacobstal[jacobIndex] == 1)
        {
            tmp.first = losers[currIndex].second;
            tmp.second = losers[currIndex].first;
            pairs.insert(pairs.begin(),tmp);
        }
        else 
        {
            oldIndex = currIndex;
            if (jacobstal[jacobIndex] - 1 < losers.size())
                currIndex = jacobstal[jacobIndex] - 1;
            else
                currIndex = losers.size() - 1;
            for (int i = currIndex; oldIndex != i; --i)
            {
                tmp.first = losers[i].second;
                tmp.second = losers[i].first;
                target = find(pairs.begin(),pairs.end(),losers[i]);
                insert_pos = lower_bound(pairs.begin(),target,tmp,compare);
                pairs.insert(insert_pos,tmp);
            }
        }
        ++jacobIndex;
    }
}

void merge_insertion_sort(vector<int> &arr)
{
    vector<pair<int,int>> pairs;
    int tmp;
    bool struggler = false;

    vector<pair<int,int>>::iterator it;
    for (size_t i = 0; i < arr.size();)
    {
        if (i + 1 < arr.size())
        {
            pair<int,int> p;
            if (arr[i] > arr[i+1])
            {
                p.first = arr[i];
                p.second = arr[i + 1];
            }
            else
            {
                p.first = arr[i+1];
                p.second = arr[i];
            }
            pairs.push_back(p);
        }
        else
        {
            tmp = arr[i];
            struggler = true;
        }
        i += 2;
    }
    recursion_sort(pairs);

    insertion(pairs);
    
    arr.clear();
    for (size_t i = 0; i < pairs.size(); i++)
    {
        arr.push_back(pairs[i].first);
        cout << pairs[i].first << (i < pairs.size()-1?',':'\n');
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