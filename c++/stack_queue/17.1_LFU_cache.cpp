#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

/*

attempt 1 works without min freq eviction
    this works but i dont know how i can find the min key in O(1) time.

chatgpt - 
    min_freq only changes in TWO situations
        1️⃣ When you INSERT a new key
        2️⃣ When you INCREMENT a key’s frequency

    1️⃣ When you INSERT a new key
        min_freq = 1
    
    2️⃣ When you INCREMENT a key’s frequency
        freq = f  →  freq = f+1
*/

class LFUcache {
private:
    //            key     count, it-to-dll
    unordered_map<int, pair<int, list<pair<int,int>>::iterator>> key_mpp;
    //          count, list<key,val>
    unordered_map<int, list<pair<int,int>>> freq_mpp;
    int cap;
    int size;
    int min_freq;
public:
    LFUcache(int capacity) {
        cap = capacity;
        size = 0;
        min_freq = 1;
    }

    int get(int key) {
        // 1. update
        if(key_mpp.find(key) == key_mpp.end()) return -1;
        
        auto &pair = key_mpp[key]; // pair <count, it>
        int old_count = pair.first;
        auto it = pair.second;        
        int new_count = old_count+1;
        pair.first = new_count;
        

        // move based on freq
        // see if the list exists        
        freq_mpp[new_count].splice(freq_mpp[new_count].begin(), freq_mpp[old_count], it);

        if(freq_mpp[old_count].size() == 0){
            if(old_count == min_freq) min_freq = new_count;
            freq_mpp.erase(old_count);
        } 
        return it->second;
    }

    void put(int key, int value) {
        // 1a. update
        if(key_mpp.find(key) != key_mpp.end()) {

            auto &pair = key_mpp[key]; // pair <count, it>
            int old_count = pair.first;
            auto it = pair.second;        
            int new_count = old_count+1;
            pair.first = new_count;

            // move based on freq            
            freq_mpp[new_count].splice(freq_mpp[new_count].begin(), freq_mpp[old_count], it);

            if(freq_mpp[old_count].size() == 0) {
                if(old_count == min_freq) min_freq = new_count;
                freq_mpp.erase(old_count);
            } 
            it->second = value; // update new value            
            
            return;
        }
        // 1b. insert
        
        // 2. check capacity
        if(size == cap) {
            
            int lfu_key = freq_mpp[min_freq].back().first;

            cout << "evict :" << lfu_key << endl;

            freq_mpp[min_freq].pop_back();
            if(freq_mpp[min_freq].size() == 0) freq_mpp.erase(min_freq);

            key_mpp.erase(lfu_key);
            size--;
        }
        // 3. insert new pair        
        freq_mpp[1].push_front({key, value}); // add pair to end of list        
        key_mpp[key] = {1, freq_mpp[1].begin()}; // insert pair<count,it>
        min_freq = 1;
        size++;
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