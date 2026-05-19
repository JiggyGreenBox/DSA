#include <iostream>
using namespace std;


class A {
public:
    void f() {
        cout << "f() from A, base" << endl;
    }
};

class B : public A {
    public:
        void f() {
            cout << "f() from B, derived" << endl;
        }
};


class A_wt_virtual {
public:
    virtual void f() {
        cout << "f() from A virtual, base" << endl;
    }
};

class C : public A_wt_virtual {
public:
    void f() {
        cout << "f() from C, derived" << endl;
    }
};

void use_f(A *a) {
    a->f();
}

void use_f2(A_wt_virtual *a) {
    a->f();
}

int main() {
    A base;
    B derived;
    
    
    base.f();    // f() from A, base
    derived.f(); // f() from B, derived

    // dynamic dispatch is not happening
    // compiler looks at the types
    // since use_f() takes the A/base pointer
    // it cant dynamically understand, to use derived f()
    // in this case early binding, static binding has happened
    use_f(&base);    // f() from A, base
    use_f(&derived); // f() from A, base

    A_wt_virtual base_wt_virtual;
    C derived_wt_virtual;

    // here at runtime using vtables,
    // f() from derived was called,
    // even tho base pointer was passed
    use_f2(&base_wt_virtual);       // f() from A virtual, base
    use_f2(&derived_wt_virtual);    // f() from C, derived
}