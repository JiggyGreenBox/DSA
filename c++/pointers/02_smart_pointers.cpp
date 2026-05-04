#include <iostream>
#include <vector>
#include <memory>
using namespace std;


// ============================================================================
struct Foo {
    int instance;
    Foo(int x) : instance(x) { cout << "Foo #: " << instance << " created" << endl; }
    ~Foo() { cout << "Foo #: " << instance << " destroyed" << endl; }
    void hello() { cout << "Hello from Foo #: " << instance << endl; }

    // Foo(Foo&& other){ cout << "pointer moved" << endl; }
    Foo& operator=(Foo&& other){ cout << "object moved" << endl; }
};

// ============================================================================

int main(){
    // std::unique_ptr<Foo> f1 = std::make_unique<Foo>();
    unique_ptr<Foo> f1 = make_unique<Foo>(1);
    f1->hello();

    // this replaces
    Foo* f2 = new Foo(2);
    f2->hello();


    

    cout << "hello from main" << endl;

    // Drawback 1:
    //      need to delete maunally
    // delete f2; // only way to call destructor

    // Drawback 2:
    //      cant keep a count of pointers
    Foo* f3 = f2;
    delete f2;
    f3->hello();    // undefined behaviour, object is deleted
                    // Hello from Foo #: 1431655787

    // Advantage 1:
    //      pointer count can be controlled with unique/shared
    // unique_ptr<Foo> f3 = f1; // copy not allowed
    unique_ptr<Foo> f4 = std::move(f1); // move allowed


    {
        vector<unique_ptr<Foo>> foos;
        for(int i=100; i<103; i++){
            foos.push_back(make_unique<Foo>(i));
        }
    } // #100,#101,#102 destroyed here

    return 0;
} // f1 is destroyed automatically, but not f2