#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& nums){
    int n = nums.size();
    int i = -1;
    int j = n;
    int pivot = nums[0];
    cout << "pivot: " << pivot << endl;

    while(true){
        do {
            i++;
            cout << nums[i] << " < " << pivot << endl;
        } while(nums[i] < pivot);


        do {
            j--;
            cout << nums[j] << " > " << pivot << endl;
        } while(nums[j] > pivot);

        if(i>=j) return j;

        cout << "swap: " << nums[i] << " : "<< nums[j] << endl;
        swap(nums[i], nums[j]);

        for (auto x:nums) cout << x << " ";         
        cout << endl;
    }
}

int main(){
    vector<int> arr = {5, 3, 8, 4, 2, 7, 1, 10};
    cout << partition(arr) << endl;

    for (int i = 0; i < arr.size(); i++) 
        cout << arr[i] << " "; 
    return 0;
}