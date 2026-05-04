#include <iostream>
#include <vector>
#include <memory>
using namespace std;


// ============================================================================
void good_stack(){
    int a = 5;    
    int* p = &a;
    // delete p; // delete is for memory created by new
} // a and p are destroyed

void good_heap(){
    int* p = new int(99);
    // *p = 5;
    // cout << *p << endl;
    delete p;
} // p is destroyed destroyed

int* bad_raw_dangling_pointer(){
    int a = 5;
    return &a;
}

// ============================================================================

int main(){
    good_stack();
    good_heap();

    int* p = bad_raw_dangling_pointer();
    // cout << *p << endl; // segmentation fault

    return 0;
}