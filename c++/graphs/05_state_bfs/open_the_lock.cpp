

/*
752. Open the Lock
0000
0202

observation

for each char we can move up or down
    int char++
        if char == 10
            char = 0

    char--
        if char == -1
            char = 9

for each string 0000
    we can move 4 wheels
        up or down

    8 combinations


we can transform 0000 to 0202
    one char at a time
        each char change can be a node of a graph
        we want to reach target as soon as possible

    now if we encounter a deadlock 
        we dont continue the BFS for that combination
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

vector<string> generateCombos(string &s) {

    // we want 8 combinations for each s
    // 4 wheels
    // each goes up and down

    vector<string> combinations;

    for(int i=0; i<4; i++) {

        int og = s[i] - '0';

        // wheel up
        int up = og+1;
        if(up == 10)
            up = 0;

        s[i] = up + '0';
        combinations.push_back(s);

        // wheel down
        int down = og-1;
        if(down == -1)
            down = 9;
        s[i] = down + '0';
        combinations.push_back(s);

        // reset
        s[i] = og + '0';
        
    }
    return combinations;
}

int openLock(vector<string>& deadends, string target) {

    unordered_set<string> dict(deadends.begin(), deadends.end());

    if(dict.count("0000"))
        return -1;

    if(target == "0000")
        return 0;


    unordered_set<string> visited;
    visited.insert("0000");

    queue<pair<string, int>> q; // curr, level
    q.push({"0000", 0});

    while(!q.empty()) {
        auto &[curr, level] = q.front();
        q.pop();

        if(curr == target)
            return level;

        for(auto next : generateCombos(curr)) {

            if(dict.count(next) || visited.count(next))
                continue;
        
            visited.insert(next);
            q.push({next, level + 1});
        }
    }
    return -1;
}

int main() {
    vector<string> deadends = {"0201","0101","0102","1212","2002"};
    string target = "0202";
    cout << openLock(deadends, target) << endl; //Output: 6

    deadends = {"8888"}; target = "0009";
    cout << openLock(deadends, target) << endl; //Output: 1

    deadends = {"8887","8889","8878","8898","8788","8988","7888","9888"}, target = "8888";
    cout << openLock(deadends, target) << endl; //Output: -11

    return 0;
}

/*
time 
    for each transformation
        we have 8 choices

    for each digit we have 0-9
        10 choices

    10^4 combinations to check in total

    we might

space
    deadends
    visited 10^4
    queue size 10^4


*/