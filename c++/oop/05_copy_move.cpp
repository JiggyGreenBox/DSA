#include <iostream>
#include <memory>
using namespace std;

struct A {
    A() {cout << "default constructor" << endl;}
    A(const A& other) {
        cout << "copy" << endl;
    }
};

void f(A a) {} // pass-by-value (copy)

A g1(A& a) {return a;}

A g2() {return A();}

// ===================================================================
struct Foo {
    int instance;
    Foo(int x) : instance(x) { cout << "Foo #: " << instance << " created" << endl; }
    ~Foo() { cout << "Foo #: " << instance << " destroyed" << endl; }
    void hello() { cout << "Hello from Foo #: " << instance << endl; }

    // copy constructor
    Foo(Foo& other){
        cout << "copy constructor" << endl;
        
        this->instance = other.instance;

        cout << "\tcopied instance from " << this->instance << endl;
    }
    // copy assignment
    Foo& operator=(Foo& other){ 
        cout << "copy assignment" << endl;
        cout << "\tcopied instance from " << other.instance << endl;        
        this->instance = other.instance;        
        return *this;
    }

    Foo(Foo&& other){ 
        this->instance = other.instance;   
        cout << "move constructor" << endl;
        cout << "\tmoved instance from " << other.instance << endl;
    }
    Foo& operator=(Foo&& other){
        cout << "move assignment" << endl; 
        
        this->instance = other.instance;        

        // cout << "changed instance from " << this->instance;
        // cout << " to "<< other.instance << endl;
        cout << "\tmoved instance from " << other.instance << endl;
        return *this;
    }
};

int main() {

    A a;
    A b = a; // direct initialization using the copy constructor
    A c(b);  // direct initialization
    f(b);    // copy constructor (argument)
    g1(a);   // copy constructor (return value)

                    // What happens inside: The function takes a by reference (A& a), so no
                    // copy happens when entering the function.  The Return Trigger:
                    // However, the function specifies that it returns by value (A).
                    // Because it promises to hand back a brand-new, independent A object
                    // to the outside world, it has to create a copy of a before it
                    // destroys the function's local scope.  Why it calls the copy
                    // constructor: To create that temporary return object, C++ looks at
                    // the source (a) and initializes the return value using A(const A&
                    // other). 

                    // Even though you don't catch the return value in a variable (you just
                    // write g1(a);), that temporary object is still fully constructed on
                    // the return line, and then immediately destroyed.

    A d = g2(); // RVO , doesnt print copy, uses default constructor
                    // The Old School Way (Without Optimization)                    
                    // A() creates a temporary object inside g2().
                    // return A(); copies that temporary into a "return slot" for the caller.
                    // A d = g2(); copies that "return slot" into the variable d.

            // Compilers realized that all this copying is a massive waste of time.
            // Under RVO, the compiler looks ahead and says: "Hey, instead of
            // creating a temporary object inside the function and copying it out,
            // I'm just going to construct the object directly inside d's memory
            // slot to begin with."  Because of this, the copy constructor is
            // bypassed entirely.




    // ===================================================================
    
    Foo f1(1);
    
    Foo f2(f1); // copy constructor
    
    Foo f3(99);
    f3 = f1;  // copy assignment

    Foo f4(std::move(f1)); // move constructor

    Foo f5(101);
    f5 = std::move(f1);  // move assigment

    return 0;
}