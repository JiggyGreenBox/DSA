#include <iostream>
#include <vector>
using namespace std;

/*

Partition a set into two subsets with minimum absolute sum difference

we can partition into sum1, sum2
    then we want min(sum1 - sum2)
    total = sum1 + sum2

    min(total-sum2-sum2)
    min(total-2*sum2)

    min(total-2sum)

f(idx, sum, total, arr)
    idx==n return 0

    int take_sum = 
    int skip_sum = 

    return min(total - 2*take_sum, total - 2*skip_sum)


we do NOT need recursion that returns minimum difference directly
we only need to know which subset sums are achievable

0 → total
    find achievable subset sum s
    that minimizes |total - 2s|

*/

int main() {
    return 0;
}