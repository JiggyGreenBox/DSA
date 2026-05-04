#include <iostream>
using namespace std;


struct A {
    // void f() { cout << "A" << endl; }
    virtual void f() { cout << "A" << endl; } // evaluated at run time
};

struct B : A {
    // void f() { cout << "B" << endl; }
    void f() override { cout << "B" << endl; } // evaluated at run time

    // virtual void f() { cout << "B" << endl; } // also valid

};


void g(A& a) { a.f(); }     // "B"
void h(A* a) { a->f(); }    // "B"
void i(A  a) { a.f(); }     // "A" cast to A
                            // does not work with pass-by-value

int main(){
    A a;
    B b;
    g(a);       // A
    g(b);       // B

    h(&b);      // B
    i(b);       // A
}