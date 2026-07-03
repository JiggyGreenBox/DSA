# 1. Heap Basics

### Min Heap

Parent is smaller than children.

```
        2
      /   \
     4     6
    / \
   8  10
```

### Max Heap

Parent is larger than children.

```
        10
      /    \
     8      7
    / \
   2   3
```

---

# 2. Complexity

| Operation  | Complexity |
| ---------- | ---------- |
| top()      | O(1)       |
| push()     | O(log n)   |
| pop()      | O(log n)   |
| build heap | O(n)       |

Remember:

> Building a heap from n elements is **O(n)**, **not** O(n log n).

---

# 3. C++ Syntax

### Max Heap

```cpp
priority_queue<int> pq;
```

---

### Min Heap

```cpp
priority_queue<int, vector<int>, greater<int>> pq;
```

---

### Pair

```cpp
priority_queue<pair<int,int>> pq;
```

Largest first.

---

### Min Pair

```cpp
priority_queue<
    pair<int,int>,
    vector<pair<int,int>>,
    greater<pair<int,int>>
> pq;
```

Lexicographical ordering.

---

### Custom comparator

Know the syntax.

```cpp
struct Compare {
    bool operator()(Node a, Node b) {
        return a.dist > b.dist;
    }
};

priority_queue<Node, vector<Node>, Compare> pq;
```

---

# 4. Top Interview Patterns

## Pattern 1

### Top K

```
K largest
K smallest
Top K frequent
```

Keep heap size = K.

Complexity

```
O(n log K)
```

---

## Pattern 2

### Streaming

Maintain answers while numbers arrive.

Examples

```
Median Finder
Kth Largest in Stream
```

---

## Pattern 3

### Merge K Sorted Lists

Each heap node stores

```
(value, list_index, node*)
```

Heap size

```
K
```

Complexity

```
O(N log K)
```

---

## Pattern 4

### Multiple sorted arrays

Exactly same idea.

---

## Pattern 5

### Always process smallest/largest first

Examples

```
Meeting Rooms II
Smallest Range
CPU Scheduling
```

Usually

```
sort
+
min heap
```

---

## Pattern 6

### Graph Algorithms

Know where heap appears.

```
Dijkstra

Prim

A*
```

Priority queue stores

```
(distance,node)
```

---

# 5. Heap vs Sorting

Sorting

```
Need entire order
```

Heap

```
Need only minimum
Need only maximum
Need top K
Need streaming
```

---

# 6. Heap Clues

If you read

```
largest

smallest

closest

minimum

maximum

K

top K

stream

online

merge K

next smallest
```

Immediately think

```
Heap?
```

---

# 7. Common Problems

These cover almost everything.

### Easy

* Kth Largest Element
* Last Stone Weight

---

### Medium

* Top K Frequent Elements
* K Closest Points
* K Closest Elements
* Kth Largest in Stream
* Find Median from Data Stream
* Merge K Sorted Lists
* Meeting Rooms II
* Task Scheduler (heap + greedy)

---

### Hard

* Smallest Range Covering K Lists
* Sliding Window Median

---

# 8. Common Mistakes

### Forgetting to pop

Heap grows to O(n)

Instead

```cpp
pq.push(x);

if(pq.size()>k)
    pq.pop();
```

---

### Wrong heap

Need smallest?

Don't accidentally use

```cpp
priority_queue<int>
```

---

### Wrong comparator

Remember

```cpp
greater<int>
```

gives

```
Min Heap
```

---

### Pair ordering

```
pair<int,int>
```

compares

```
first

then second
```

---

# 9. Mental Decision Tree

```
Need only max/min?
        ↓
      Heap

Need top K?
        ↓
 Heap size K

Need median?
        ↓
 Two heaps

Need merge K sorted?
        ↓
 Heap of K elements

Need shortest distance?
        ↓
 Priority queue
```

---

## What I'd memorize

For interviews, the following six patterns account for the vast majority of heap problems:

1. **Top K** (fixed-size heap)
2. **Two heaps** (median and streaming)
3. **Merge K sorted lists/arrays**
4. **Sort + heap** (intervals, scheduling, ranges)
5. **Priority queue in graph algorithms** (Dijkstra, Prim)
6. **Recognizing heap keywords** (largest, smallest, closest, top K, stream, merge K)

If you can recognize which of these patterns applies and write the `priority_queue` syntax without hesitation, you're well prepared for nearly all heap questions you'll encounter in SDE2 interviews.
---
# heap internals
### internal nodes etc
```text
          0
       /     \
      1       2
     / \     / \
    3   4   5   6

leaf nodes start at n/2
7/2 = 3
so nodes 0,1,2 are not leaves
we only care about them
```
 - proof for non-leaf nodes
```
leaf is node is when left_child >= n

    left_child = 2*i + 1

    2*i + 1 >= n
    i >= (n-1) / 2

first leaf is at n/2
last parent is at n/2 - 1
```