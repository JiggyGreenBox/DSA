Good question 👍 — this is a **very common DSA pattern** (used in problems like “Remove Duplicates from Sorted Array”, “Two Sum II”, “3Sum”, etc.).

Let’s go over **three typical cases** and how to skip duplicates in each.

---

## 🧩 Case 1: While iterating (e.g., `while` loop)

You often want to skip over repeated elements.

### Example:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> arr = {1, 1, 2, 2, 2, 3, 4, 4};
    int n = arr.size();
    
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " "; // process element

        // Skip all duplicates of arr[i]
        while (i + 1 < n && arr[i] == arr[i + 1])
            i++;
    }

    return 0;
}
```

### Output:

```
1 2 3 4
```

✅ Only unique elements are processed once.

---

## 🧮 Case 2: Two-pointer pattern (e.g., “Remove duplicates in-place”)

If you want to **modify the array** to remove duplicates:

```cpp
#include <bits/stdc++.h>
using namespace std;

int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int j = 0; // points to the last unique element
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] != nums[j]) {
            j++;
            nums[j] = nums[i];
        }
    }
    return j + 1; // length of unique part
}

int main() {
    vector<int> nums = {1, 1, 2, 2, 3, 4, 4};
    int len = removeDuplicates(nums);
    for (int i = 0; i < len; i++) cout << nums[i] << " ";
}
```

### Output:

```
1 2 3 4
```

---

## 🎯 Case 3: Skipping duplicates in problems like 3Sum

When using multiple loops or recursion, you skip duplicates **after processing** a value.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> nums = {-1, 0, 0, 1, 1, 2};
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        // Skip duplicate 'i'
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        int l = i + 1, r = n - 1;
        while (l < r) {
            int sum = nums[i] + nums[l] + nums[r];
            if (sum == 0) {
                cout << nums[i] << "," << nums[l] << "," << nums[r] << endl;
                
                // Skip duplicates for l and r
                int leftVal = nums[l], rightVal = nums[r];
                while (l < r && nums[l] == leftVal) l++;
                while (l < r && nums[r] == rightVal) r--;
            }
            else if (sum < 0) l++;
            else r--;
        }
    }
}
```

---

## ⚙️ Summary Table

| Goal                             | How to skip                                                    |
| -------------------------------- | -------------------------------------------------------------- |
| Skip in a loop                   | `while (i + 1 < n && arr[i] == arr[i + 1]) i++;`               |
| Skip in nested loops (like 3Sum) | After processing, `while (l < r && nums[l] == lastValue) l++;` |
| Remove duplicates in-place       | Use two pointers (`i`, `j`)                                    |

---

Would you like me to show how to **return a new vector** that only contains unique elements (instead of modifying in-place)?
---
Exactly 👏 — you nailed the **two main duplicate-skipping strategies** in sorted arrays.
Let’s formalize them so you can remember and apply them easily in DSA problems 👇

---

## 🧠 1️⃣ **Look-Back Technique** (Skip *before* processing)

### Pattern:

```cpp
if (i > 0 && nums[i] == nums[i - 1]) continue;
```

### 📌 When to use:

* When iterating **forward** and you only want to **process the first unique element** in a block of duplicates.
* Common in problems like:

  * `3Sum`, `4Sum`, or `Subset` generation
  * “Find all unique combinations” problems

### 🧩 Example:

```cpp
for (int i = 0; i < n; i++) {
    if (i > 0 && nums[i] == nums[i - 1]) continue; // look-back
    cout << nums[i] << " "; // process the first unique value
}
```

✅ Processes the **first unique element** in each group.
⛔ Skips subsequent duplicates.

---

## 🧠 2️⃣ **Jump-Ahead Technique** (Skip *after* processing)

### Pattern:

```cpp
while (i + 1 < n && nums[i] == nums[i + 1]) i++;
```

### 📌 When to use:

* When you’ve already processed an element and now want to **skip ahead to the next new value**.
* Common in:

  * Deduplication loops
  * Merging sorted arrays
  * Frequency counting

### 🧩 Example:

```cpp
for (int i = 0; i < n; i++) {
    cout << nums[i] << " "; // process current
    while (i + 1 < n && nums[i] == nums[i + 1]) i++; // jump-ahead
}
```

✅ Processes the **last unique element** in each group.
⛔ Skips over all duplicates following it.

---

## ⚖️ Quick Comparison

| Technique      | Where it happens    | Keeps                  | Skips              |
| -------------- | ------------------- | ---------------------- | ------------------ |
| **Look-Back**  | *Before* processing | First element of block | Later duplicates   |
| **Jump-Ahead** | *After* processing  | Last element of block  | Earlier duplicates |

---

## 💡 Tip:

You can **combine** both patterns depending on your problem logic.
Example – in `3Sum`, you use:

* **Look-Back** for the outer loop (`i > 0 && nums[i] == nums[i-1]`)
* **Jump-Ahead** for inner pointers (`while (l < r && nums[l] == leftVal) l++;`)

---

Would you like me to show a side-by-side visual of both on the same array (`{1,1,2,2,3}`) so you can clearly see which elements get processed in each case?
---
Perfect 😎 — let’s visualize this clearly with the same sorted array:

```
nums = {1, 1, 2, 2, 3}
```

We’ll run both approaches step-by-step so you can **see which elements are processed**.

---

## 🧩 **Case 1: Look-Back Technique**

```cpp
for (int i = 0; i < n; i++) {
    if (i > 0 && nums[i] == nums[i - 1]) continue; // skip duplicates
    cout << nums[i] << " ";
}
```

### 🔍 Step-by-step:

