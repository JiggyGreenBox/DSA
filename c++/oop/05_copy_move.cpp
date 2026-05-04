#include <iostream>
#include <memory>
using namespace std;

struct Foo {
    int instance;
    Foo(int x) : instance(x) { cout << "Foo #: " << instance << " created" << endl; }
    ~Foo() { cout << "Foo #: " << instance << " destroyed" << endl; }
    void hello() { cout << "Hello from Foo #: " << instance << endl; }

    // copy constructor
    Foo(Foo& other){
        cout << "copy constructor" << endl;
        
        this->instance = other.instance;

        cout << "copied instance from " << this->instance << endl;              
    }
    // copy assignment
    Foo& operator=(Foo& other){ 
        cout << "copy assignment" << endl;
        // cout << "changed instance from " << this->instance;
        // cout << " to "<< other.instance << endl;
        this->instance = other.instance;        
        return *this;
    }

    Foo(Foo&& other){ 
        this->instance = other.instance;   
        cout << "move constructor" << endl;
    }
    Foo& operator=(Foo&& other){
        cout << "move assignment" << endl; 
        
        this->instance = other.instance;        

        cout << "changed instance from " << this->instance;
        cout << " to "<< other.instance << endl;
        return *this;
    }
};

int main(){        
    
    Foo f1(1);
    
    Foo f2(f1); // copy constructor
    
    Foo f3(99);
    f3 = f1;  // copy assignment

    Foo f4(std::move(f1)); // move constructor

    Foo f5(101);
    f5 = std::move(f1);  // move assigment

    return 0;
}