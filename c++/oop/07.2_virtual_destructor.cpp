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

/*

refer to the 07.1 to understand the need for virtual functions
now with virtual destructors,
we need to make sure that we dont miss a destructor due to static/early binding
and cause a memory leak
*/

class Base {
public:
    Base() {
        cout << "Base constructor" << endl;
    }
    // virtual ~Base() {
    ~Base() {
        cout << "Base destructor" << endl;
    }
};

class Derived : public Base {
private:
    int* data;
public:
    Derived() {
        cout << "Derived constructor" << endl;
        data = new int[100];
    }
    ~Derived() {
        cout << "Derived destructor" << endl;
        delete[] data;
    }
};

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

    Base *ptr = new Derived(); // upcasting
    delete ptr; // memory leak, derived data not deleted
    return 0;

    /*
        Adding the virtual keyword to the base class destructor triggers dynamic
        binding. The program checks the VTable of the actual object at runtime,
        ensuring the destructor chain executes in the correct reverse order. 
    */
}