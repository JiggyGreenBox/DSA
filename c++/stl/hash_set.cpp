#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    unordered_set<int> mset;

    mset.insert(1);
    mset.insert(2);
    mset.insert(5);
    mset.insert(6);
    mset.insert(7);

    mset.insert(-2);
    mset.insert(-3);
    mset.insert(-1);

    for(auto x: mset) {
        cout << x << " ";
    }

    return 0;
}