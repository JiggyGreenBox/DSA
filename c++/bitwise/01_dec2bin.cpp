#include <bits/stdc++.h>
using namespace std;

string dec2bin(int num) {
    string s;

    // divide by 2
    while(num > 0) {
        // s += char()
        // cout << num << endl;
        int rem = num%2;
        // cout << rem  << endl;
        s += char(rem + '0');
        num = num/2;
    }

    reverse(s.begin(), s.end());
    return s;
}

// #include <string>
// #include <algorithm>
string dec2bin2(int num) {
    if(num == 0) return "0"; // 0 edge case

    string s;
    while(num > 0){
        // for understanding
        // s+= (num%2 == 0)? '0':'1';
        // num = num/2;

        // for interviews
        s+= (num & 1)? '1':'0';
        num >>= 1;
    }
    reverse(s.begin(), s.end());
    return s;
}

int bin2dec(string s) {
    int ans = 0;
    int pow = 1;
    for(int i=s.size()-1; i>=0; i--) {
        int num = s[i] - '0';
        ans += num * pow;
        pow *= 2;
    }
    return ans;
}

int bin2dec2(string s) {
    int ans = 0;
    for (char c : s) {
        // Shift existing answer left (multiply by 2) and add the new bit
        ans = (ans << 1) + (c - '0');
    }
    return ans;
}

int main() {
    
    dec2bin(13);
    for(const auto& num : {0,13,8,100,15}){
        cout << num << ":" << dec2bin2(num) << " | " << bin2dec2(dec2bin2(num)) << endl;
    }

    // cout << bin2dec("2") << endl;
    int x = 20;
    x = x << 1;
    cout << x;
    return 0;
}
/*
Actually, it still works perfectly! It’s a common intuition to think the leading zeros will "break" the math, but let's trace it carefully.

When we see a `0` at the start, we are just doing . The result stays **0** until we hit the first `1`.

### Let's trace `00011` (Decimal 3)

Step,Char c,Calculation: (ans << 1) + digit,New ans

1  '0'  (0×2)+0   0
2  '0'  (0×2)+0   0
3  '0'  (0×2)+0   0
4  '1'  (0×2)+1   1
5  '1'  (1×2)+1   3

### Why it is robust

1. **Leading Zeros:** As you can see, leading zeros just keep the `ans` at zero. They effectively "do nothing" to the final value, which is exactly what leading zeros are supposed to do in any number system.
2. **The "Shift" is relative:** The multiplication by 2 only starts "growing" the number once `ans` becomes non-zero.
3. **Mathematical proof:**
Your method: 
Horner's method: 

### Why this is safer for Interviews

In many LeetCode problems (like **"String to Integer (atoi)"** or **"Reverse Integer"**), you have to handle strings with leading spaces or zeros. This "Left-to-Right" approach handles them naturally without you having to write extra `if` statements to skip them.

**Would you like to try writing the code for a different base, like Hexadecimal (Base 16), using this same "Left-to-Right" logic?**
*/

// 100
// 1100100

// 1   (0*2)+1=1
// 1   (1*2)+1=3
// 0   (3*2)+0=6
// 0   (6*2)+0=12
// 1   (12*2)+1=25
// 0   (25*2)+0=50
// 0   (50*2)+0=100


// Think of the number 1101.
//  In your right-to-left method, you determine the "weight" of each bit immediately
// (1, 2, 4, 8) and then add them.
// 
// In the left-to-right (Horner's) method, you don't know the weight yet,
// so you just keep doubling the "current sum."
// 
// By the time you reach the end, the first 1 you encountered has been doubled 3
// times, effectively giving it a weight of 2^3 (or 8).


