# Heap Complexities

## Binary Heap

Complete Binary Tree

- Height = O(log n)
- Parent = (i-1)/2
- Left Child = 2*i+1
- Right Child = 2*i+2

---

## Operations

| Operation | Time |
|-----------|------|
| Top | O(1) |
| Push | O(log n) |
| Pop | O(log n) |
| Heapify | O(log n) |
| Build Heap | O(n) |
| Heap Sort | O(n log n) |

Space

- Heap = O(n)

---

## STL Priority Queue

```cpp
priority_queue<int> pq;
```

| Operation | Time |
|-----------|------|
| top() | O(1) |
| push() | O(log n) |
| pop() | O(log n) |
| empty() | O(1) |
| size() | O(1) |

---

## Heap Construction

Repeated insert

```
for each element
    push()
```

Time

```
O(n log n)
```

---

Bottom-up Heapify

```
for(i = n/2-1; i>=0; i--)
    heapify(i)
```

Time

```
O(n)
```

This is the standard STL heap construction.

---

## Heapify

One node may travel from root to leaf.

Worst case

```
O(log n)
```

---

## Heap Sort

Build Heap

```
O(n)
```

Extract n times

```
n × O(log n)
```

Total

```
O(n log n)
```

In-place

```
Yes
```

Stable

```
No
```

---

## Min Heap

Top = smallest element

```cpp
priority_queue<
    int,
    vector<int>,
    greater<int>
> pq;
```

---

## Max Heap

Top = largest element

```cpp
priority_queue<int> pq;
```

---

## Custom Comparator

Comparator answers:

> "Does a have LOWER priority than b?"

Max Heap

```cpp
return a < b;
```

Min Heap

```cpp
return a > b;
```

Think in terms of **priority**, not sorting.

---

## Heap Recognition Patterns

### Need largest repeatedly

```
Max Heap
```

Examples

- IPO
- Reorganize String
- Task Scheduler (simulation)

---

### Need smallest repeatedly

```
Min Heap
```

Examples

- Merge K Lists
- K Smallest Pairs
- Dijkstra

---

### Maintain best K elements

```
Heap of size K
```

Examples

- Top K Frequent
- K Closest Points

---

### Streaming data

```
Heap
```

Examples

- Median Finder
- Kth Largest Stream

---

## Interview Tips

Heap is useful when:

- Repeatedly extracting min/max.
- Maintaining Top K.
- Processing a stream.
- Greedy repeatedly chooses the best candidate.
- Merging multiple sorted sequences.

If you only need the minimum or maximum **once**, sorting is often simpler.

If you need it **repeatedly**, think Heap.