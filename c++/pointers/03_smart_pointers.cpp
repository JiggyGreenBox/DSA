#include <iostream>
#include <vector>
#include <memory>
#include <vector>
using namespace std;


// ============================================================================
struct Foo {
    int instance;
    Foo(int x) : instance(x) { cout << "Foo #: " << instance << " created" << endl; }
    ~Foo() { cout << "Foo #: " << instance << " destroyed" << endl; }
    void hello() { cout << "Hello from Foo #: " << instance << endl; }
};

// ============================================================================

int main(){
    shared_ptr<Foo> f1 = make_shared<Foo>(1);
    cout << f1.use_count() << endl; // 1

    shared_ptr<Foo> f2 = f1;
    cout << f1.use_count() << endl; // 2

    shared_ptr<Foo> f3 = make_shared<Foo>(2);
    cout << f3.use_count() << endl; // 1


    {
        shared_ptr<Foo> f3 = make_shared<Foo>(3);        
    }// #3 destroyed here    


    

    cout << "before return" << endl;
    return 0;
} // #1 and #2 destroyed here