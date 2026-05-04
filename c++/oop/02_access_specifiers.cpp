#include <iostream>
using namespace std;


struct A1 {
// public:
    int value; // struct, public by default
protected:
    void f1(){}
private:
    void f2(){}
};

class A2 {
    int value; // class, private by default
};


struct B1 : A1 {
    void h1(){ f1(); }
    // void h2(){ f2(); } // inaccessible
};


int main(){
    A1 a1;
    a1.value;
    // a1.f1(); // inaccessible
    // a1.f2(); // inaccessible

    A2 a2;
    // a2.value; // incaccessible
}


