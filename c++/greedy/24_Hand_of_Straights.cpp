/*

Hand of Straights
Alice has some number of cards and she wants to rearrange the cards 
into groups so that each group is of size groupSize, and consists of 
groupSize consecutive cards.

Given an integer array hand where hand[i] is the value written on the 
ith card and an integer groupSize, return true if she can rearrange 
the cards, or false otherwise.

 

Example 1:

    Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
    Output: true
    Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]

Example 2:

    Input: hand = [1,2,3,4,5], groupSize = 4
    Output: false
    Explanation: Alice's hand can not be rearranged into groups of 4.

*/

/*
observations
    we need array size to be % groupSize
    if we are given groupsize 5
        its ok to be given 5,10,15,100 cards
        it might be possible

        but 12 cards wont work

    if n % groupSize != 0 
        return false

    sort numbers
        pick smallest

        for groupSize
            find next element
                if not found return false

    return true


    now the problems become efficient search
        also we can reuse some elements
        1 2 3
            2 3 4

        if we have 2x2, and 3x3

        we need to keep a track of frequencies
        when consumed reduce the frequency

    we will use a map of element, count

    map<int,int> mpp                
*/
#include <iostream>
#include <map>
#include <vector>
using namespace std;
int main() {

    int groupSize = 5;
    vector<int> nums;
    map<int, int> freq;
    
    for(auto x: nums)
        freq[x]++;
    
    for (auto &[card, count] : freq) {

        while (freq[card] > 0) {

            for (int x = card; x < card + groupSize; x++) {

                if (freq[x] == 0)
                    return false;

                freq[x]--;
            }
        }
    }
    return true;
}