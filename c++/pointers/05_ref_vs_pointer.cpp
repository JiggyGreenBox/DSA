#include <iostream>
#include <memory>
using namespace std;

int main(){

    // pointer can be reassigned
    int x=5;
    int y=7;
    int *p = &x; // p points to a
    p = &y;      // p points to b

    cout << *p << endl;
    cout << x << endl;
    cout << y << endl;

    // reference cannot be reassigned
    int a = 99;
    int b = 100;

    int &ref = a;
    ref = b; // ref=a so now a=b
    cout << ref << endl;    // 100
    cout << a << endl;      // 100 a=b not 99
    cout << b << endl;      // 100


    



    return 0;
}