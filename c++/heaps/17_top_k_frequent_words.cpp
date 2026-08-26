

/*


Top K Frequent Words
    [https://leetcode.com/problems/top-k-frequent-words/description/]

Given an array of strings words and an integer k, return the k most 
frequent strings.

Return the answer sorted by the frequency from highest to lowest. 
Sort the words with the same frequency by their lexicographical order.

 

Example 1:

    Input: words = ["i","love","leetcode","i","love","coding"], k = 2
    Output: ["i","love"]

    Explanation: "i" and "love" are the two most frequent words.
    Note that "i" comes before "love" due to a lower alphabetical order.

Example 2:

    Input: words = ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
    Output: ["the","is","sunny","day"]

    Explanation: "the", "is", "sunny" and "day" are the four most 
    frequent words, with the number of occurrence being 4, 3, 2 and 1 
    respectively.


*/


/*
Top K Frequent Words
    unordered_map<freq, string>

    k most
        max heap
            return top k

        min heap of size k
        pop k into vector
*/
#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;


// max heap version
vector<string> topKFrequent(vector<string>& words, int k) {

    unordered_map<string, int> mpp;

    for(string word : words) {
        mpp[word]++;
    }

    auto cmp = [](const auto &a, const auto &b) {
        if(a.second == b.second) {
            return a.first > b.first; // lower lex string desired
        }
        return a.second < b.second; // larger freq desired
    };

    priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> pq(cmp);

    for(auto &[word, freq] : mpp) {
        pq.push({word, freq});        
    }

    vector<string> ans;
    while(!pq.empty() && k--) {
        ans.push_back(pq.top().first);
        pq.pop();
    }
    return ans;
}

// min heap version
vector<string> topKFrequent(vector<string>& words, int k) {

    unordered_map<string, int> freq;

    for (const string &word : words)
        freq[word]++;

    auto cmp = [](const auto &a, const auto &b) {

        // Min Heap by frequency.
        if (a.second != b.second)
            return a.second > b.second;

        // For equal frequency,
        // lexicographically larger word has lower priority.
        return a.first < b.first;
    };

    priority_queue<
        pair<string,int>,
        vector<pair<string,int>>,
        decltype(cmp)
    > pq(cmp);

    for (auto &[word, count] : freq) {

        pq.push({word, count});

        if (pq.size() > k)
            pq.pop();
    }

    vector<string> ans;

    while (!pq.empty()) {
        ans.push_back(pq.top().first);
        pq.pop();
    }

    // min heap has lowest freq and largest lexi order?
    reverse(ans.begin(), ans.end());
    // so answer is in reverse

    return ans;
}

void print(const vector<string> & v) {
    cout << "[ ";
    for(auto s : v) cout << s << " ";
    cout << "]\n";
}

int main() {
    vector<string> words = {"i","love","leetcode","i","love","coding"};
    int k = 2;
    print(topKFrequent(words, k));

    words = {"the","day","is","sunny","the","the","the","sunny","is","is"};
    k = 4;
    print(topKFrequent(words, k));
    return 0;
}

/*
BEST:
    higher frequency
    smaller lexicographical order

WORST:
    lower frequency
    larger lexicographical order


Max heap — when you just want to extract Top K

    Want K best
        ↓
    Max heap
        ↓
    top = best
        ↓
    pop K times


Min heap — when you want to maintain Top K efficiently

    Want K best
        ↓
    Keep only K candidates
        ↓
    Need to remove worst
        ↓
    Min heap
        ↓
    top = worst
        ↓
    push candidate
    if size > K:
        pop
*/