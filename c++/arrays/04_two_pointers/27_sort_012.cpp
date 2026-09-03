#include <iostream>
#include <vector>

using namespace std;

/*
0 ... low-1       = 0s
low ... mid-1     = 1s
mid ... high      = unknown
high+1 ... n-1    = 2s


*/
void sortZeroOneTwo(vector<int>& nums) {
    // brute force
    // scan once and keep a count of all
    // then replace

    // optimal Solution
    // have 3 pointers
    // i for 0
    // j for 1
    // k for 2
    // keep k at the end

    int n = nums.size();
    int i = 0;
    int j = 1;
    int k = n -1;

    // when the crossover happens the vector is sorted
    while(i<=k && j<=k) {
        if(nums[k] == 0){            
            cout << nums[k] << endl;
            swap(nums[i++], nums[k]);
            while(i<n && nums[i] == 0) ++i;
        }                
        else if(nums[k] == 1){
            cout << nums[k] << endl;            
            swap(nums[j++], nums[k]);
            while(j<n && nums[j] == 1) ++j;
        }
        else{
            cout << nums[k] << endl;
            --k;
            while(k>0 && nums[k] == 2) --k;
        }            
    }
}


void sortZeroOneTwo2(vector<int>& nums) {    
    int n = nums.size();
    int i = 0, j = 1, k = n - 1;

    // when the crossover happens the vector is sorted
    while(j<=k) {
        if(nums[j] == 0) {
            swap(nums[i], nums[j]);
            i++;j++;
        }                
        else if(nums[j] == 2){
            swap(nums[j], nums[k]);
            k--;
        }
        else{
            j++;
        }
    }
}



int main() {
    vector<int> v = {2,1,0,2,1,0,2,1,0,2,1,0,2,1,0};
    // vector<int> v = {2,2,2,1,1,1};
    // vector<int> v = {2,2,2,0,0,0};
    // vector<int> v = {1,1,1,0,0,0};
    // vector<int> v = {2,1,0,2,1,0,2,1,0};
    // vector<int> v = {2,1,0,2,1,0,2,1,0,2,1,0};

    v = {1,0,1,0,1,0};

    // sortZeroOneTwo(v);
    sortZeroOneTwo2(v);

    for(auto x:v){
        cout << x << " ";
    }
    return 0;
}