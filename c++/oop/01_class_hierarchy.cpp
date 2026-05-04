#include <iostream>
using namespace std;

struct A {
    int a_val;
};



struct B : A {
    int b_val;
};


int main(){


    A a1_obj;
    cout << a1_obj.a_val << endl;

    B b1_obj;
    cout << b1_obj.a_val;
    cout << b1_obj.b_val;

    A a2_obj;
    a2_obj = b1_obj;

    a2_obj.a_val;
    // a2_obj.b_val; // not accessible

    B b2_obj;
    b2_obj = b1_obj;
    b2_obj.b_val;

    // B b3_obj = a1_obj; // not possible
    // no suitable user-defined conversion from "A" to "B" exists
    B& b_ref = b1_obj;

    // B& b_ref2 = a1_obj; // not possible

    A& a_ref = a1_obj;
    A& a_ref2 = b1_obj;

}

