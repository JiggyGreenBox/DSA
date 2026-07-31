#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    int NthRoot(int N, int M) {

        // modulo
        // division
        // multiplication

        int start = 1;
        int end = M;

        while(start <= end) {

            long long mid = start + (end-start)/2;

            cout << start;
            cout << " | ";
            cout << mid;
            cout << " | ";
            cout << end;
            cout << endl;
            cout << endl;


            long long n_root = pow(mid, N);

            cout << start;
            cout << " | ";
            cout << mid;
            cout << " | ";
            cout << end;
            cout << " | n_root: ";
            cout << n_root;
            cout << endl;
            cout << endl;

            if(n_root == M) return mid;

            if(n_root < M){
                start = mid + 1;
            }
            else{
                end = mid - 1;
            }
        }
        return -1;
    }
};



int NthRoot(int n, int m) {

    long long l = 1;
    long long r = m;

    while(l <= r) {

        long long mid = l + (r - l) / 2;

        long long val = power(mid, n, m);

        if(val == m)
            return mid;

        if(val < m)
            l = mid + 1;
        else
            r = mid - 1;
    }

    return -1;
}

int main(){
    Solution sol;

    // cout << sol.NthRoot(7,128) << endl;

    cout << sol.NthRoot(9,512) << endl;
}

/*

Find Nth root of a number

invariant
    given n and m
    find x such that x^n = m

    x can be between 0 and m
        need exact match or return -1

    l=0, r = m

    while l<=r
        mid = 

    i dont know the function to find pow(n,x)



    x ∈ [1, m]
    Search for x in [l,r]

    If x^n == m
        found

    If x^n < m
        answer must be larger

    If x^n > m
        answer must be smaller
*/



long long power_simple(long long x, int n) {
    long long ans = 1;

    for(int i=0; i<n; i++) {
        ans *= x;
    }

    return ans;
}
long long power(long long x,
                int n,
                long long limit) {

    long long ans = 1;

    for(int i=0; i<n; i++) {
        ans *= x;

        if(ans > limit)
            return limit + 1;
    }

    return ans;
}

/*
Invariant:

    ans * (base ^ exp)
    =
    original x^n


Observation:

    If n is odd:
        x^n = x * x^(n-1)
        -> move one x into ans

    Remaining exponent is even:

        x^n = (x*x)^(n/2)

Updates:

    if (n is odd)
        ans *= x

    x *= x
    n /= 2
*/
long long power_logn(long long x, long long n) {
    long long ans = 1;

    while(n > 0) {

        if(n & 1)       // odd case, x^3, remove one x, put in ans
            ans *= x;

        x *= x;         // even case, x^2, x now equal to x*x, divide n by 2
        n >>= 1;    // right shift is divide by 2
    }

    return ans;
}

/*
example
    2^5 = 32
        

    Step 1 (n = 5, odd)

        Peel off one 2.
            ans = 2
            x = 2
            n = 4

        Now compress the remaining power:
            2^4 = (2×2)^2 = 4^2

        update:
            ans = 2
            x = 4
            n = 2

    Step 2 (n = 2, even)

        no peel

        Compress again:
            4^2 = (4x4)^1 = 16

            ans = 2
            x = 16
            n = 1

    Step 3 (n = 1, odd)
        peel off one x, 16
            ans = 32

        x = 256
        n = 0
    
    DONE
        ans = 32
*/