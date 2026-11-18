#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*
Fruit Into Baskets
    [https://leetcode.com/problems/fruit-into-baskets/description/]

You are visiting a farm that has a single row of fruit trees arranged 
from left to right. The trees are represented by an integer array 
fruits where fruits[i] is the type of fruit the ith tree produces.

You want to collect as much fruit as possible. However, the owner has 
some strict rules that you must follow:

You only have two baskets, and each basket can only hold a single 
type of fruit. There is no limit on the amount of fruit each basket 
can hold.
Starting from any tree of your choice, you must pick exactly one 
fruit from every tree (including the start tree) while moving to the 
right. The picked fruits must fit in one of your baskets.
Once you reach a tree with fruit that cannot fit in your baskets, you 
must stop.
Given the integer array fruits, return the maximum number of fruits 
you can pick.

 

Example 1:

    Input: fruits = [1,2,1]
    Output: 3
    Explanation: We can pick from all 3 trees.

Example 2:

    Input: fruits = [0,1,2,2]
    Output: 3
    Explanation: We can pick from trees [1,2,2].
    If we had started at the first tree, we would only pick from trees 
    [0,1].

Example 3:

    Input: fruits = [1,2,3,2,2]
    Output: 4
    Explanation: We can pick from trees [2,3,2,2].
    If we had started at the first tree, we would only pick from trees 
    [1,2].

*/

/*
we want max trees
    trees have types
        only 2 types are allowed
            the third type makes the collection invalid

    return max-trees, longest-subarray

longest-subarray with distinct nums == 2
    we need map
        type, count

    expand till map.size <= 2
    then remove from front
        till size <= 2

    track size when valid window
*/

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