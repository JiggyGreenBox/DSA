#include <iostream>
#include <vector>

using namespace std;

// no need to check for sizes
// we can safely put i=0; j=1
// either i is correct or its not

// guarentee of equal num of  pos and neg
// guarentee of even num of elements

// brute force can involve extra space

void print(vector<int>& v){
    for(auto x: v){
        cout << x << " ";
    }
    cout << endl;
}

void rearrange_array_elements_by_sign(vector<int>& nums){
    int n = nums.size();
    int pos=0;
    int neg=0;

    while(pos<n && neg<n){
        while(pos<n && nums[pos]<0) ++pos;  // find pos index
        cout << "\tpos: " << pos << endl;
        while(neg<n && nums[neg]>0) ++neg;  // find neg index
        cout << "\tneg: " << neg << endl;

        // need to write out of place value to correct place
        // need to copy elements forward
        // and insert value in right place

        int store = nums[max(pos,neg)];
        cout << "\tstore: " << store << endl;
        int start = -1;
        if(pos<neg){ // [1,2,3,-1]
            start = pos+1;
        }
        else{        // [-1,-2,-3,1]
            start = neg;
        }
        int end = max(pos,neg);
        cout << "\tstart: "<< start << endl;
        cout << "\tend: "<< end << endl;        

        for(int i=end; i>=start; i--){
            nums[i] = nums[i-1];
        }
        nums[start] = store;

        print(nums);

        pos = min(pos,neg)+2; // min value was in the right place, max was not
        neg = pos;
        cout << "\t\tpos: " << pos << endl;
        cout << "\t\tneg: " << neg << endl;
    }
    return;
}




int main() {
    vector<int> v = {1,2,3,-1,-2,-3};
    // vector<int> v = {-1,-2,-3,1,2,3};
    // vector<int> v = {2, 4, 5, -1, -3, -4};
    // vector<int> v = {1, -1, -3, -4, 2, 3};
    

    print(v);

    rearrange_array_elements_by_sign(v);

    print(v);

    return 0;
}

/*
equal number of positive and negative
i = even, 0
j = odd, 1

when even
    nums[i] = num
    i += 2

when odd
    nums[j] = num
    j += 2

*/