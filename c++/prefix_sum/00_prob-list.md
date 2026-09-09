### Level 1 — Basic prefix sum
 1. Range Sum Query - Immutable — LC 303
 2. Find Pivot Index — LC 724
 3. Left and Right Sum Differences — LC 2574
 4. Running Sum of 1D Array — LC 1480

### Level 2 — Prefix sum + hashmap ⭐
 5. Subarray Sum Equals K — LC 560 ⭐
 6. Contiguous Array — LC 525 ⭐
 7. Continuous Subarray Sum — LC 523
 8. Binary Subarrays With Sum — LC 930
 9. Count Number of Nice Subarrays — LC 1248

### Level 3 — Prefix remainder / modulo
 10. Subarray Sums Divisible by K — LC 974 ⭐
 11. Make Sum Divisible by P — LC 1590

### Level 4 — 2D prefix sum
 15. Range Sum Query 2D - Immutable — LC 304 ⭐
 16. Number of Submatrices That Sum to Target — LC 1074 🔥



### add
 - 09_Product_of_Array_Except_Self.cpp
 - 13_Corporate_Flight_Bookings.cpp
 - 14_Car_Pooling.cpp
 - 12_Range_Addition.cpp (optional)
 8. Maximum Size Subarray Sum Equals k — LC 325 ⭐
 10. Longest Well-Performing Interval — LC 1124 ⭐
 11. Count of Range Sum — LC 327 🔥


1124  Longest Well-Performing Interval
327   Count of Range Sum
1658  Minimum Operations to Reduce X to Zero

# clues for prefix-sum
```
1. Is it about a CONTIGUOUS subarray/range?
                  ↓
2. Is there some condition involving SUM / counts?
                  ↓
3. Can I express the subarray quantity as
       prefix[r] - prefix[l-1]?
                  ↓
4. What relationship must the two prefix states satisfy?
                  ↓
5. What information do I need to store?

```
```
Question                    Store

Does one exist?             set / hashmap
How many?                   frequency
Longest?                    earliest index
Shortest?                   latest index / other technique
Divisible by K?             prefix remainder
Range query?                prefix array
Range updates?              difference array + prefix
```

```
                 PREFIX SUM
                     │
       ┌─────────────┼──────────────┐
       │             │              │
     COUNT         LONGEST        SHORTEST
       │             │              │
   frequency       earliest        latest
       │             │              │
  560, 930       525, 325       1590
  1248, 974        1124


PREFIX SUM
   │
   ├── modulo          → 523, 974, 1590
   │
   ├── transformation  → 525, 1124, 1248
   │
   ├── difference      → 1109, 1094, 370
   │
   ├── 2D              → 304, 1074
   │
   └── range counting  → 327

```