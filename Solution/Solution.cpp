#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void show(vector<int> in) {
    for (auto i : in) {
        cout << i << " ";
    }
    cout << endl;
}

void removeDuplicates(std::vector<int>& in)
{
    auto end = in.end();
    for (auto i = in.begin(); i != end; ++i) {
        end = remove(i + 1, end, *i);
    }
    in.erase(end, in.end());
}

int main()
{
    vector<int> v = { 1, 2, 5, 50, 47, 2 ,1, 3, 5, 2, 1, 50, 47, 8, 23, 1, 8 };
    show(v);
    removeDuplicates(v);
    show(v);

    return 0;
}