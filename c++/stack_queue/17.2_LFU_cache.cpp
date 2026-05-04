#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

/*
i had 2 DS with lots of pairs etc

cannonical has 3 DS's
    1. unordered_map < int, pair<int,int > > keyMap;
        key , value, freq
        map[key] = pair<val, freq>
    
    2. unordered_map < int, list<int> > freqMap
        freq = dll,
            push front, pop_back
        we need min_freq to do this
    
    3. we need a mapping between these 2 DS's
        when we change freq of a key,val
            we need to move it
        
        key, it
        unordered_map < int, list<int>::iterator >

    4. min freq key
        assign =1 when a new element is inserted
        
        put(1,1)
        put(2,2)
            min_freq = 1
            freq[1] = [2,1]
        get(1)
            min_freq = 1
            freq[2] = [1]
            freq[1] = [2]
        get(2)
            
            freq[2] = [2,1]
            freq[1] = []
                change min_freq = 2
*/

class LFUcache {
private:
    int cap;
    int min_freq;
    // {key,{val,freq}}
    unordered_map<int, pair<int,int>> keyMap;

    // {freq, list<key>}
    unordered_map<int, list<int>> freqMap;

    // {key, iterator}
    unordered_map<int, list<int>::iterator> linkMap;
public:
    LFUcache(int capacity) {
        cap = capacity;
        min_freq = 0;
    }

    int get(int key) {
        if(cap == 0 || keyMap.find(key) == keyMap.end()) return -1;

        touch(key);

        return keyMap[key].first;
    }

    void put(int key, int value) {
        if(cap == 0) return;

        // update existing key
        if(keyMap.find(key) != keyMap.end()) {
            keyMap[key].first = value;
            touch(key);
            return;            
        }

        // insert new key
        // evict if reached capacity
        if(keyMap.size() == cap) {
            int evict_key = freqMap[min_freq].back();
            freqMap[min_freq].pop_back();
            keyMap.erase(evict_key);
            linkMap.erase(evict_key);
        }

        keyMap[key] = {value, 1};
        freqMap[1].push_front(key);
        linkMap[key] = freqMap[1].begin();
        min_freq = 1;
    }
    
private:
    void touch(int key) {

        // get iterator to dll, from linkMap
        // change freqMapping
        //      remove from cur freq
        //      add to freq+1
        // update min_freq
        // update keyMap freq
        // update iterator in dll with it[freq+1]

        int freq = keyMap[key].second;
        auto it = linkMap[key];

        // remove from freq list
        freqMap[freq].erase(it);

        // update min freq
        // min freq is a bucket
        // if the bucket is empty due to the current element
        // then the min freq increments
        if(freqMap[freq].empty() && min_freq == freq) {
            min_freq++;
        }

        // update new freqs
        keyMap[key].second++;
        freqMap[freq + 1].push_front(key);
        linkMap[key] = freqMap[freq + 1].begin();
    }
};

int main() {
    LFUcache cache(2);
    cache.put(1,1);
    cache.put(2,2);
    cout << cache.get(1) << endl;       // 1     
    cache.put(3,3);              
    cout << cache.get(2) << endl;       // -1

    cout << cache.get(3) << endl;       // 3
    cout << cache.get(3) << endl;       // 3
    cache.put(4,4);
    cout << cache.get(1) << endl;       // -1
    cache.put(5,5);
    cout << cache.get(4) << endl;       // -1
    return 0;
}