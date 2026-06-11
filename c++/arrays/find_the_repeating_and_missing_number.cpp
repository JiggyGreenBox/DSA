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

vector<int> findMissingRepeatingNumbers_3(vector<int> nums) {
    int n = nums.size();
    int xorr = 0;    
    for(int i=0; i<n; i++) {
        xorr ^= nums[i]; // actual   a[0] .. a[n-1]
        xorr ^= (i+1);   // expected 1..n
    }

    // xorr = A^B, missing^repeat
    // since A^B != 0, they are distinct numbers
    // rightmost set bit is where they differ
    // using this, we can create 2 buckets
    // bucket1, bucket2, will have A^B, separated
    // next is to check which is the missing, and which is the repeat
    long long bit = xorr ^ (-xorr);

    int bucket1 = 0;
    int bucket2 = 0;
    for(int num : nums) {
        if(num & bit)
            bucket1 ^= num;
        else
            bucket2 ^= num;
    }

    for(int i=1; i<=n; i++) {
        if(i & bit)
            bucket1 ^= i;
        else
            bucket2 ^= i;
    }


    int count = 0;
    for(int x : nums) {
        if(x == bucket1)
            count++;
    }

    if(count == 2) {
        return {bucket1, bucket2}; // repeating, missing
    }

    return {bucket2, bucket1};
}

/*
S = sum of 1..n
S' = actual sum

A=missing
B=repeating

S' - B + A = S

(A - B) = (S - S') .. 1


A^2 - B^2 = S^2 - S'^2

(A-B)(A+B) = [loop for S^2] - [formula for S'^2]
    formula sum of square,
    n*(n+1)*(2n+1) / 6

(A+B) = val1
(A-B) = val2

A+B = (sum_n_sq - sum_act_sq)/




*/
vector<int> findMissingRepeatingNumbers_4(vector<int> nums) {

    // A = repeating number
    // B = missing number

    long long n = nums.size();
    
    long long actualSum = 0;
    long long actualSumSq = 0;

    for(long long x : nums) {
        actualSum   += x;
        actualSumSq += x * x;
    }

    long long expectedSum   = (n*(n+1)) / 2;
    long long expectedSumSq = (n*(n+1)*(2*n+1)) / 6;

    // let x = (A-B) = actS - expS
    // A2 - B2 = (A+B)(A-B)
    // let y = (A+B) = (actSq - expSq) / x

    // A = (x+y)/2
    // B = y - A

    long long x = actualSum - expectedSum;

    long long y = (actualSumSq - expectedSumSq) / x;

    long long A = (x + y) / 2;
    long long B =  y - A;

    return {(int)A, (int)B};
}

int main() {
    Solution sol;
    vector<int> v = {3, 5, 4, 1, 1};
    vector<int> ans = findMissingRepeatingNumbers_4(v);

    for(auto x : ans) {
        cout << x << " ";
    }
    cout << endl;
}
/*

1,2,3,4,5
1,1,3,4,5
xorAct^xorEx
= 1^1^1^2 = 1^2
we dont know fomr 1^2, which is missing and which is repeating
need to separate them


A ^ B contains bits where A and B differ.

Choose one such bit.

Use it to split numbers into two groups.

A and B must land in different groups.

All matching numbers still cancel inside their group.

The remaining values are A and B.
*/