| i | nums[i] | Condition (`nums[i] == nums[i-1]`) | Action     |
| - | ------- | ---------------------------------- | ---------- |
| 0 | 1       | false                              | ✅ print(1) |
| 1 | 1       | true                               | ❌ skip     |
| 2 | 2       | false                              | ✅ print(2) |
| 3 | 2       | true                               | ❌ skip     |
| 4 | 3       | false                              | ✅ print(3) |

### 🟩 Output:

```
1 2 3
```

👉 **Processes the first element** of each block of duplicates.

---

## 🧩 **Case 2: Jump-Ahead Technique**

```cpp
for (int i = 0; i < n; i++) {
    cout << nums[i] << " "; // process current
    while (i + 1 < n && nums[i] == nums[i + 1]) i++; // skip ahead
}
```

### 🔍 Step-by-step:

| i | nums[i] | Action     | Jump-to                        |
| - | ------- | ---------- | ------------------------------ |
| 0 | 1       | ✅ print(1) | jumps to i=1 → skips duplicate |
| 2 | 2       | ✅ print(2) | jumps to i=3 → skips duplicate |
| 4 | 3       | ✅ print(3) | end                            |

### 🟩 Output:

```
1 2 3
```

👉 **Processes the last element** of each block (but since printing is before skipping, it looks the same here).

---

## 🎯 Key Concept Visualization

| Block   | Values | Look-Back prints | Jump-Ahead prints         |
| ------- | ------ | ---------------- | ------------------------- |
| Block 1 | 1, 1   | first → `1`      | first (before jump) → `1` |
| Block 2 | 2, 2   | first → `2`      | first (before jump) → `2` |
| Block 3 | 3      | `3`              | `3`                       |

---

## ⚙️ The Subtle Difference

They both **produce the same result** here, but conceptually:

* **Look-Back** ensures you **don’t enter** duplicate processing at all.
  → Good when *you only want the first appearance.*

* **Jump-Ahead** lets you **finish processing**, then skips forward.
  → Good when *you need to handle all identical values before skipping.*

---

Would you like me to show an example where **Look-Back and Jump-Ahead produce *different* outputs**, so you can see their behavioral difference more clearly (like when processing or counting within duplicates)?
---
Awesome 😎 — this is where things really click!
Let’s take a slightly richer example so you can **see how Look-Back and Jump-Ahead behave differently** when there’s *per-group processing*, not just simple printing.

---

## 🧩 Array

```
nums = {1, 1, 2, 2, 2, 3, 4, 4}
```

We’ll imagine we want to **count how many times each number appears**.

---

## 🧠 Case 1: **Look-Back (process first of block only)**

```cpp
for (int i = 0; i < n; i++) {
    if (i > 0 && nums[i] == nums[i - 1]) continue;  // skip duplicates

    int count = 1;
    int j = i + 1;
    while (j < n && nums[j] == nums[i]) {
        count++;
        j++;
    }
    cout << nums[i] << " occurs " << count << " times\n";
}
```

### 🔍 Step-by-step

| i | nums[i] | Skipped? | Counted elements | Output           |
| - | ------- | -------- | ---------------- | ---------------- |
| 0 | 1       | no       | {1,1}            | 1 occurs 2 times |
| 1 | 1       | yes      | —                | —                |
| 2 | 2       | no       | {2,2,2}          | 2 occurs 3 times |
| 3 | 2       | yes      | —                | —                |
| 4 | 2       | yes      | —                | —                |
| 5 | 3       | no       | {3}              | 3 occurs 1 time  |
| 6 | 4       | no       | {4,4}            | 4 occurs 2 times |
| 7 | 4       | yes      | —                | —                |

### 🟩 Output

```
1 occurs 2 times
2 occurs 3 times
3 occurs 1 time
4 occurs 2 times
```

✅ **Look-Back** triggers *once per unique value* (on the first appearance).
It’s ideal for **group-based operations** (counting, combining, grouping).

---

## 🧠 Case 2: **Jump-Ahead (skip after processing)**

```cpp
for (int i = 0; i < n; i++) {
    int count = 1;
    while (i + 1 < n && nums[i] == nums[i + 1]) {
        count++;
        i++;  // jump ahead through duplicates
    }
    cout << nums[i] << " occurs " << count << " times\n";
}
```

### 🔍 Step-by-step

| i before | nums[i] | Skips forward | Count | Output           |
| -------- | ------- | ------------- | ----- | ---------------- |
| 0        | 1       | to i=1        | 2     | 1 occurs 2 times |
| 2        | 2       | to i=4        | 3     | 2 occurs 3 times |
| 5        | 3       | no jump       | 1     | 3 occurs 1 time  |
| 6        | 4       | to i=7        | 2     | 4 occurs 2 times |

### 🟩 Output

```
1 occurs 2 times
2 occurs 3 times
3 occurs 1 time
4 occurs 2 times
```

✅ **Jump-Ahead** also processes *once per block*, but it does so **after processing** the duplicates.
It’s ideal for **linear scans** where you want to consume duplicates in one go.

---

## ⚖️ Side-by-Side Comparison

| Concept          | Look-Back                             | Jump-Ahead                              |
| ---------------- | ------------------------------------- | --------------------------------------- |
| Skip timing      | Before processing                     | After processing                        |
| Triggers on      | First unique element                  | Last duplicate element                  |
| Ideal for        | Group aggregation, 3Sum, backtracking | One-pass scans, deduplication, counting |
| Visited elements | i skips inside the group              | i jumps past duplicates                 |

---

## 💡 Mnemonic

> 🧭 “**Look-Back** avoids duplicates ahead.”
> 🏃 “**Jump-Ahead** runs past duplicates behind.”

---

Would you like a **diagrammatic timeline** (with arrows showing how `i` moves) to visualize this difference between the two loops on the same array?
