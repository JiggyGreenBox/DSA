#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print(vector<int>& vec){
    // Print result
    for (int x : vec) cout << x << " ";
    cout << endl;
}

int main(){

    // =====================================================================
    // erase
    //      after erased element, left shift O(n)
    // =====================================================================
    

    vector<int> v = {10, 20, 30, 40, 50};

    // Erase by position
    v.erase(v.begin() + 2);  // removes element at index 2 (30)

    // Erase a range
    v.erase(v.begin(), v.begin() + 2); // removes first two elements (10, 20)

    print(v);



    v = {10, 20, 30, 40, 50};
    v.erase(v.begin()+1, v.begin() + 2); // second arg is non-inclusive, only (20) is removed
    print(v);

    // erase(pos) removes the element at iterator pos.
    // erase(first, last) removes all elements in the range [first, last).
    // Elements after the erased ones are shifted left — O(n) complexity.


    // =====================================================================
    // remove    
    //      O(n)
    // =====================================================================

    v = {10, 20, 30, 20, 40};
    print(v);

    // "Remove" 20s by shifting non-20s to front
    auto new_end = remove(v.begin(), v.end(), 20);

    print(v);

    cout << "\nNew logical end index: " << (new_end - v.begin()) << endl;

    // remove() does not actually erase elements — it just moves the unwanted ones to the end.
    // Returns an iterator (new_end) to the new logical end of the range.
    // You must call erase() to really delete those elements.


    // =====================================================================
    // erase + remove    
    //      O(n)
    // =====================================================================

    v = {1, 2, 3, 2, 4, 2, 5};
    print(v);
    v.erase(remove(v.begin(), v.end(), 2), v.end());
    print(v);

    // Steps:
    // remove() does one pass (O(n))
    // erase() deletes leftover tail (O(k) ≤ O(n))
    // Total: O(n)

    // =====================================================================
    // only erase?
    //          O(n^2)
    // =====================================================================

    // If you use only std::vector::erase to remove all elements matching 
    // a specific value from a vector, the time complexity will be O(N^2) 
    // (Quadratic Time), which is highly inefficient.
    // The Erase-Remove Idiom is necessary because it achieves O(N) efficiency.
    // Removing the std::remove step causes the performance degradation.

    v = {1, 2, 3, 2, 4, 2, 5};
    int value_to_remove = 2;

    for (auto it = v.begin(); it != v.end(); /* update in loop */) {
        if (*it == value_to_remove) {
            // INEFFICIENT: Erasing here shifts the rest of the array
            it = v.erase(it); 
        } else {
            it++;
        }
    }
    // In the worst-case scenario (e.g., removing every element), the outer loop runs O(N) times.
    // As previously discussed, std::vector::erase(iterator) must shift all subsequent elements to close the gap.
    // If you erase an element near the beginning, the shift takes O(N) time.
    // n^2

    
    // so erase + remove, perform the shift only once


    return 0;
}