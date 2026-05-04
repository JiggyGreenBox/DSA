#include <iostream>
#include <vector>
#include <chrono>
using namespace std;


// x^n = x^2^(n/2)  even
// x^n = x^1^(n-1)  odd
// use odd to update ans
// use odd to update x and n

// for even
//      x = x*x, n=n/2
// for odd
//      ans = ans*x
//      x = x*x, n=n/2
// n always becomes 0 eventually
//      so while(n>0){..}
// n== 1 and 0 are always achieved during binary division
// so ans will always be updated ans n==1


double myPow1(double x, int n){
    // first approcah is too multiply x*n times
    // for 1..n x*x
    // this is O(n)

    // lets reduce num of calls by 2 at each step
    // 2^32
    // = 2^2 * 2^16
    // = 2^2 * 2^2 * 2^8
    // = 2^2 * 2^2 * 2^2 * 2^4
    // = 2^2 * 2^2 * 2^2 * 2^2 * 2^2

    // 4 calls vs 32 calls
    // think of quick reduction
    // we need to consider negative exponents
    // and odd exponents
    
    long long nn = n;
    double ans = 1;
    if(n<0) nn = -1LL*n;
    // cout << nn << endl;
    // this version even though is logn uses more iterations
    // one for odd and one for even
    // if nn is odd, ans gets updated and nn becomes even    
    while(nn>0){        
        if(nn%2 == 0){
            x = x*x;
            nn = nn/2;
        }
        else{
            ans *= x;
            nn=nn-1;
        }            
        // cout << "nn: " << nn << endl;
        // cout << "ans: "<< ans << endl;
    }
    if(n<0) ans = 1/ans;
    return ans;
}

double myPow2(double x, int n){
    long long nn = n; // INT_MIN buffer overflow
    if(nn<0){
        x = 1/x;
        nn = -nn;
    }
    double ans = 1.0;
    // this version even though is logn uses LESS iterations
    // no separate flows for odd and even
    // if nn is odd, ans gets updated and nn becomes even thru division anyways    
    while(nn>0){
        if(nn & 1) { // (nn % 2) == 1
            ans *= x;
        }
        x *= x;
        nn >>= 1; // nn=nn/2;
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

double myPowRecursive(double x, long long n) {
    // need return conditions since this is recursive
    if(n == 0) return 1;
    if(n < 0) return 1.0 / myPowRecursive(x, -n);

    double half = myPowRecursive(x, n/2);
    if(n%2==0) return half * half;
    return half * half * x;
}

void div2(int n){
    cout << n << " ";

    while(n>0){
        cout << n/2 << " ";
        n = n/2;
    }
    cout << "\n";
}

int main(){

    using Clock = std::chrono::high_resolution_clock;
    using ns = chrono::nanoseconds;

    auto start = Clock::now();
    double x = myPow1(2.0, -500);
    auto end = Clock::now();
    auto duration = std::chrono::duration_cast<ns>(end - start);
    cout << duration.count() << endl;

    start = Clock::now();
    x = myPow2(2.0, -500);
    end = Clock::now();
    duration = std::chrono::duration_cast<ns>(end - start);
    cout << duration.count() << endl;


    start = Clock::now();
    x = myPowRecursive(2.0, -500);
    end = Clock::now();
    duration = std::chrono::duration_cast<ns>(end - start);
    cout << duration.count() << endl;
    cout << x << endl;
    

    // div2(5); // 5 2 1 0
    // div2(8); // 8 4 2 1 0
    // div2(13); // 13 6 3 1 0
    // div2(1000); // 1000 500 250 125 62 31 15 7 3 1 0 
    // div2(1000000); // 1000000 500000 250000 125000 62500 31250 15625 7812 3906 1953 976 488 244 122 61 30 15 7 3 1 0

    return 0;
}