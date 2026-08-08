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





#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

class LFUCache {
private:
    struct Node {
        int key;
        int value;
        int freq;
        list<int>::iterator it;
    };

    int capacity;
    int minFreq;

    // key -> node information
    unordered_map<int, Node> nodes;

    // frequency -> keys ordered by recency
    unordered_map<int, list<int>> freqList;

public:
    LFUCache(int cap) {
        capacity = cap;
        minFreq = 0;
    }

    int get(int key) {

        auto it = nodes.find(key);

        if (it == nodes.end())
            return -1;

        increaseFrequency(it->second);

        return it->second.value;
    }

    void put(int key, int value) {

        if (capacity == 0)
            return;

        auto it = nodes.find(key);

        // Update existing key
        if (it != nodes.end()) {
            it->second.value = value;
            increaseFrequency(it->second);
            return;
        }

        // Evict LFU if full
        if (nodes.size() == capacity) {

            int evictKey = freqList[minFreq].back();

            freqList[minFreq].pop_back();

            if (freqList[minFreq].empty())
                freqList.erase(minFreq);

            nodes.erase(evictKey);
        }

        // Insert new node
        freqList[1].push_front(key);

        nodes[key] = {
            key,
            value,
            1,
            freqList[1].begin()
        };

        minFreq = 1;
    }

private:

    void increaseFrequency(Node &node) {

        int oldFreq = node.freq;

        freqList[oldFreq].erase(node.it);

        if (freqList[oldFreq].empty()) {

            freqList.erase(oldFreq);

            if (minFreq == oldFreq)
                minFreq++;
        }

        node.freq++;

        freqList[node.freq].push_front(node.key);

        node.it = freqList[node.freq].begin();
    }
};

/*

put(1,..)
    nodes[1] = {...}
    F[1].push_front(1)
    min = 1

put(2,..)
    nodes[2] = {...}
    F[1].push_front(2)
        F[1] = {2,1}
    min = 1

get(1)
    auto node = node.find(1)
    return node.val

    updateFreq
        F[1].erase(node.it)
        F[2].push_front(node_key)
        if(node_freq == min_freq)
            min_freq++

*/

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