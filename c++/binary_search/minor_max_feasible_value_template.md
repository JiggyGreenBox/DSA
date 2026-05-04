Perfect 🔥 — here’s your **canonical Binary Search on Answer Template** —
this is *the* pattern used in hundreds of problems (LeetCode, GFG, etc.) such as:

* ⛏️ **Minimum Days to Make m Bouquets**
* 📦 **Capacity to Ship Packages Within D Days**
* 🏭 **Minimum Time to Complete Jobs**
* 📚 **Allocate Minimum Pages**
* ⚙️ **Koko Eating Bananas**
* 🏗️ **Aggressive Cows / Minimize Max Distance**

---

## 🧠 **Binary Search on Answer – Canonical Template**

### ✅ Step 1: Identify the pattern

If the problem asks something like:

> “Find the *minimum* value X such that a condition becomes true”

or

> “Find the *maximum* value X that still satisfies a condition”

then you’re in the **binary search on the answer** family.

---

### ✅ Step 2: General Template

```cpp
int binarySearchAnswer() {
    int low = MIN_POSSIBLE_VALUE;
    int high = MAX_POSSIBLE_VALUE;
    int ans = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (isFeasible(mid)) {
            ans = mid;          // mid works
            high = mid - 1;     // try smaller (for minimum)
        } else {
            low = mid + 1;      // not feasible yet
        }
    }

    return ans;
}
```

For **maximum feasible value**, just swap the moves:

```cpp
if (isFeasible(mid)) {
    ans = mid;          // mid works
    low = mid + 1;      // try larger
} else {
    high = mid - 1;     // too large
}
```

---

### ✅ Step 3: Monotonic Function (Key Property)

Your helper function `isFeasible(x)` must be **monotonic**:

* If it’s **true** for some `x`, then it’s **true** for all greater (or smaller) values, depending on the problem.

Examples:

| Problem                | `isFeasible(mid)` means                        | Moves if true                     |
| ---------------------- | ---------------------------------------------- | --------------------------------- |
| 🌹 Rose Garden         | can we make ≥ m bouquets by day `mid`?         | search smaller (min day)          |
| 📦 Ship Packages       | can we ship in ≤ D days with capacity `mid`?   | search smaller                    |
| 🍌 Koko Eating Bananas | can Koko finish in ≤ H hours with speed `mid`? | search smaller                    |
| 🐄 Aggressive Cows     | can we place cows ≥ distance `mid` apart?      | search larger (maximize distance) |

---

### ✅ Step 4: Checklist

| Concept                      | Meaning                                                          |
| ---------------------------- | ---------------------------------------------------------------- |
| **low, high**                | always inclusive range (`while (low <= high)`)                   |
| **mid = low + (high-low)/2** | prevents overflow                                                |
| **return ans**               | or sometimes `return low` (if searching min feasible)            |
| **Overflow handling**        | use `long long` if intermediate multiplications may exceed `int` |
| **Monotonic predicate**      | must ensure no oscillation or gaps                               |

---

### ✅ Step 5: Common Examples

#### 🌹 Minimum Day to Make Bouquets

```cpp
if (bouquets(mid) >= m) { ans = mid; high = mid - 1; }
else low = mid + 1;
```

#### 🍌 Koko Eating Bananas

```cpp
if (canEatAll(mid)) { ans = mid; high = mid - 1; }
else low = mid + 1;
```

#### 🐄 Aggressive Cows

```cpp
if (canPlace(mid)) { ans = mid; low = mid + 1; }
else high = mid - 1;
```

---

### 🧩 **Template Summary (Cheat Sheet)**

| Goal                        | Predicate                                 | Move When True   | Move When False  |
| --------------------------- | ----------------------------------------- | ---------------- | ---------------- |
| Find **minimum feasible X** | `f(x)` = “can we achieve this or better?” | `high = mid - 1` | `low = mid + 1`  |
| Find **maximum feasible X** | `f(x)` = “can we achieve this value?”     | `low = mid + 1`  | `high = mid - 1` |

---

Would you like me to give you a **mini reference sheet** (one-page C++ template) you can reuse for both *minimum* and *maximum* type binary searches, with comments and examples inline (ready to paste in your LeetCode/GFG solutions)?
