# counting subarrays
 - usually we want a valid subarray
 - then get min or max len
### counting is different
 - for `[left,right]` how many are valid at `right`?
    - `[left,right]`,`[left+1,right]`,`[left+2,right]` ...
    - number of ways = right - left + 1 = window length
    - `total += len(left,right)`

 - this is the `atMost()` pattern
    - fix `right`
    - how many from `[left,right]`

- this is the `atLeast()` pattern
    - fix left
    - how many from ending positions work
    - count += n-right
    - left gets moved ahead for next check

```
MAX LEN
    valid window
    → keep largest window

MIN LEN
    valid window
    → keep shrinking
    → keep smallest window

COUNT AT MOST
    valid window
    → count valid STARTS
    → right - left + 1

COUNT AT LEAST
    valid window
    → count valid ENDS
    → n - right
```
```
atMost to count starts
atLeast to count ends
```

```
we want count of subarrays
    where distinct is == k

for checking equals or not equals we can use a sliding window easily
for counting how do we do this?
    if keep distinct == k
        how do we know the inner subarray details without checking each subarray?

but we can say in this subarray
    all subarrays have distinct <= k 
        without check each combination in O(n) pass

    so perform another O(n) pass
        and find distinct <= k-1

    then the diff is exacly == k
```

### deque
 - for a sliding window if we want MIN/MAX
 - use it like a monotonic stack