Excellent question — this is one of the **most confusing but most important** distinctions in binary search patterns.
Let’s break this down clearly and **once and for all** fix this confusion. 🧠💡

---

## 🔹 The Root Cause of Confusion

There are **two “styles”** of binary search loops:

| Style                           | `high` initialized as | Loop condition     | Common use                         |
| ------------------------------- | --------------------- | ------------------ | ---------------------------------- |
| **[lo, hi)** half-open interval | `n`                   | `while (lo < hi)`  | `lower_bound`, `upper_bound`       |
| **[lo, hi]** closed interval    | `n - 1`               | `while (lo <= hi)` | classic binary search, floor, ceil |

The confusion comes from **mixing** these two.
Let’s decode when each is used 👇

---

## 🧭 1. Half-open Interval — `[low, high)`

✅ Used in **STL functions** (`lower_bound`, `upper_bound`).

### Rules:

* Initialize:

  ```cpp
  int low = 0, high = n;  // notice: high = n (not n-1)
  ```
* Loop:

  ```cpp
  while (low < high)
  ```
* `mid` formula is normal:

  ```cpp
  int mid = low + (high - low) / 2;
  ```
* If condition true → move `high = mid`
* Else → move `low = mid + 1`

The key:
👉 `high` is *exclusive* (one past the last valid index).
So `nums[high]` is **never accessed** — that’s why this is **safe**.

---

### Example – `lower_bound`

Find **first index ≥ x**

```cpp
int lower_bound(vector<int>& a, int x) {
    int low = 0, high = a.size();
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (a[mid] < x)
            low = mid + 1;
        else
            high = mid;
    }
    return low;  // or high (same)
}
```

✅ `high = n`
✅ Loop is `low < high`
✅ We never access `a[n]`

---

### Example – `upper_bound`

Find **first index > x**

```cpp
int upper_bound(vector<int>& a, int x) {
    int low = 0, high = a.size();
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (a[mid] <= x)
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}
```

---

## 🧭 2. Closed Interval — `[low, high]`

✅ Used in **manual** binary search, **floor**, **ceil**, **search** for exact element.

### Rules:

* Initialize:

  ```cpp
  int low = 0, high = n - 1;
  ```
* Loop:

  ```cpp
  while (low <= high)
  ```
* When you move:

  * `if (condition)` → `high = mid - 1`
  * else → `low = mid + 1`

The key:
👉 `high` is *inclusive* (last valid index).
So you can access `nums[high]`.

---

### Example – Classic Binary Search

Find if `x` exists:

```cpp
int binary_search(vector<int>& a, int x) {
    int low = 0, high = a.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == x) return mid;
        if (a[mid] < x) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
```

---

### Example – Floor (greatest ≤ x)

```cpp
int floor_value(vector<int>& a, int x) {
    int low = 0, high = a.size() - 1, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] <= x) {
            ans = a[mid];
            low = mid + 1;
        } else high = mid - 1;
    }
    return ans;
}
```

---

### Example – Ceil (smallest ≥ x)

```cpp
int ceil_value(vector<int>& a, int x) {
    int low = 0, high = a.size() - 1, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] >= x) {
            ans = a[mid];
            high = mid - 1;
        } else low = mid + 1;
    }
    return ans;
}
```

---

## 🧠 Memory Trick: “Inclusive → n-1, Exclusive → n”

| If your interval is...    | You set high to... | You loop while... | Used in                           |
| ------------------------- | ------------------ | ----------------- | --------------------------------- |
| `[low, high]` (inclusive) | `n - 1`            | `low <= high`     | manual binary search, floor, ceil |
| `[low, high)` (exclusive) | `n`                | `low < high`      | STL lower_bound, upper_bound      |

---

## 🧩 Summary Cheat Sheet

| Operation              | Range    | Init      | Loop     | Return      | Typical Use |
| ---------------------- | -------- | --------- | -------- | ----------- | ----------- |
| **Binary search** (==) | `[l, r]` | `r = n-1` | `l <= r` | exact match | search      |
| **Lower bound (≥x)**   | `[l, r)` | `r = n`   | `l < r`  | `l`         | STL style   |
| **Upper bound (>x)**   | `[l, r)` | `r = n`   | `l < r`  | `l`         | STL style   |
| **Floor (≤x)**         | `[l, r]` | `r = n-1` | `l <= r` | `ans`       | manual      |
| **Ceil (≥x)**          | `[l, r]` | `r = n-1` | `l <= r` | `ans`       | manual      |

---

Would you like me to draw a **visual diagram** of how `low` and `high` move differently in these two variants? (It makes it much easier to memorize.)


| Operation          | Range    | Init `high` | Loop | Return | Typical Use        |
| ------------------ | -------- | ----------- | ---- | ------ | ------------------ |
| Binary search (==) | `[l, r]` | `n - 1`     | `<=` | index  | exact match        |
| Lower bound (≥x)   | `[l, r)` | `n`         | `<`  | `l`    | STL style          |
| Upper bound (>x)   | `[l, r)` | `n`         | `<`  | `l`    | STL style          |
| Floor (≤x)         | `[l, r]` | `n - 1`     | `<=` | `ans`  | manual             |
| Ceil (≥x)          | `[l, r]` | `n - 1`     | `<=` | `ans`  | manual             |
| Peak element       | `[l, r)` | `n-1`       | `<`  | `l`    | monotonic property |


