#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class Solution {
public:
    vector<int> findMissingRepeatingNumbers(vector<int> nums) {        
        int n = nums.size();
        vector<int> count(n+1, 0);

        for(auto x : nums){
            count[x]++;
        }        
        

        int repeating = 0;
        int missing = 0;

        for(int i=1; i<=n; i++) {    

            if(count[i] == 2) 
                repeating = i;

            if(count[i] == 0) 
                missing = i;
        }
        cout << endl;

        return {repeating, missing};
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

    // long long bit = xorr ^ (-xorr);
    int bit = xorr & -xorr; // rightmost set bit

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
    S = 1 + 2 + ... + n

A = missing
B = repeating

S' = actual sum
    S' = S - B + A

S' - S  = A - B

x = A - B

---

Expected:
    1² + 2² + ... + n²

    actualSumSq = expectedSumSq + A² - B²

actualSumSq - expectedSumSq = A² - B²

A² - B² = (A-B)(A+B)
    and (A-B) = x

A+B = (actualSumSq - expectedSumSq) / x

y = A+B

A-B = x
A+B = y

A = (x+y)/2
B = y - A

Time:  O(n)
Space: O(1)
    remember to use long long



*/
vector<int> findMissingRepeatingNumbers_2(vector<int> nums) {

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
    vector<int> ans = findMissingRepeatingNumbers_2(v);

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

/*
DERIVATION
nums = [3, 5, 4, 1, 1]

Expected:  [1, 2, 3, 4, 5]
Actual:    [1, 1, 3, 4, 5]

repeating = 1
missing   = 2

----

A = repeating
B = missing

S = 1+2+3+4+5+n
S` = S + B - A

S-S` = A - B
x = A - B

expSumSq = 1^2 + 2^2 + 3^3 + ..n^2
actualSumSq = expSumSq - A^2 + B^2

A^2 - B^2 = expSumSq - actualSumSq
(A-B)(A+B) = expSumSq - actualSumSq

A+B = expSumSq - actualSumSq / x

y = expSumSq - actualSumSq / x

A+B = x
A-B = y
2A = x+y
A = (x+y)/2
B = y - A


sum of first n nums:
    n(n+1) / 2

sum of squares of first n nums:
    [n(n+1) * (2*n+1)] / 6
*/