#include <iostream>
#include <deque>
#include <unordered_map>
using namespace std;

/*
LRU cache
    evict the least recently used element
    when capacity is reached

    when put or get is called we keep a track 
    of the most recent element

    the challenge for this is if we keep calling 
    get() on an existing element

    we would remove the element that wasnt accessed

    1. use a queue
        push_back recent element
        pop_front until capacity

    2. to return / insert / update elements use a map

    3. when pop_front is called, check if hashmap size == capacity
        we MUST remove this index from the hashmap
*/
class LRUcache {
private:
    int capacity;
    unordered_map<int, int> mpp; // [key,val]
    deque<int> dq; // key
public:    
    LRUcache(int c) {
        capacity = c;
    }

    

    int get(int key) {
        if(mpp.find(key) == mpp.end()) return -1;

        dq.push_back(key);

        return mpp[key];
    }

    void put(int key, int value) {
        mpp[key] = value;
        dq.push_back(key);

        if(dq.size() > capacity) {
            // need to pop front
            // but do we also need to remove the least frequent element?
            if(mpp.size() == capacity) {
                mpp.erase(dq.front());
            }
            dq.pop_front();
        }
    }
};
int main() {
    return 0;
}