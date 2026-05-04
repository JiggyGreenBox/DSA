# next permutation
1. find pivot
2. after pivot is found we process the suffix
3. find greatest suffix number compared to pivot
4. swap the pivot and next
5. reverse new suffix
---

## 1. find pivot
* from R to L find L<R
* from R to L find L<L+1
* ```
  [2, 1, 3]
    1<3 pivot  
    pivot = 1
  ```
* ```
  [2, 4, 1, 3]
    1<3 pivot  
    pivot = 1
  ```
* ```
  [1, 2, 5, 4, 3]
    4>3
    5>4
    2<5 pivot
  ```
---
## 2. after pivot is found we process the suffix
find the min element > pivot
```
[5, 4, 3]
3>2
4>2
5>2
    next=3
```
---
## 3. find greatest suffix number compared to pivot
---
## 4. swap the pivot and next
```
pivot=2
next=3
swap pivot and next_max
[1,2,5,4,3] -> [1,3,5,4,2]
```
---
## 5. reverse new suffix
```
pivot=2
next=3
suffix before swap [5,4,2]
suffix after swap [5,4,3]
reverse [3,4,5]
[1,3,5,4,2] -> [1,3,2,4,5]
```
---

Excellent question again 💡 — you’re now diving into how **`std::next_permutation`** is actually declared in the **C++ Standard Library** — that’s where things get beautifully generic.

Let’s look at the **canonical template declaration** from `<algorithm>`:

---

## 🧾 Template Declaration (from the C++ standard)

```cpp
template <class BidirectionalIterator>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last);
```

---

### ✅ Explanation of Each Part

| Part                                     | Meaning                                                                                                                                                                                                    |
| ---------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `template <class BidirectionalIterator>` | It works with *any* iterator that supports moving both forward and backward — like those from `vector`, `string`, `deque`, or even raw arrays.                                                             |
| `bool next_permutation(...)`             | Returns `true` if the function could rearrange the sequence into the next lexicographically greater permutation, and `false` if it was the last one (in which case it resets to the smallest permutation). |
| `BidirectionalIterator first`            | The iterator pointing to the **start** of the range.                                                                                                                                                       |
| `BidirectionalIterator last`             | The iterator pointing **one past the end** of the range.                                                                                                                                                   |

---

### 🧩 There’s also an Overload (with Comparator)

```cpp
template <class BidirectionalIterator, class Compare>
bool next_permutation(BidirectionalIterator first,
                      BidirectionalIterator last,
                      Compare comp);
```

This version lets you define your own custom comparison logic (e.g., for descending order or case-insensitive strings).

---

### 🧠 Conceptually, the STL Implementation Looks Like

```cpp
template <class BidirectionalIterator>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last) {
    if (first == last) return false;
    BidirectionalIterator i = last;
    if (first == --i) return false; // only one element

    while (true) {
        BidirectionalIterator i1, i2;

        i1 = i;
        if (*--i < *i1) {
            i2 = last;
            while (!(*i < *--i2))
                ; // find rightmost successor
            iter_swap(i, i2);
            reverse(i1, last);
            return true;
        }

        if (i == first) {
            reverse(first, last);
            return false;
        }
    }
}
```

That’s a simplified version of what’s actually inside `<algorithm>`.
Notice how:

* It uses **iterator-based logic** (no index arithmetic).
* Works for any bidirectional container — not just arrays or strings.
* Uses **`iter_swap`** and **`reverse`**, which themselves are generic.

---

### ⚙️ Example Usages

**With `vector<int>`**

```cpp
vector<int> v = {1, 2, 3};
next_permutation(v.begin(), v.end());
```

**With `string`**

```cpp
string s = "abc";
next_permutation(s.begin(), s.end());
```

**With custom comparator**

```cpp
next_permutation(v.begin(), v.end(), greater<int>());  // for descending order
```

---

Would you like me to show you the **reverse operation** (`std::prev_permutation`) and how it pairs perfectly with `next_permutation`?
