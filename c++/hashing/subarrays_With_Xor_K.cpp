#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


// nums[L] ^ nums[L+1] ^ ... ^ nums[R] = px[R] ^ px[L-1]
// xor(L,R) = px[R] ^ px[L-1]
// we want xor(L,R) == k for each L,R combination

// px[R] ^ px[L-1] = k

// px[L-1] = k ^ px[R] 

// for R if we find px[L-1] then we add this count
// if k == R then 
// we add {0:1} to the map

// At index i, prefix XOR is xorr.

// Subarray (L..i) has XOR = k iff px[L-1] = xorr ^ k.

// So we only need to count how many px[L-1] are equal to xorr ^ k.

int subarraysWithXorK(vector<int>& nums, int k) {
    int n = nums.size();
    int xor_count = 0;
    unordered_map<int, int> mpp; // xor, xor_count

    mpp[0] = 1;
    
    int xorr = 0;
    for(int i=0; i<n; i++){
        cout << xorr << " ^ " << nums[i] << " = "; 
        xorr = xorr ^ nums[i];
        cout << xorr << endl;

        // either we find k by xor
        // or we find L-1 by xor with k
        if(mpp.find(xorr^k) != mpp.end()){
            cout << "\t" << xorr << " ^ " << k << " = " << (xorr^k);
            cout << " found in mapp with count: " << mpp[xorr^k] << endl;
            xor_count += mpp[xorr^k];
            cout << "\txor_count: " << xor_count << endl;
        }        
        
        mpp[xorr]++;
    }


    for(auto pair : mpp){
        cout << pair.first << " | " << pair.second << endl;
    }
    // int x = 5^5;
    // cout << x << endl;

    cout << "XOR-Count :" << xor_count << endl;

    return xor_count;
}

int main(){
    vector<int> v = {4, 2, 2, 6, 4};
    int k = 6;

    // vector<int> v = {5, 6, 7, 8, 9};
    // int k = 5;
    
    cout << subarraysWithXorK(v, k) << endl;
    return 0;
}