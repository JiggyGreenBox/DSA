#include <iostream>
using namespace std;


struct A {
    A() { cout << "A constructor" << endl; }

    // ~A() { cout << "A destructor" << endl; }
    virtual ~A() { cout << "A destructor" << endl; }
};

struct B : A {
    B() { cout << "B constructor" << endl; }

    ~B() { cout << "B destructor" << endl; }
};

void destroy(A* a) {
    delete a; // since the destructor is not virtual it will call ~A() instead of ~B(), if B* is passed
}

int main(){
    
    // B b;
        // A constructor
        // B constructor
        // B destructor
        // A destructor

    B* b = new B();
    destroy(b);
        // A constructor
        // B constructor
        // A destructor
    // B destructor MISSING
}