#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

	void merge(vector<int>& nums, int start, int mid, int end){
		// merge 2 sorted arrays
		// start..mid, mid+1..end
		vector<int> temp(end-start+1);

		int i = start;
		int j = mid+1;
		int k = 0;

		for(auto x:temp){cout << x << " ";}
		cout << endl;

		//   cout << "process: ";;
		//   cout << start;
		//   cout << " | ";
		//   cout << mid;
		//   cout << " | ";
		//   cout << end;
		//   cout << endl;
		//   cout << endl;

		while(i<=mid && j<=end) {
		if(nums[i] < nums[j]){
			cout << nums[i] << " : " << nums[j] << endl;
			temp[k++] = nums[i++];
		}
		else{
			cout << nums[j] << " : " << nums[i] << endl;
			temp[k++] = nums[j++];
		}
		}
		while(i<=mid){ // if only j is remaining, array was sorted, but if i is remaining some swaps happened
			temp[k++] = nums[i++];
		}
		while(j<=end){ // if only j is remaining, array was sorted, but if i is remaining some swaps happened
			temp[k++] = nums[j++];
		}

		for(auto x:temp){cout << x << " ";}
		cout << endl;

		// copy temp back to nums
		k = start;
		for(int i=0; i<temp.size();i++){        
			nums[k++] = temp[i];
		}
	}

	void merge_s(vector<int>& nums, int start, int end){

		if(start >= end) return;

		int mid = start + (end-start)/2;

		cout << "process: ";;
		cout << start;
		cout << " | ";
		cout << mid;
		cout << " | ";
		cout << end;
		cout << endl;
		cout << "process: ";;
		cout << nums[start];
		cout << " | ";
		cout << nums[mid];
		cout << " | ";
		cout << nums[end];
		cout << endl;		
		cout << endl;

		merge_s(nums, start, mid);
		merge_s(nums, mid+1, end);
		merge(nums, start, mid, end);
	}
	

	vector<int> mergeSort(vector<int>& nums) {
		// merge sort needs extra space to store swaps
		// log n, split the array and sort both and merge both
		merge_s(nums, 0, nums.size()-1);
		return nums;
	}
};


int main(){
	Solution sol;

	// vector<int> v = {7, 4, 1, 5, 3};
	vector<int> v = {2,17,-6,-49,47,-34,7,32,15,-14,-10,45,6,22,10,34,3,-37,-28,11,-16,42,-42,-4,19,37,45,-32,-3,3,-34,-16,28,-38,25,27};

	sol.mergeSort(v);

	for(auto x:v){cout << x << " ";}
	cout << endl;

	// -49 -42 -38 -37 -34 -34 -32 -28 -16 -16 -14 -10 -6 -4 -3 2 3 3 6 7 10 11 15 17 19 22 25 27 28 32 34 37 42 45 45 47
	return 0;
}
