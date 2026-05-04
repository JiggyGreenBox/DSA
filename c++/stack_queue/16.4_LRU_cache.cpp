#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LRUcache {
private:
    
    list<pair<int,int>> dll; // <key,val>, // most recent at front
    // front = most recently used
    // back  = least recently used
    unordered_map<int, list<pair<int,int>>::iterator> cache; // use auto it, to move / delete list element
    int cap;
public:
    LRUcache(int capacity) {
        cap = capacity;
    }

    int get(int key) {
        if(cache.find(key) == cache.end()) return -1;

        auto it = cache[key];
        dll.splice(dll.begin(), dll, it); // move it to front

        return it->second;
    }

    void put(int key, int value) {
        // update existing pair
        // place element at front of dll-list
        if(cache.find(key) != cache.end()) {
            auto it = cache[key];
            it->second = value; // update value

            // l1.splice(pos, l2);              // For whole list
            // l1.splice(pos, l2, pos1);        // For single element
            // l1.splice(pos, l2, first, last); // For range of elements.

            dll.splice(dll.begin(), dll, it); // move to front of dll-list
        }
        else{
            // need to insert a new element into front of dll-list
            // if we are full we will need to delete the last element from dll-list

            // cache-full
            // evict last element from dll
            if(dll.size() == cap) {
                auto lru = dll.back();
                cache.erase(lru.first);
                dll.pop_back();
            }

            // insert new key at front
            dll.emplace_front(key, value);
            cache[key] = dll.begin();
        }
    }
};

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
    // listA.splice(listA.begin(), listA, std::next(listA.begin(), 2));
    // print(listA); // [ 10 20 1 30 ]
    

    LRUcache cache(2);

    cache.put(1,1);
    cache.put(2,2);
    cout << cache.get(1) << endl;   // 1
    cache.put(3,3);
    cout << cache.get(2) << endl;   // -1
    cout << cache.get(3) << endl;   // 3
    cache.put(5,5);
    cache.put(10,10);
    cout << cache.get(3) << endl;   // -1
    cout << cache.get(10) << endl;  // 10

    return 0;
}

// dll-list to store key,val
// front latest
// back oldest

// un_map[key, it] 
    // it = std::list<pair<int, int>>::iterator
// get -> check map
    // it-> <key,val>
    // move it to front of dll-list

// put
    // check map
        // key exists, update val
        // move it to front of dll-list

        // no key- insert new pair in dll-list and map
            // if cache == limit
                // delete dll-list back()
            // insert-front dll-list <key,val>
            // un_map[key] = dll-list.begin()