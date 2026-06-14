#include <iostream>
#include <vector>
using namespace std;


/*

Find square root of a number

    Given a positive integer n. Find and return its square root. If n is 
    not a perfect square, then return the floor value of sqrt(n).

        Input: n = 36
        Output: 6
        Explanation: 6 is the square root of 36.

        Input: n = 28
        Output: 5
        Explanation: The square root of 28 is approximately 5.292. So, the 
        floor value will be 5.
*/

/*

x^2 = y
    we want to find x given y

brute force
    we can start from 1 and keep mulitplying till we find the number
    28

    1*1, 2*2....5*5=25, 6*6=36
        return 5

        will be O(n)


binary search
    what is the search space,
        answer lies [1..n]
            can we reduce, after 9, it is always less than n/2
            [1..n/2]

    mid = l+(h-l)/2;

    mid*mid == target return mid
        OR if target/mid == mid return mid

    less
        ans = mid
        low = mid+1

    more
        high = mid-1
*/

/*
Invariant:
    Answer is the largest x satisfying x² <= n

Observation:
    x² <= n is monotonic

    T T T T T F F F F

Discard Rule:
    if mid² <= n
        answer can be mid or larger
        l = mid + 1

    else
        r = mid - 1
*/

int floorSqrt(int n)  {
    int l=0, h=n;
    int ans = 0;

    while(l<=h) {
        long long mid = l + (h-l)/2;

        if(mid*mid <= n) {
            ans = mid;
            l = mid + 1;
        }
        else{
            h = mid - 1;
        }
    }
    return ans;
}


int main() {
    return 0;
}