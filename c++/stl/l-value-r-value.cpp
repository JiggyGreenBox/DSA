#include <iostream>
#include <vector>
using namespace std;

/*
1. L-values (Locator Value)

    An L-value is an expression that refers to a specific,
    persistent memory location and can appear on the left-hand side of an
    assignment (the 'L' traditionally stands for "left").

    get the address using the & operator

    can be assigned a new value, unless const L-value

    int a = 10;
    int b = 5;

    a = b;      // a (L-value) assigned b (L-value)
    a = 20;     // a (L-value) assigned 20 (R-value)
    &a;         // Valid: can take the address of a


2. R-values (Reader Value)

    An R-value is an expression that results in a temporary
    value that does not persist beyond the current expression and
    therefore cannot appear on the left-hand side of an assignment (the
    'R' traditionally stands for "right"). R-values are
    essentially temporary results.

    Non-identifiable: Does not have a persistent name or
    memory address beyond its use. 

    Non-addressable: You generally
    cannot take its address. 

    Temporary: Its value exists only until
    the end of the full expression.



    int a = 10;
    int b = 5;

    a = a + b;  // a (L-value) assigned result of (a + b) (R-value)

    // ❌ Invalid: Cannot assign to a temporary value
    // a + b = 20;

    // ❌ Invalid: Cannot take the address of a temporary value
    // &(a + b); 


*/
void accepts_copy(int a){
    a += 5;
    cout << a <<endl;
}

void accepts_lvalue(int& a){
    a += 5;
    cout << a <<endl;
}

// const lvalue reference can bind to an rvalue
// this allows literals to be passed
void accepts_const_lvalue(const int& a){
    // a += 5; // cant modify const
    cout << a <<endl;
}


// Since int is a trivial type (it has no resources to
// steal), the difference is purely in what the function can accept:
void accepts_rvalue(int&& a){    
    a+=5;
    cout << a <<endl;
}


int main() {
    int a = 1;
    accepts_copy(a); // 6
    accepts_copy(2); // 7

    a=1;
    accepts_lvalue(a); // 6
    // accepts_lvalue(2); // initial value of reference to non-const must be an lvalueC/C++(461)

    a=1;
    accepts_const_lvalue(a); // 1
    accepts_const_lvalue(2); // 2

    a=1;
    accepts_rvalue(20+5); // 25 is an R-value (temporary result)
    // accepts_rvalue(a); // an rvalue reference cannot be bound to an lvalueC/C++(1768)
    accepts_rvalue(std::move(a)); // 6
    return 0;
}