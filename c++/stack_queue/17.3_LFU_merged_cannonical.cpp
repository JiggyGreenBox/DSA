#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;
/*
Before (3 maps)
    keyMap[key]  -> {value, freq}
    freqMap[f]  -> list<key>
    pos[key]    -> iterator into freqMap[f]

After (merged-node)
    nodes[key] -> {value, freq, iterator}
    freqMap[f] -> list<key>
*/
class LFUcache {
private:
    int cap;
    int min_freq;
    struct Node {
        int val;
        int freq;
        list<int>::iterator it;        
    };

    // freq, list<key>
    unordered_map<int, list<int>> freqMap;

    // key, {key,val,it}
    unordered_map<int, Node> nodeMap;
public:
    LFUcache(int capacity) {
        cap = capacity;
        min_freq = 0;
    }

    int get(int key) {
        if(nodeMap.find(key) == nodeMap.end()) return -1;

        touch(key);

        return nodeMap[key].val;
    }

    void put(int key, int value) {
        // update
        if(nodeMap.find(key) != nodeMap.end()) {
            nodeMap[key].val = value;
            touch(key);            
            return;
        }

        // insert
        // evict if full
        if(nodeMap.size() == cap) {
            int evictKey = freqMap[min_freq].back();
            freqMap[min_freq].pop_back();
            nodeMap.erase(evictKey);
        }

        freqMap[1].push_front(key);
        nodeMap[key] = {value, 1, freqMap[1].begin()};
        min_freq = 1;
    }

private:
    void touch(int key) {
        // change freq mapping
        // update min freq if neccessary
        int freq = nodeMap[key].freq;
        auto it = nodeMap[key].it;

        freqMap[freq].erase(it);

        if(freqMap[freq].empty() && freq == min_freq) {
            min_freq++;
        }

        nodeMap[key].freq++;
        freqMap[freq + 1].push_front(key);
        nodeMap[key].it = freqMap[freq + 1].begin();
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