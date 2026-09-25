```
LOOP vs BRANCHING

Ask:
    What is my decision at this recursion level?

If I choose WHICH element among many:
    → loop

If I'm processing ONE fixed element:
    → direct branches

Examples:

    Subsets
        → pick / skip
            this can be both branching and loop
                the loop picks from [1,2,3]
                    1, then [2,3]
                    2, then [3], which means skip [1]
                    3, then [],  which means skip [1,2]

                branching is
                    for idx
                        pick:
                            push
                            backtrack
                            pop

                        skip
                            backtrack

    Combinations
        → loop over candidates

    Permutations
        → loop over unused candidates

    Letter Case Permutation
        → current character:
           lowercase / uppercase

    N-Queens
        → current row:
           try each column
           → loop
```

```
BUCKET / ASSIGNMENT BACKTRACKING

Ask:

    "Do I have N items that must be distributed
     among K groups/buckets/resources?"

If yes:

    process one item at a time

    for each bucket:
        check constraint
        assign item
        recurse
        undo assignment

Template:

    item idx
        ↓
    bucket 0
    bucket 1
    ...
    bucket k-1
```