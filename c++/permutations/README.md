Perfect 🔥 — here’s your **step-by-step roadmap to master permutations in DSA using C++**, from beginner → advanced.
It’s structured to **build intuition**, **practice coding patterns**, and **prepare for interviews**.

---

## 🧭 STAGE 1: Foundation (Understand and Implement)

### 🧩 **Problem 1: Generate All Permutations (Basic)**

**Goal:** Implement recursion & backtracking logic.

#### 👉 Example

```
Input: [1, 2, 3]
Output:
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
```

#### 🧠 Hint

* Use recursion with a `for` loop and swapping.
* When `start == nums.size()`, print.

#### 🧰 Template

```cpp
void permute(vector<int>& nums, int start) {
    if (start == nums.size()) {
        for (int n : nums) cout << n << " ";
        cout << endl;
        return;
    }
    for (int i = start; i < nums.size(); i++) {
        swap(nums[start], nums[i]);
        permute(nums, start + 1);
        swap(nums[start], nums[i]);
    }
}
```

🧑‍💻 **Practice:** [LeetCode #46 - Permutations](https://leetcode.com/problems/permutations/)

---

## ⚙️ STAGE 2: Handle Duplicates (Intermediate)

### 🧩 **Problem 2: Unique Permutations**

**Goal:** Skip duplicate elements (important for real interviews).

#### 👉 Example

```
Input: [1, 1, 2]
Output:
1 1 2
1 2 1
2 1 1
```

#### 🧠 Hint

* Sort input first.
* Skip duplicate elements at the same recursion depth.

#### 🧰 Template

```cpp
void permuteUnique(vector<int>& nums, int start) {
    if (start == nums.size()) {
        for (int n : nums) cout << n << " ";
        cout << endl;
        return;
    }
    unordered_set<int> used;
    for (int i = start; i < nums.size(); i++) {
        if (used.count(nums[i])) continue;
        used.insert(nums[i]);
        swap(nums[start], nums[i]);
        permuteUnique(nums, start + 1);
        swap(nums[start], nums[i]);
    }
}
```

🧑‍💻 **Practice:** [LeetCode #47 - Permutations II](https://leetcode.com/problems/permutations-ii/)

---

## 🧮 STAGE 3: Lexicographic Logic (STL)

### 🧩 **Problem 3: Next Permutation**

**Goal:** Learn how `next_permutation` works internally.

#### 👉 Example

```
Input: [1, 2, 3]
Output: [1, 3, 2]
```

#### 🧠 Hint

* Find the first decreasing element from the right.
* Swap it with the next bigger element.
* Reverse the suffix.

#### 🧰 Template

```cpp
void nextPermutation(vector<int>& nums) {
    int i = nums.size() - 2;
    while (i >= 0 && nums[i] >= nums[i+1]) i--;
    if (i >= 0) {
        int j = nums.size() - 1;
        while (nums[j] <= nums[i]) j--;
        swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end());
}
```

🧑‍💻 **Practice:** [LeetCode #31 - Next Permutation](https://leetcode.com/problems/next-permutation/)

---

## 🔢 STAGE 4: Find K-th Permutation (Math + Recursion)

### 🧩 **Problem 4: K-th Permutation Sequence**

**Goal:** Generate the K-th permutation **without generating all**.

#### 👉 Example

```
Input: n = 3, k = 3
Output: "213"
```

#### 🧠 Hint

* Use factorial indexing.
* Think of each position independently.

#### 🧰 Template

```cpp
string getPermutation(int n, int k) {
    vector<int> nums;
    for (int i = 1; i <= n; i++) nums.push_back(i);
    vector<int> fact(n, 1);
    for (int i = 1; i < n; i++) fact[i] = fact[i-1] * i;

    k--; // 0-based index
    string ans = "";
    for (int i = n; i >= 1; i--) {
        int idx = k / fact[i-1];
        ans += to_string(nums[idx]);
        nums.erase(nums.begin() + idx);
        k %= fact[i-1];
    }
    return ans;
}
```

🧑‍💻 **Practice:** [LeetCode #60 - Permutation Sequence](https://leetcode.com/problems/permutation-sequence/)

---

## 🧠 STAGE 5: Applied Permutation Logic (Hard / Real Use)

### 🧩 **Problem 5: Permutations with Constraints**

**Goal:** Add real-world conditions.

#### Example:

> Generate permutations of `[1,2,3,4]` such that no two consecutive numbers differ by 1.

#### 🧠 Hint

* Use recursive backtracking.
* Skip placing elements that break the condition.

#### 🧰 Template

```cpp
void constrainedPermute(vector<int>& nums, int start) {
    if (start == nums.size()) {
        for (int n : nums) cout << n << " ";
        cout << endl;
        return;
    }
    for (int i = start; i < nums.size(); i++) {
        if (start > 0 && abs(nums[start-1] - nums[i]) == 1) continue;
        swap(nums[start], nums[i]);
        constrainedPermute(nums, start + 1);
        swap(nums[start], nums[i]);
    }
}
```

This trains you to handle **custom permutation constraints**, common in advanced backtracking.

---

## 🧩 BONUS: Practice Pattern Summary

| Level           | Concept                       | Problem      |
| --------------- | ----------------------------- | ------------ |
| 🟢 Beginner     | Basic recursion + swapping    | LeetCode #46 |
| 🟡 Intermediate | Skip duplicates               | LeetCode #47 |
| 🟡 Intermediate | Lexicographic order           | LeetCode #31 |
| 🟠 Advanced     | Factorial math                | LeetCode #60 |
| 🔴 Expert       | Constraint-based permutations | Custom       |

---

## 📘 Recommended Next Topics

Once you’ve mastered permutations:

1. ✅ **Combinations (nCr patterns)**
2. ✅ **Subsets / Power set**
3. ✅ **Backtracking problems (N-Queens, Sudoku, etc.)**
4. ✅ **String anagrams & permutations**

---

Would you like me to make a **C++ practice sheet (code templates + sample I/O)** for these 5 problems in one file (so you can run and test all in a single `.cpp`)?


04_permutation_sequence.cpp