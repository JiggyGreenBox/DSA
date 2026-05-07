#include <iostream>
#include <vector>

using namespace std;


// choose a key [1..n-1]
// compare with [key-1..0]
// insert into correct position
//      when the postion is found copy every other element forward
// every element before the key will be sorted
// repeat till the key is the last element

// ideally we grow from [0] to [0..n-1]
// add a key, and insert it 
// the key is the last element
// if any element is greater than the key
// we make space for it
// we copy backwards one position
// n[j+1] = n[j]
// then insert the key

void print(const vector<int>& v) {
    for(auto x: v) cout << x << " ";
    cout << "\n";
}

void insertion_sort_dry_run(vector<int>& vec) {

    print(vec);

    int n = vec.size();
    if(n < 2) return;

    int key;

    // select keys from the second element till the last
    for(int i=1; i<n; i++) {
        key = vec[i];

        cout << "key at index: ["
             << i
             << "] : "
             << key << endl;

        // compare key backwards till first element to find the insert point
        // lets not use a for loop because everything is sorted before this
        int j = i-1;
        cout << "j: [" << j  << "]" << endl;
        while(j>=0 && vec[j] > key) {
            cout << "\t"<<vec[j] << " > " << key << endl;
            vec[j+1] = vec[j];
            j--;
        }
        cout << "insert key at index: ["
             << j+1
             << "]"
             << endl;
        vec[j+1] = key;

        print(vec);
    }

    return;
}


/*

good for partially sorted datasets
start from the second element, consider the first as sorted

stable, inplace


for 1..n-1
    choose a key = arr[i]

    we want to create a slot
    everything left will be < key
    everything to the right of slot will be > key

    from j-1..0
        we copy ahead if > key
        while arr[j] > key:
            arr[j+1] = arr[j]
        
        j will stop at either -1 or where < key
        so arr[j+1] = key


*/
void insertion_sort(vector<int>& vec) {
    int n = vec.size();
    if(n < 2) return;

    for(int i=1; i<n; i++) {
        int key = vec[i];

        int j = i-1; // we go barkwards till zero

        // the goal is to move everything 
        // and to INSERT the key in the right place

        while(j>=0 && vec[j] > key) {
            vec[j+1] = vec[j]; // move 1 ahead
            j--;
        }
        vec[j+1] = key;
    }

    return;
}

int main() {
    vector<int> v = {3,4,1,2,5,6};

    insertion_sort_dry_run(v);

    for(auto x:v) {
        cout << x << endl;
    }
    return 0;
}
