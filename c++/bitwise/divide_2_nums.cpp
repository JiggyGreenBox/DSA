#include <iostream>
#include <climits>
using namespace std;

// this code has overflow issues
int divide1(int dividend, int divisor) {
    bool isNeg = false;
    long top = dividend;
    long bot = divisor;
    if(top < 0) {
        top = -top;
        isNeg = !isNeg;
    }
    if(bot < 0) {
        bot = -bot;
        isNeg = !isNeg;
    }


    long rem = top;
    int ans = 0;
    while (rem >= bot)
    {
        int i=0;
        while (bot<<i <= rem) i++;
        i--;
        rem = rem-(bot<<i);
        ans |= 1<<i;
    }
    if(isNeg) ans = -ans;
    return ans;    
}


// this version 
// still has overflow because d<<i+1, i can overflow
// it is not bounded
// we have 2 loops so the 
// TC is log^2(N)
int divide2(int dividend, int divisor) {
    // overflow cases
    if(dividend == INT_MIN && divisor == -1) return INT_MAX;

    // sign
    bool isNeg = (dividend<0) ^ (divisor<0); // even true is false, odd true is true

    // overflow
    long n = labs((long)dividend);
    long d = labs((long)divisor);

    // loop
    int ans=0;
    while( n >= d ) {

        // find largest removeable value
        int i=0;
        while(d<<(i+1) <= n) i++;

        n -= (d<<i);
        ans |= (1<<i);
    }
    if(isNeg) ans = -ans;
    return ans;
}

// There is exactly ONE division that overflows a 32-bit signed int:
//     INT_MIN / -1
//     INT_MIN / -1 = +2^31
//     +2^31 > INT_MAX

// INT_MIN = -2^31
// INT_MAX =  2^31 - 1

// abs(INT_MIN)  ❌ overflow
// labs((long)INT_MIN) == 2^31 ✔


int divide3(int dividend, int divisor) {
    // overflow cases
    if(dividend == INT_MIN && divisor == -1) return INT_MAX;

    // sign
    bool isNeg = (dividend<0) ^ (divisor<0);

    // safe abs
    long n = labs((long) dividend);
    long d = labs((long) divisor);

    long ans=0;
    for(int i=31; i>=0; i--) {
        if(d<<i <=n) {
            n -= (d<<i);
            ans |= (1L<<i);
        }
    }
    return (isNeg) ? -ans : ans;
}

int main() {
    cout << divide3(10,3) << endl;
    cout << divide3(7,3) << endl;
    return 0;
}