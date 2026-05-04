#include <iostream>
#include <vector>

using namespace std;

int main() {

    vector<int> v = {1,3,2,4,5,6,2,1,2,3,2,1,2,3,4};

    // count_sort_dry_run(v);

    cout << "[" ;
    for(auto x:v) {
        cout << x << ",";
    }
    cout << "]" << endl;
    return 0;    
}