I actually think this is the most important sheet you'll build. Arrays are the **foundation** for almost every other topic (sliding window, binary search, intervals, prefix sums, greedy, hashing, etc.).

My goal would be:

* **~65 problems**
* **Every important pattern covered**
* **Minimal redundancy**
* **Enough for SDE2 at Amazon/Microsoft/Nvidia**
* **90% coverage for Google/Meta array questions**

---

# 0. Warm-up / Simulation (7)

These should become muscle memory.

```
1. Remove Duplicates from Sorted Array
2. Remove Element
3. Merge Sorted Array
4. Move Zeroes
5. Rotate Array
6. Pascal's Triangle
7. Pascal's Triangle II
```

---

# 1. Matrix Problems (8)

```
8. Set Matrix Zeroes
9. Rotate Image
10. Spiral Matrix
11. Spiral Matrix II
12. Diagonal Traverse
13. Reshape the Matrix
14. Game of Life
15. Valid Sudoku

    isValid

    solver
        https://leetcode.com/problems/sudoku-solver/description/
```

---

# 2. Prefix Sum / Difference Arrays (9)

```
16. Running Sum of 1D Array
17. Pivot Index
18. Product of Array Except Self
19. Range Sum Query (Immutable)
20. Difference Array (implement)
21. Corporate Flight Bookings
22. Car Pooling
23. Subarray Sum Equals K
24. Continuous Subarray Sum
```

Patterns:

* Prefix Sum
* Difference Array
* Prefix HashMap

---

# 3. Kadane & Maximum Subarray Family (6)

```
25. Maximum Subarray
26. Maximum Sum Circular Subarray
27. Maximum Product Subarray
28. Maximum Absolute Sum
29. Maximum Sum Rectangle (2D)
30. K Concatenation Maximum Sum
 - Maximum Sum Rectangle (GFG)
```

---

# 4. Two Pointers (10)

```
31. Two Sum II
32. Container With Most Water
33. 3Sum
34. 3Sum Closest
35. 4Sum
36. Sort Colors
37. Squares of a Sorted Array
38. Remove Duplicates II
39. Partition Labels
40. Boats to Save People
```

---

# 5. Intervals (7)

```
41. Merge Intervals
42. Insert Interval
43. Non-overlapping Intervals
44. Meeting Rooms
45. Meeting Rooms II
46. Minimum Number of Arrows
47. Employee Free Time
```

---

# 6. Hashing + Arrays (8)

```
48. Two Sum
49. Longest Consecutive Sequence
50. Majority Element
51. Majority Element II
52. Find All Duplicates in an Array
53. Find All Numbers Disappeared
54. Contains Duplicate
55. Find Duplicate Number
```

---

# 7. Binary Search on Arrays (6)

(You may already have these in Binary Search.)

```
56. Search Rotated Sorted Array
57. Find Minimum Rotated Array
58. Peak Element
59. First and Last Position
60. Single Element in Sorted Array
61. Median of Two Sorted Arrays
```

---

# 8. Observation Problems (12)

These separate strong candidates from average ones.

```
62. First Missing Positive
63. Next Permutation
64. Gas Station
65. Jump Game
66. Jump Game II
67. Candy
68. Wiggle Sort II
69. Advantage Shuffle
70. Maximum Swap
71. Patching Array
72. Maximum Gap
73. Create Maximum Number (Google)
```

---

# 9. Optional Google Hard

These are the ones I'd only do if you're specifically targeting Google/Meta or enjoy very hard problems.

```
Count of Smaller Numbers After Self
Reverse Pairs
Shortest Unsorted Continuous Subarray
Find Median from Data Stream
Beautiful Array
Split Array Largest Sum
```

---

# Topics covered

| Pattern            | Covered |
| ------------------ | ------- |
| Simulation         | ✅       |
| Matrix             | ✅       |
| Prefix Sum         | ✅       |
| Difference Array   | ✅       |
| Kadane             | ✅       |
| Two Pointer        | ✅       |
| Sorting            | ✅       |
| Hashing            | ✅       |
| Binary Search      | ✅       |
| Intervals          | ✅       |
| Greedy Observation | ✅       |
| Cyclic Sort        | ✅       |

---

# What I would remove

A lot of sheets include **10+ stock-buying problems**. I don't think they're all necessary.

I'd keep:

* Best Time to Buy and Sell Stock I
* Best Time to Buy and Sell Stock II
* Best Time to Buy and Sell Stock III

The rest (IV, cooldown, fee) are better treated as **Dynamic Programming** because the state transition is the key idea.

Similarly, I'd move **Sliding Window** questions into your dedicated Sliding Window sheet rather than keeping them here. That avoids duplication and makes revision faster.

---

# My recommended sheet size

| Topic         | Questions |
| ------------- | --------: |
| Warm-up       |         7 |
| Matrix        |         8 |
| Prefix Sum    |         9 |
| Kadane        |         6 |
| Two Pointer   |        10 |
| Intervals     |         7 |
| Hashing       |         8 |
| Binary Search |         6 |
| Observation   |        12 |
| **Total**     |    **73** |

## One suggestion based on how you've been studying

From our previous conversations, I know you're building topic-wise revision folders (Greedy, Heap, Stack/Queue, etc.) with canonical implementations and notes. I'd make one small organizational change:

Instead of thinking of this as an "Arrays" sheet, think of it as an **"Array Techniques"** sheet. Keep it focused on array-specific techniques and move reusable algorithmic paradigms (Sliding Window, Binary Search, Greedy, Monotonic Stack, DP) into their own folders. That way each concept is learned once and revised once, while the array sheet remains the place where those techniques are first encountered in their simplest form.

I think that organization will scale much better as your overall interview preparation grows to 400–500 curated problems.
