#include <iostream>
using namespace std;

int add(int a, int b) {
    return (a+b);
}


void n(){
    cout << "n" << endl;
}

void (*f())(){
    return n;
}

int (*g())(int,int){
    return add;
}


int (*(*z())())(int,int){
    return g;
}


int main() {
    
    auto x = f();
    
    auto y = g();
    
    // cout << add(1,2) << endl;
    x();
    
    cout << y(1,2) << endl;
    
    auto a1 = z();
    auto a2 = a1();
    cout << a2(3,4) << endl;

    return 0;
}