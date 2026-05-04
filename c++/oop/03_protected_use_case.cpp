#include <iostream>
using namespace std;

class Base {
protected:
    int protectedValue;   // accessible in derived class
private:
    int privateValue;     // NOT accessible in derived class
public:
    Base() : protectedValue(10), privateValue(20) {}
};

class Derived : public Base {
public:
    void show() {
        cout << "Protected Value: " << protectedValue << endl;
        // cout << privateValue;  ❌ Error: privateValue not accessible
    }

    void change_val(int val){
        protectedValue = val;
    }
};

int main() {
    Derived d;
    d.show();

    // cout << d.protectedValue; ❌ Error: not accessible outside the class hierarchy

    // d.protectedValue = 100; // not accessisble
    d.change_val(100);
    d.show();
    
}
