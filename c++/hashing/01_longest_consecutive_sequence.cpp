#include <iostream>
#include <unordered_set>
#include <vector>


using namespace std;




// but your current code has a hidden inefficiency. Let me break it down
// the problem is you might recompute the same sequence many times.
// v = [1, 2, 3, 4, 5]
// So complexity can blow up toward O(n²) in the worst case.

// Only start counting when x is the start of a sequence, i.e. when x-1 is not in the set.
// if (!mset.count(x-1)) { // x is the start
int longest_consecutive_sequence_1(vector<int>& v){
    int ans = 0;

    unordered_set<int> mset;
    for(auto x : v) {
        mset.insert(x);
    }


    // loop thru the set or vector?
    // loop thru the vector and pop from the set
    // check for x+1, increment counter, erase from set
    // x could be last element/ mid element of set so dont erase if a x-1 element found
    // 5,4,3,2,1

    int max_sequence = 0;
    for(auto x : v){
        int seq_count = 1;
        // check if the next element exists
        // increment the sequnce count
        int elem = x;
        while(mset.count(elem+1)>0) {
            elem++;
            seq_count++;
        }

        max_sequence = max(max_sequence, seq_count);
    }


    return max_sequence;
}


int longest_consecutive_sequence_2(vector<int>& v){

    unordered_set<int> mset;
    for(auto x: v) mset.insert(x);
    int max_count = 0;

    // only start when we know the sequence is the start
    // that mean x-1 isnt in the sequence
    for( auto x :v ) {
        if(!mset.count(x-1)) {
            
            int elem = x;
            int seq_count = 1;

            while(mset.count(elem+1)){
                elem++;
                seq_count++;
            }
            max_count = max(max_count, seq_count);
        }
    }
    return max_count;
}
int main(){
    vector<int> v = {100, 4, 200, 1, 3, 101, 102,103,104};
    // int ans = longest_consecutive_sequence_1(v);
    int ans = longest_consecutive_sequence_2(v);
    cout << ans << endl;
    return 0;
}