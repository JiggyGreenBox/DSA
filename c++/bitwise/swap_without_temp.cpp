#include <iostream>
#include <vector>

using namespace std;

int main() {

    int a = 5;
    int b = 7;

    // swap without temp
    cout << a;
    cout << b;
    cout << endl;

    /*
    a = 5 = 0101
    b = 7 = 0111

    a = a^b
    0101 = 5  a
    0111 = 7  b
    0010 = 2  a^b
    a = 2

    b = a^b
    0010 = 2  a
    0111 = 7  b
    0101 = 5  a^b
    b = 5

    a = a^b
    0010 = 2  a
    0101 = 5  b
    0111 = 7  a^b
    a = 7
    */

    a = a^b; // a = 2
    b = a^b; // b = 5
    a = a^b; // a = 7

    cout << a;
    cout << b;
    cout << endl;


    return 0;
}

// 001
// 010


// 110 not a
// 101 not b

// 011 xor 1+2
// 010 xor b
// 001
