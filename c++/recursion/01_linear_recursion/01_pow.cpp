#include <iostream>
#include <vector>
#include <chrono>
using namespace std;




double power(double x, int n){

    long long N = n; // INT_MIN buffer overflow

    if(N < 0) {
        x = 1/x;
        N = -N;
    }

    double ans = 1.0;
    // this version even though is logn uses LESS iterations
    // no separate flows for odd and even
    // if nn is odd, ans gets updated and nn becomes even thru division anyways    
    while(N>0) {

        if(N & 1) { // (nn % 2) == 1
            ans *= x;
        }
        x *= x;
        N >>= 1; // nn=nn/2;
    }
    return ans;
}


// if n is even the n/2 remainder will be 0
//      x^n = x^(n/2) * x^(n/2)
//      ans = myPow(half) * myPow1(half)
//
//      half = myPow(x, n/2)
//      ans = half*half

// if n is odd eg.3 x^5 = x^4 * x
// in this case since div is int div
// half is 5/2 = 2
// ans = 2*2 * x
// ans - half * half * x

double power_rec(double x, long long n) {
    // need return conditions since this is recursive
    if(n == 0) 
        return 1;

    if(n < 0) 
        return 1.0 / power_rec(x, -n);

    double half = power_rec(x, n/2);

    if(n%2==0) 
        return half * half;

    return half * half * x;
}


int main(){
    
    double x = power(2.0, -500);
    
    x = power_rec(2.0, -500);    
    
    return 0;
}