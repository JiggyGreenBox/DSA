# binary search
* lower_bound is useful for finding the start of a range of duplicates.

* upper_bound is useful for finding the end of a range of duplicates.


```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {10, 20, 30, 30, 40, 50};
    int val = 30;

    auto upper = std::upper_bound(v.begin(), v.end(), val);

    // The index of the element
    int index = std::distance(v.begin(), upper);

    std::cout << "Upper bound for 30 is at index: " << index << std::endl;
    // Output: Upper bound for 30 is at index: 4

    return 0;
}
```

- Upper bound: find the first element which is not the value `nums[mid]>val` mid is never a value
- Lowe bound: find the first element which is lesser or the first occurance value `nums[mid]>val` mid could be the value

```cpp
// upper bound
if(nums[mid]<=val) {
    // discard
    start = mid+1;
}
else{
    end = mid-1;
}

//5,5,5,5,5  val=5, return first 5
// lower bound
if(nums[mid]<val) {
    // discard
    start = mid+1;
}
else{
    // >=
    end = mid; // mid can be a solution
}
```

* Lower bound `mid < x` discard and `mid >= x` keep
* Upper bound `mid <= x` discard and `mid > x` keep
```cpp
/*
[5,5,5,5,5,6] val=5
upper-bound: 6
lower-bound: first 5, index 0
*/
```