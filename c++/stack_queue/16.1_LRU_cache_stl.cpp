#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LRUcache {
private:

    int capacity;

    // front = most recently used
    // back  = least recently used
    list<pair<int,int>> dll; // <key,val>, // most recent at front
    
    // key and iterator to the above list
    unordered_map<int, list<pair<int,int>>::iterator> mpp; // use auto it, to move / delete list element
    
public:
    LRUcache(int capacity) : capacity(capacity) {}

    int get(int key) {

        if(mpp.find(key) == mpp.end()) 
            return -1;

        // move node to the front
        auto it = mpp[key];
        int value = it->second;
        
        dll.erase(it);
        dll.push_front({key, value});
        mpp[key] = dll.begin();

        return value;
    }

    int get_splice(int key) {

        if(mpp.find(key) == mpp.end()) 
            return -1;
        
        auto it = mpp[key];
        dll.splice(dll.begin(), dll, it);
        

        return dll.begin()->second;
    }

    void put(int key, int value) {
        
        // key exists
        if(mpp.find(key) != mpp.end()) {
            dll.erase(mpp[key]); // use iterator to delete
        }
        else if(dll.size() == capacity) {
            // we get rid of last dll entry
            auto last = dll.back();
            mpp.erase(last.first);
            dll.pop_back();
        }

        dll.push_front({key, value});
        mpp[key] = dll.begin();
    }

    void put_splice(int key, int value) {
        
        // Key already exists
        if(mpp.find(key) != mpp.end()) {
            auto it = mpp[key];

            it->second = value; // update
            dll.splice(dll.begin(), dll, it); // move to front

            return;
        }

        // cache full
        if(dll.size() == capacity) {
            auto last = dll.back();
            mpp.erase(last.first);
            dll.pop_back();
        }

        dll.push_front({key, value});
        mpp[key] = dll.begin();
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