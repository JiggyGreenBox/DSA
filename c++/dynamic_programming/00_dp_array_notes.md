The biggest trick is:

```text id="u4m8qx"
DP tables are just stored recursion answers
```

Nothing more.

If recursion is clear, the DP table is already hiding inside it.

---

# The Core Conversion Process

For every recursive function:

```cpp id="k1q7mr"
f(a, b, c)
```

ask:

```text id="x6m2qw"
which variables change?
```

Those variables become DP dimensions.

---

# Step 1 — Define the Recursive Meaning

This is the MOST important step.

You must be able to say:

```text id="r9q4mw"
what exact question does f(...) answer?
```

Example:

```cpp id="v3m7qx"
f(idx, target)
```

means:

> using elements from idx onward,
> can I form target?

If this sentence is unclear:

```text id="c5q1mr"
tabulation becomes impossible
```

---

# Step 2 — Identify Changing Variables

Example:

```cpp id="j8m4qp"
f(idx, target)
```

Changes:

* idx
* target

So DP dimensions:

```text id="n2q7mw"
dp[idx][target]
```

---

Examples:

| Recursive State  | DP Table            |
| ---------------- | ------------------- |
| `f(n)`           | `dp[n]`             |
| `f(i,j)`         | `dp[i][j]`          |
| `f(day,buy,cap)` | `dp[day][buy][cap]` |

This mapping is mechanical.

---

# Step 3 — Copy Base Cases into Table

Recursion:

```cpp id="y7m1qx"
if(target == 0) return true;
```

becomes:

```cpp id="t4q8mr"
dp[*][0] = true;
```

because:

```text id="m9q2wx"
all states with target 0 are true
```

---

Another example:

```cpp id="u5m4qr"
if(idx == n) return 0;
```

becomes:

```cpp id="f8q1mw"
dp[n][*] = 0;
```

---

# Step 4 — Translate Recursion Directly

Recursive:

```cpp id="z3m7qx"
return take || skip;
```

becomes:

```cpp id="g6q2mr"
dp[i][t] = take || skip;
```

Literally the same logic.

---

# Step 5 — Figure Out Loop Direction

This is the MOST COMMON confusion.

Ask:

```text id="p1m8qw"
what previous states does current state depend on?
```

---

Example:

```cpp id="r4q7mw"
dp[i][t]
depends on
dp[i-1][...]
```

Then:

```text id="v9m2qr"
iterate i forward
```

because previous row must already exist.

---

Another example:

```cpp id="c2q5mx"
dp[i][t]
depends on
dp[i+1][...]
```

Then:

```text id="k7m1qw"
iterate backward
```

---

# THE BEST DP TRICK

Whenever confused:

write the recursive equation first.

Example:

f(i,t)=f(i-1,t)\ OR\ f(i-1,t-arr[i])

Then simply replace:

```text id="d5q8mr"
f(...) → dp[...]
```

That is literally tabulation.

---

# Another Huge Trick

Think of DP cells as:

```text id="w1m4qx"
answered recursive calls
```

Example:

```cpp id="x8q2mw"
f(3,7)
```

becomes:

```cpp id="n6m9qr"
dp[3][7]
```

So the table is just:

```text id="t3q1mw"
all recursive calls cached ahead of time
```

---

# How to Mentally Build Tables

Don’t think:

```text id="u7m4qx"
fill rows and columns
```

Think:

```text id="m2q8wr"
answer smaller recursive questions first
```

That naturally gives correct order.

---

# MOST IMPORTANT PATTERN TO MEMORIZE

Different DP families use different combine operations:

| Problem Type | Transition            |   |       |
| ------------ | --------------------- | - | ----- |
| Feasibility  | `take                 |   | skip` |
| Counting     | `take + skip`         |   |       |
| Optimization | `max/min(take, skip)` |   |       |

This alone clarifies MANY DP problems.

---

# Your Biggest Current Gap

You already understand recursion reasonably well.

Your current weak point is:

```text id="h9m1qx"
understanding what one dp cell MEANS
```

That is the exact thing to focus on now.

For every problem, force yourself to write:

```text id="b4q7mw"
dp[i][x] means __________
```

in English before coding.

That single habit accelerates DP understanding massively.

# single row optimization
 - RIGHT → LEFT
    - `protect previous row`
    - `use once`
 - LEFT → RIGHT
    - `allow current row reuse`
    - `reuse infinitely`