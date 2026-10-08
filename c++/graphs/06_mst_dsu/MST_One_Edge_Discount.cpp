/** 
## MST + One Edge Discount

### Problem

You are given `n` cities and `m` undirected roads:

```cpp
roads[i] = {u, v, cost}
```

You need to connect all cities with minimum total cost.

You may use a coupon **at most once**. If the coupon is used on an edge of cost `cost`, that edge costs:

```cpp
cost / 2
```

using integer division.

Return the minimum possible cost to connect all cities, or `-1` if connecting all cities is impossible.

---

### Key Observation

First construct the ordinary MST.

Let:

```text
C = cost of the MST
M = maximum edge in the MST
```

If we apply the coupon to `M`, the total becomes:

```text
C - M/2
```

Why is this optimal?

For a fixed MST, the largest edge gives the largest saving.

The important question is whether a **non-MST edge** could become useful after the coupon.

Suppose a non-MST edge `e` is added to the MST. It creates a cycle. Remove an MST edge `f` from that cycle.

The new tree has cost:

```text
C - f + e
```

If the coupon is applied to `e`:

```text
C - f + e/2
```

Because the original tree is an MST, the cycle property gives:

```text
e >= f
```

And because `M` is the largest edge in the MST:

```text
M >= f
```

Therefore:

```text
e/2 + M/2 >= f
```

which gives:

```text
C - f + e/2 >= C - M/2
```

So a non-MST edge cannot produce a better answer.

### Final formula

```text
answer = MST_cost - maximum_MST_edge / 2
```

---

### Algorithm

Use Kruskal:

1. Sort all edges by cost.
2. Use DSU to select edges that connect different components.
3. Add selected edge cost to `mst_cost`.
4. Track the largest selected edge.
5. If fewer than `n - 1` edges were selected, return `-1`.
6. Return:

```cpp
mst_cost - max_edge / 2
```

### Complexity

```text
Sorting:       O(E log E)
DSU:           O(E α(V))

Overall:       O(E log E)
Space:         O(V + E)
```

### Canonical Code
*/

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class DSU{
public:
    DSU(int n){}
    bool unite(int u, int v){
        return true;
    }
};

int cheapestMST(int n, vector<vector<int>>& roads) {

    sort(roads.begin(), roads.end(),
         [](const auto& a, const auto& b) {
             return a[2] < b[2];
         });

    DSU dsu(n);

    int mst_cost = 0;
    int max_edge = 0;
    int edges_used = 0;

    for (auto& road : roads) {

        int u = road[0];
        int v = road[1];
        int cost = road[2];

        if (dsu.unite(u, v)) {

            mst_cost += cost;
            max_edge = max(max_edge, cost);
            edges_used++;

            if (edges_used == n - 1)
                break;
        }
    }

    if (edges_used != n - 1)
        return -1;

    return mst_cost - max_edge / 2;
}
/*
### Recognition

**MST + one-time discount →**

```text
Kruskal / DSU
    ↓
ordinary MST
    ↓
largest MST edge
    ↓
discount it
```

The full exchange proof is only needed if the interviewer challenges why a non-MST edge cannot become optimal.
*/