#include <bits/stdc++.h>
using namespace std;

int main() {

    return 0;
}




[-5, -2, 4, 5, 0, 0, 0]          [-3, 1, 8]
[-5, -2, 4, 5, 0, 0, 0]          [-3, 1, 8]
i                                  j

i<=j i++

-2<-3
    swap i, j, i++
[-5, -3, -2, 5, 0, 0, 0]          [4, 1, 8]
             i                     j


target=-3, idx=2
[-5, -2, 4, 5, 0, 0, 0] -> [-5, -2, -3, 4, 5, 0, 0]

shift i=2
    while j==n-1; j>i; j--
        nums[j] = nums[j-1]

