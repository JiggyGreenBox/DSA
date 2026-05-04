#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int>& v){
    cout << "[ ";
    for(auto x:v) cout << x << " ";
    cout << "]\n";
 
}

int upperBound(vector<int> &nums, int x){
    int start = 0;
    int end = nums.size();

    while(start < end) {
        int mid = start + (end - start)/2;
        cout << "start: " << start << " | end: " << end << endl;
        cout << "\tmid: " << mid<< " | " << nums[mid] << endl;

        if(nums[mid] <= x){
            start = mid + 1;
        }
        else{
            end = mid - 1;
        }
    }
    return start;
}

int upperBound2(vector<int> &nums, int x){

    print(nums);

    int start = 0;
    int end = nums.size();

    while(start < end) {
        int mid = start + (end - start)/2;
        cout << "start[" << start << "]: " << nums[start] << " | ";
        cout << "mid[" << mid << "]: " << nums[mid] << " | ";
        cout << "end[" << end << "]: " << nums[end] << endl;

        if(nums[mid] > x){
            end = mid;
        }
        else{
            start = mid+1;
        }
    }
    string line(50, '-');
    cout << line << endl;
    return start;
}

int main(){
    vector<int>  v = {3,5,8,15,19};int x = 0;
    
    // vector<int>  v = {1,2,2,3};int x = 2;
    
    cout << upperBound2(v, x) << endl;

    cout << upperBound2(v, 8) << endl;




    return 0;
}