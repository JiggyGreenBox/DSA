#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

void print(list<int> l) {
    cout << "[ ";
    for (int num : l) {
        cout << num << " ";
    }    
    cout << "]\n";
}

int main() {

    // splice practice
    std::list<int> listA = {10, 20, 30};
    std::list<int> listB = {1, 2, 3, 4, 5};
    // listA.splice(listA.begin(), listB, listB.begin(), listB.end());
    // print(listA); // [ 1 2 3 4 5 10 20 30 ]

    // listA.splice(std::next(listA.begin(),2), listB, listB.begin(), listB.end());
    // print(listA); // [ 10 20 1 2 3 4 5 30 ]

    // listA.splice(std::next(listA.begin(),2), listB, listB.begin(), std::next(listB.begin()));
    // print(listA); // [ 10 20 1 30 ]

    // splice ( start pos, list, list-start, list-end) 
        // this is for a range
    // splice ( start pos, list, list-iterator)
        // this is for a single element
    listA.splice(listA.begin(), listA, std::next(listA.begin(), 2));
    print(listA); // [ 30 10 20 ]

    listB.splice(listB.begin(), listB, std::next(listB.begin(), 3)); // move 4 ahead
    print(listB); // [ 30 10 20 ]
    

    return 0;
}