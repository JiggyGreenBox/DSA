#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class Solution {
public:
    vector<int> findMissingRepeatingNumbers(vector<int> nums) {
        // for loop

        // cant use sum formula

        // extra space
        // unordered_map
        // count array
        //1, n
        int n = nums.size();
        vector<int> c(n+1, 0);

        for(auto x : nums){
            c[x]++;
        }

        for(auto x : c) cout << x << " ";
        cout << endl;

        vector<int> ans;
        int rep=0, miss=0;
        for(int i=1; i<=n; i++){
            cout << c[i] << " ";
            if(c[i] == 2) rep = i;
            if(c[i] == 0) miss = i;
        }
        cout << endl;

        return {rep,miss};
    }

    vector<int> findMissingRepeatingNumbers_2(vector<int> nums) {
        // for loop

        // cant use sum formula

        // extra space
        // unordered_map
        // count array
        //1, n
        int n = nums.size();
        unordered_map<int, int> m; //val, freq

        for(int i=1; i<=n; i++) m[i]++;        

        for(auto x : nums){
            m[x]--;
        }

        int rep=0,miss=0;
        for(auto& p : m){
            cout << p.first << " | " << p.second << endl;
            if(p.second==-1) rep = p.first;
            if(p.second==1) miss = p.first;
        }

        
        return {rep,miss};
    }
};

int main(){
    Solution sol;
    vector<int> v = {3, 5, 4, 1, 1};
    vector<int> ans = sol.findMissingRepeatingNumbers(v);

    for(auto x : ans) {
        cout << x << " ";
    }
    cout << endl;
}