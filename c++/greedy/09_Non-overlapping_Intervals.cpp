#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void print(vector<vector<int>>& intervals){
	for(const auto& interval : intervals){
		cout << interval[0] << " " << interval[1] << endl;
	}
	cout << "\n";
}

int MaximumNonOverlappingIntervals(vector<vector<int>>& Intervals) {

	// print(Intervals);
	sort(Intervals.begin(), Intervals.end(), [](const vector<int>& a, const vector<int>& b){
		if(a[1] == b[1]){
			return a[0] < b[0];
		}
		return a[1] < b[1];
	});
	print(Intervals);

	int prev_end = -1;
	int remove_i = 0;
	for(const auto& i : Intervals) {
		int start   = i[0];
		int end     = i[1];

		// is start greater than previous end?
		// remove this interval
		if(start < prev_end){
			remove_i++;
		}
		else{
			// valid interval
			prev_end = end;
		}

	}
	return remove_i;
}


int eraseOverlapIntervals(vector<vector<int>>& intervals) {

	sort(intervals.begin(), intervals.end(),
			[](const auto &a, const auto &b) {
				return a[1] < b[1];
			});

	int removals = 0;
	int prevEnd = intervals[0][1];

	for (int i = 1; i < intervals.size(); i++) {

		int start = intervals[i][0];
		int end   = intervals[i][1];

		if (start >= prevEnd) {
			prevEnd = end;
		}
		else {
			removals++;
		}
	}

	return removals;
}


int main() {
	vector<vector<int>> intervals = { {1, 2}, {2, 3}, {3, 4}, {1, 3} };    
	cout << MaximumNonOverlappingIntervals(intervals) << endl;

	intervals = { {1, 3}, {1, 4}, {3, 5}, {3, 4}, {4, 5} };
	cout << MaximumNonOverlappingIntervals(intervals) << endl;
	return 0;
}

/*
Non-overlapping Intervals

Given an array of N intervals in the form of (start[i], end[i]), 
where start[i] is the starting point of the interval and end[i] is 
the ending point of the interval, return the minimum number of 
intervals that need to be removed to make the remaining intervals 
non-overlapping.



Note:

Intervals which only touch at a point are also considered as 
non-overlapping. For example, [1, 3] and [3, 4] are non-overlapping.


Example 1

	Input : Intervals = [ [1, 2] , [2, 3] , [3, 4] ,[1, 3] ]

	Output : 1

	Explanation : You can remove the interval [1, 3] to make the 
	remaining interval non overlapping.

Example 2

	Input : Intervals = [ [1, 3] , [1, 4] , [3, 5] , [3, 4] , [4, 5] ]

	Output : 2

	Explanation : You can remove the intervals [1, 4] and [3, 5] and the 
	remaining intervals becomes non overlapping.

Example 3

	Input : Intervals = [ [1, 10] , [1, 4] , [3, 8] , [3, 4] , [4, 5] ]
	Output: 3
*/

/*

observation
	[start, end]
	
	we sort by end
	we want to choose intervals that finish earliest

	if we sort by start
	(1,10)
	(2,3)
	(3,4)
	(4,5)

	we may get large intervals
	so sort by end time
	
	(2,3)
	(3,4)
	(4,5)
	(1,10)
*/

/*

sort by end

	take first interval

	for every remaining interval
		if start >= prevEnd
			keep
			prevEnd = currEnd
		else
			remove

*/