Perfect — here’s the **updated, polished version** of your binary search notes, rewritten for **clarity, precision, and memorability** 👇

---

# 🧭 Binary Search — Once and For All (Definitive Cheat Sheet)

This is one of the **most misunderstood but most crucial** parts of algorithm design.
Let’s fix it forever. ⚡

---

## 🔹 The Root Cause of Confusion

There are **two distinct “styles”** of binary search:

| Style                       | `high` initialized as | Loop condition        | Common use                          |
| --------------------------- | --------------------- | --------------------- | ----------------------------------- |
| **[low, high)** (half-open) | `n`                   | `while (low < high)`  | `lower_bound`, `upper_bound`, peaks |
| **[low, high]** (closed)    | `n - 1`               | `while (low <= high)` | exact match, floor, ceil, classic   |

The confusion happens when people **mix the two interval styles** — leading to off-by-one bugs or infinite loops.

---

## 🧭 1️⃣ Half-Open Interval — `[low, high)`

✅ **Used in STL (`lower_bound`, `upper_bound`)**

### Rules

```cpp
int low = 0, high = n;      // ✅ high = n (exclusive)
while (low < high) {        // ✅ loop while low < high
    int mid = low + (high - low) / 2;
    if (condition)
        high = mid;         // mid might still be valid
    else
        low = mid + 1;      // discard mid
}
return low; // or high — same
```

Key idea:
👉 `high` is **exclusive**, so `nums[high]` is never accessed.
👉 You *never lose* a possible answer.

---

### Example — `lower_bound`

Find **first index ≥ x**

```cpp
int lower_bound(vector<int>& a, int x) {
    int low = 0, high = a.size();
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (a[mid] < x)
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}
```

✅ Safe
✅ Simple
✅ Exactly how STL does it

---

### Example — `upper_bound`

Find **first index > x**

```cpp
int upper_bound(vector<int>& a, int x) {
    int low = 0, high = a.size();
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (a[mid] <= x)
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}
```

---

### Example — `findPeakElement`

```cpp
int findPeakElement(vector<int>& nums) {
    int low = 0, high = nums.size() - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] < nums[mid + 1])
            low = mid + 1;
        else
            high = mid;  // mid might be the peak
    }
    return low;
}
```

This works because of a **monotonic slope property**,
even though the array is *not sorted*.

---

## 🧭 2️⃣ Closed Interval — `[low, high]`

✅ Used in **classic search**, **floor**, **ceil**, etc.

### Rules

```cpp
int low = 0, high = n - 1;
while (low <= high) {              // ✅ inclusive both ends
    int mid = low + (high - low) / 2;
    if (condition)
        high = mid - 1;            // discard mid
    else
        low = mid + 1;
}
```

Key idea:
👉 Both `low` and `high` are valid indices.
👉 Mid is excluded when it’s invalid.

---

### Example — Classic Binary Search

```cpp
int binary_search(vector<int>& a, int x) {
    int low = 0, high = a.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == x) return mid;
        if (a[mid] < x) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
```

---

### Example — Floor (greatest ≤ x)

```cpp
int floor_value(vector<int>& a, int x) {
    int low = 0, high = a.size() - 1, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] <= x) {
            ans = a[mid];
            low = mid + 1;   // go right to find larger floor
        } else high = mid - 1;
    }
    return ans;
}
```

---

### Example — Ceil (smallest ≥ x)

```cpp
int ceil_value(vector<int>& a, int x) {
    int low = 0, high = a.size() - 1, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] >= x) {
            ans = a[mid];
            high = mid - 1;  // go left to find smaller ceil
        } else low = mid + 1;
    }
    return ans;
}
```

---

## 🧠 Memory Trick — “Inclusive → n-1, Exclusive → n”

| Interval Type | Initialize `high` | Loop condition | Used for                        |
| ------------- | ----------------- | -------------- | ------------------------------- |
| `[low, high]` | `n - 1`           | `low <= high`  | exact match, floor, ceil        |
| `[low, high)` | `n`               | `low < high`   | lower_bound, upper_bound, peaks |

---

## 🧩 Summary Table

| Operation          | Range    | Init `high` | Loop | Return | Typical Use        |
| ------------------ | -------- | ----------- | ---- | ------ | ------------------ |
| Binary search (==) | `[l, r]` | `n - 1`     | `<=` | index  | exact match        |
| Lower bound (≥x)   | `[l, r)` | `n`         | `<`  | `l`    | STL style          |
| Upper bound (>x)   | `[l, r)` | `n`         | `<`  | `l`    | STL style          |
| Floor (≤x)         | `[l, r]` | `n - 1`     | `<=` | `ans`  | manual             |
| Ceil (≥x)          | `[l, r]` | `n - 1`     | `<=` | `ans`  | manual             |
| Peak element       | `[l, r)` | `n-1`       | `<`  | `l`    | monotonic property |

---

✅ **Golden Rule of Thumb**

> If `mid` **might still be the answer** → use `high = mid` and loop with `low < high`.
>
> If `mid` **is definitely invalid** → use `high = mid - 1` and loop with `low <= high`.

---


* Closed interval → "I am searching for an exact value."
* Half-open interval → "I am searching for a boundary (first true / lower bound)."