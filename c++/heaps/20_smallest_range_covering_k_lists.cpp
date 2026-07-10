/*
Smallest Range Covering Elements from K Lists
    [https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/description/]

You have k lists of sorted integers in non-decreasing order. Find the 
smallest range that includes at least one number from each of the k 
lists.

We define the range [a, b] is smaller than range [c, d] if b - a < d 
- c or a < c if b - a == d - c.

Example 1:

    Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
    Output: [20,24]
    Explanation: 
    List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
    List 2: [0, 9, 12, 20], 20 is in range [20,24].
    List 3: [5, 18, 22, 30], 22 is in range [20,24].

Example 2:

    Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
    Output: [1,1]
*/

/*
Smallest Range Covering Elements from K Lists
we want a range from all lists
    4, 10, 15, 24, 26
    0,  9, 12, 20
    5, 18, 22, 30

    start:
    [4], 10, 15, 24, 26
    [0],  9, 12, 20
    [5], 18, 22, 30

    [0,5], width = 5
        try a smaller range by moving 0 ahead

    [4], 10, 15, 24, 26
     0,  [9], 12, 20
    [5], 18, 22, 30

    best [0,5]
    [4,9], w=5
        try a smaller range by moving 4 ahead

     4, [10], 15, 24, 26
     0,  [9], 12, 20
    [5], 18, 22, 30
    
    best [0,5]
    [5,10], w=5
        try a smaller range by moving 5 ahead

    4, [10], 15, 24, 26
    0,  [9], 12, 20
    5, [18], 22, 30

    best [0,5]
    [9,18], w=9
        try a smaller range by moving 9 ahead

    4, [10],  15, 24, 26
    0,    9, [12], 20
    5, [18],  22, 30

    best [0,5]
    [10,18], w=10
        try a smaller range by moving 10 ahead


    4,  10, [15], 24, 26
    0,   9, [12], 20
    5,[18],  22, 30

    best [0,5]
    [12,18], w=6
        try a smaller range by moving 12 ahead

    4,  10,[15], 24, 26
    0,   9,  12, [20]
    5,[18],  22, 30

    best [0,5]
    [15,28], w=5
        try a smaller range by moving 15 ahead

    4,  10, 15, [24], 26
    0,   9, 12, [20]
    5,[18], 22, 30

    best [0,5]
    [18,24], w=6
        try a smaller range by moving 18 ahead

    4, 10, 15, [24], 26
    0,  9, 12, [20]
    5, 18, [22], 30
    
    [20,24], w=4, update best
        try a smaller range by moving 20 ahead
            cant

    




*/

/*
Smallest Range Covering K Lists

Invariant:
- One pointer per list.
- Heap stores current minimum.
- Track current maximum.
- Candidate range = [min, max].
- Advance only the minimum.
- Stop when one list ends.
*/
