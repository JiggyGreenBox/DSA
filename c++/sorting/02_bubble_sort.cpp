// #include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;


void bubble_sort_dry_run(vector<int>& vec){
    int n = vec.size();

    // place the largest number at the back
    // repeat backwards till the first element

    // we need to compare 2 adjacent numbers
    // swap
    // last element will be the greatest element
    // now we move to the second last position
    // repeat till the end
    // 
    // first loop is the reducing condition
    // second loop starts from 0 till dynamic-last-element

    bool swapped = false; // optimize, 
    // if there were no swaps in the first run, 
    // there wont be any on the second run either
    
    for(int i=0; i<n-1; i++) { // why dont we i<n, because then i=n-1, then j<(n-1-(n-1)), which is j<0, useless!
        
        for(int j=0; j<(n-i-1); j++) {
            cout << "compare: " << vec[j] << " - " << vec[j+1] << endl;

            if(vec[j] > vec[j+1]) {
                cout << "\tswap: " << vec[j] << " - " << vec[j+1] << endl;
                swapped = true;
                // swap(vec[j] ,vec[j+1]);
            }
        }

        if(!swapped){
            cout << "already sorted, early exit" << endl;
            return;
        }
        cout << endl;
        cout << endl;
    }
    return;
}


void bubble_sort(vector<int>& vec){

    int n = vec.size();
    bool swapped = false;
    

    for(int i=0; i<n-1; i++) 
    {
        
        for(int j=0; j<(n-i-1); j++) 
        {
            if(vec[j] > vec[j+1]) {
                
                swap(vec[j] ,vec[j+1]);
                swapped = true; // early exit, sorted already
            }
        }

        if(!swapped) return; // early exit, sorted already
    }
    return;
}

int main() {
    vector<int> v = {100,2,3,4};

    // bubble_sort_dry_run(v);
    bubble_sort(v);

    for(auto x:v){
        cout << x << endl;
    }
    
    return 0;
}