The most common C++ variations of the XOR missing number problem use bit-masking (xorVal & -xorVal) to separate elements into two buckets or track bit frequencies modulo 3 when numbers appear more than twice.

1. One Missing AND One Duplicate Number (1 to n)

Problem: An array of size n contains numbers from 1 to n, except one number A appears twice and one number B is missing. Find both.
Logic:
1. XOR all array elements and numbers 1 to n. The result is xorVal = A ^ B.
2. Find the rightmost set bit (diffBit = xorVal & -xorVal), which represents a bit position where A and B differ.
3. Divide all array elements and numbers 1..n into two groups based on whether diffBit is set. XORing each group isolates A and B.
4. Do a quick pass through nums to check which one is the duplicate and which is missing.
```cpp
#include <vector>
using namespace std;

vector<int> findErrorNums(vector<int>& nums) {
    int n = nums.size();
    int xorVal = 0;

    // Step 1: Get A ^ B
    for (int i = 0; i < n; i++) {
        xorVal ^= nums[i] ^ (i + 1);
    }

    // Step 2: Isolate the rightmost set bit (use unsigned int to avoid UB on INT_MIN)
    unsigned int diffBit = (unsigned int)xorVal & -(unsigned int)xorVal;

    int bucket1 = 0, bucket2 = 0;

    // Step 3: Partition numbers into two buckets
    for (int i = 0; i < n; i++) {
        if (nums[i] & diffBit) bucket1 ^= nums[i];
        else bucket2 ^= nums[i];

        if ((i + 1) & diffBit) bucket1 ^= (i + 1);
        else bucket2 ^= (i + 1);
    }

    // Step 4: Identify which is duplicate and which is missing
    for (int num : nums) {
        if (num == bucket1) return {bucket1, bucket2}; // {duplicate, missing}
    }
    return {bucket2, bucket1};
}
```
Use code with caution.

2. Two Missing Numbers (1 to n)

Problem: An array of size n - 2 contains distinct numbers from 1 to n. Find the two missing numbers.
Logic: Identical to the bucket-splitting technique above, except you don't need Step 4 because neither number exists in the array.
```cpp
#include <vector>
using namespace std;

vector<int> twoMissingNumbers(vector<int>& nums, int n) {
    int xorVal = 0;

    for (int num : nums) xorVal ^= num;
    for (int i = 1; i <= n; i++) xorVal ^= i;

    unsigned int diffBit = (unsigned int)xorVal & -(unsigned int)xorVal;
    int missing1 = 0, missing2 = 0;

    for (int num : nums) {
        if (num & diffBit) missing1 ^= num;
        else missing2 ^= num;
    }
    for (int i = 1; i <= n; i++) {
        if (i & diffBit) missing1 ^= i;
        else missing2 ^= i;
    }

    return {missing1, missing2};
}
```
Use code with caution.

3. Single Non-Duplicate (Every Other Element Appears Twice)

Problem: Every element appears twice except for one. Find that single one (LeetCode 136).
Logic: Since there is no expected range (1..n), simply XOR all elements in the array together. Pairs cancel out to 0.
```cpp
#include <vector>
using namespace std;

int singleNumber(vector<int>& nums) {
    int result = 0;
    for (int num : nums) {
        result ^= num;
    }
    return result;
}
```
Use code with caution.

4. Two Non-Duplicates (Every Other Element Appears Twice)

Problem: Every element appears twice except for two elements that appear only once. Find both (LeetCode 260).
Logic: XOR the whole array to get A ^ B, split into two buckets using the rightmost set bit, and XOR each bucket.
```cpp
#include <vector>
using namespace std;

vector<int> singleNumberIII(vector<int>& nums) {
    unsigned int xorVal = 0;
    for (int num : nums) {
        xorVal ^= num;
    }

    unsigned int diffBit = xorVal & -xorVal;
    int a = 0, b = 0;

    for (int num : nums) {
        if (num & diffBit) a ^= num;
        else b ^= num;
    }
    return {a, b};
}
```
Use code with caution.

5. Single Non-Duplicate (Every Other Element Appears Three Times)

Problem: Every element appears three times except for one, which appears once (LeetCode 137).
Logic: Standard XOR cancels pairs, not triplets. Instead, simulate a base-3 counter across all 32 bits using two bitmasks (ones and twos). When a bit appears a 3rd time, it resets to 0 in both variables.
```cpp
#include <vector>
using namespace std;

int singleNumberII(vector<int>& nums) {
    int ones = 0, twos = 0;
    for (int num : nums) {
        ones = (ones ^ num) & ~twos;
        twos = (twos ^ num) & ~ones;
    }
    return ones;
}
```
Use code with caution.

Quick Summary of Patterns


Problem Constraint	Core Bitwise Trick	Time / Space
1 missing / 1 unique (pairs cancel)	Simple XOR accumulation (res ^= x)	O(n) / O(1)
2 missing / 2 unique / 1 missing + 1 dup	Rightmost set bit (x & -x) to split into 2 buckets	O(n) / O(1)
1 unique (triplets cancel)	State machine bitmasks (ones and twos)	O(n) / O(1)

If you'd like to dive deeper into any of these, let me know:
• A step-by-step bit trace (e.g., how ones and twos work or how x & -x isolates a bit)
• LeetCode problem links/numbers to practice these exact patterns
• Non-XOR alternatives (like Cyclic Sort) for when there are k missing numbers
I can walk you through the trace or provide the code.
