#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;
    v.reserve(2);

    v.push_back(1);
    v.push_back(2);


    int *ptr = &v[1];

    cout << "value of ptr: " << *ptr << endl; // 2

    v.push_back(3); // heap moves because capacity reached, new dynamic array created, original ptr is lost

    cout << "value of ptr: " << *ptr << endl; // 0 UB

    // solutions for this case:
    //  1. store index instead
    //  2. use deque

    return 0;
}