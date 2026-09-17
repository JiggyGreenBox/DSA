#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;


// n2 time
// n space
int totalFruits_bruteforce(vector<int>& fruits) {
    int n = fruits.size();
    int total_fruits = 0;

    for(int i=0; i<n; i++) {

        unordered_set<int> mset;

        for(int j=i; j<n; j++) {

            mset.insert(fruits[j]);
            
            if(mset.size() > 2) 
                break;

            total_fruits = max(total_fruits,j-i+1);
        }
    }
    return total_fruits;
}



int totalFruits_bucket_array(const vector<int>& fruits) {
    int n = fruits.size();

    int last_f1 = -1;
    int last_f2 = -1;
    int left = 0;
    int max_fruits = 0;

    // expand window
    for(int right=0; right<n; right++) {
        if((last_f1 == -1) || (fruits[right] == fruits[last_f1])) {            
            last_f1 = right;
        }
        else if((last_f2 == -1) || (fruits[right] == fruits[last_f2])) {            
            last_f2 = right;
        }
        else {
            // replace lower fruit
            // recalculate max_fruits
            left = min(last_f1, last_f2) + 1;

            if(last_f1 < last_f2) last_f1 = right;
            else last_f2 = right;
        }
        max_fruits = max(max_fruits, right-left+1);
    }
    return max_fruits;
}

int totalFruits(const vector<int>& fruits) {
    
    unordered_map<int, int> mpp;
    int left = 0;
    int max_fruits = 0;

    for(int right=0; right<fruits.size(); right++) {
        // add fruit to window, expand
        mpp[fruits[right]]++;

        // disallow window having more than 3 fruits
        while(mpp.size() > 2){

            mpp[fruits[left]]--;

            if(mpp[fruits[left]] == 0)
                mpp.erase(fruits[left]);

            left++;
        }

        max_fruits = max(max_fruits, right - left + 1);
    }
    return max_fruits;
}

int total_fruits_gpt_cannonical(const vector<int>& fruits) {

    int currentWindow = 0, maxWindow = 0;
    int lastFruit = 0, secondLastFruit = 0; 
    int lastFruitCount=0;   

    for(int f : fruits){
        if(f == lastFruit || f == secondLastFruit) {
            currentWindow++;
        }
        else{
            currentWindow = lastFruitCount + 1; // can be replaced by 2? NO, need to trim. 2 would discard earlier valid counts

            // fruits = [1, 2, 2, 2, 3]
            // Step-by-step when 3 appears:
            //     lastFruit = 2
            //     lastFruitCount = 3

        }

        if(f == lastFruit) {
            lastFruitCount++; // keep a count of continuous fruits [...2,2,2,2,...]
        }
        else{
            lastFruitCount = 1; // discard count when fruits flips [1,2,1,2,1,2,1,2], earlier counts dont matter
            secondLastFruit = lastFruit;
            lastFruit = f;            
        }

        maxWindow = max(maxWindow, currentWindow);
    }
    return maxWindow;
}




int main() {
    // vector<int> fruits = {1, 2, 1};
    // cout << totalFruits_bucket_array({1, 2, 1}) << endl;
    cout << total_fruits_gpt_cannonical({1, 2, 3, 2, 2}) << endl;
    return 0;
}