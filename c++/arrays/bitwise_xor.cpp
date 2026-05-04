#include <iostream>
#include <vector>

using namespace std;

int main() {
    int x = 5;
    int y = 5;

    int c = x ^ y;
    cout << c << endl;

    vector<int> v = {0,1,2,4};
    int xor1 = 0;    
    for(int i=0; i<=v.size(); i++) {
        xor1 = xor1^i^v[i];                 
    }    
    cout << xor1;
}