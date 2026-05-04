#include <iostream>
#include <vector>

using namespace std;

int main() { 

    vector<int> v = {};
    v.reserve(100);
    // cout << v.capacity() << endl; // 100
    
    
    for(int i=0; i<100; ++i){
        v.push_back(i);
    }

    cout << v.size() << endl;       // 100
    cout << v.capacity() << endl;   // 100

    v.push_back(1);

    cout << v.size() << endl;       // 101
    cout << v.capacity() << endl;   // 200
    
    

    return 0;
}

