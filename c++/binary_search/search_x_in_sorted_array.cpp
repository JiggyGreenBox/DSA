#include <iostream>
#include <vector>
using namespace std;

void print(const vector<int>& v){
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]" << endl;
}

int b_search(vector<int>& v, int target) {

    print(v);

    int n = v.size();

    int low = 0;
    int high  = n-1;

    while(low < high) {
        
        int mid = low + (high - low)/2;

        cout << "low: ["<< low << "] : " << v[low]
             << " | "
             << "mid: ["<< mid << "] : " << v[mid]
             << " | "
             << "high: ["<< high << "] : " << v[high]
             << endl;

        if(v[mid] == target) return mid;
        else if(v[mid] < target){
            low = mid + 1;
            cout << "next low: ["<< low << "] : " << v[low] << endl;
        }
        else{
            high = mid - 1;
            cout << "next high: ["<< high << "] : " << v[high] << endl;
        }
    }
    return -1;
}

int main(){
    // vector<int> v = {-9109,-6888,-5296,-3183,-1570,-1423,-1186,-380,813,2988,3213,3497,3695,4774,5519,6119,6708,9245,9371,9434,9517};
    // int target = -3183;


    vector<int> v = {0,1};
    int target = 1;

    // why low <= high?
    // because when the array is 2 elements [0,1] low and mid are the same
    // if target is 0 then good but if target is 1 we will miss it
    

    cout << b_search(v, target) << endl;
}