#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
Find Peak Element - II
    Given a 0-indexed n x m matrix mat where no two adjacent cells are 
    equal, find any peak element mat[i][j] and return the array [i, j].A 
    peak element in a 2D grid is an element that is strictly greater than 
    all of its adjacent neighbours to the left, right, top, and bottom.

    Assume that the entire matrix is surrounded by an outer perimeter 
    with the value -1 in each cell.

    Note: As there can be many peak values, 1 is given as output if the 
    returned index is a peak number, otherwise 0.


    Example 1
        Input: mat=[[10, 20, 15], [21, 30, 14], [7, 16, 32]]
        Output: [1, 1]
        Explanation: The value at index [1, 1] is 30, which is a peak element 
        because all its neighbours are smaller or equal to it. Similarly, {2, 
        2} can also be picked as a peak.

    Example 2
        Input: mat=[[10, 7], [11, 17]]
        Output : [1, 1]
        Explanation:The value at index [1, 1] is 17, which is the only peak 
        element because all its neighbours are smaller or equal to it.
*/



/*
no 2 adjacent cells are equal
    assume -1 border
    so starting at the border reduces comparisons

    start any corner
    move towards the greater element

    lets start top right

    dirs = [down, left, up, right]
    int max = -1;
    for(dir in dirs)
        if(n[dir] > curr)
            max = ...
        if max == -1 return
        curr = max

can we try a bsearch like approach


[10, 20, 15]
[21, 30, 14]
[ 7, 16, 32]
30 and 32


[1, 2, 3]
[4, 5, 6]
[7, 8, 9]


[1, 2, 3, 8, 0, 5]
[4, 5, 6, 8, 0, 5]
[7, 8, 9, 8, 0, 5]


take mid col
find max
    now up and down dont matter

    if > left and > right, max is peak

    if left larger
        peak in left
    else if right is larger
        peak in right
*/

/*
-------------------------------------------------
Pick middle column.

Choose maximum element in that column.

Vertical neighbours are automatically smaller.

If left neighbour is larger:
    peak exists in left half.

If right neighbour is larger:
    peak exists in right half.

Otherwise:
    current element is a peak.

-------------------------------------------------
    Notice how similar this is to 1D Peak Element:
        nums[mid] < nums[mid-1]
            go left

        nums[mid] < nums[mid+1]
            go right

        otherwise
            peak

    The only extra work in 2D is:
        convert the column into a 1D problem
        by first taking the column maximum
-------------------------------------------------

int mr = ..
int mc = ..
low=0
high=mc-1

while() {
    int mid = low + (high-low)/2;

    int row_idx = -1
    for(int i=0; i<mr; i++) {
        // find max
        row_idx = ..
    }

    if(mid > 0 && mat[row_idx][mid] < mat[row_idx][mid-1]) {
        high = mid - 1;
    }
    else if(mid < mc-1 && mat[row_idx][mid] < mat[row_idx][mid+1]) {
        low = mid + 1;
    }
    else {
        return {row_idx, mid};
    }
}
*/

vector<int> findPeakGrid(vector<vector<int>>& mat) {}

int main() {

    // vector<vector<int>> v = {{1,1,1,1},{2,2,2,2},{3,3,3,3}};
    vector<vector<int>> v = {{1,  3,  8},
                             {2,  3,  4},
                             {1,  2,  5}};



    // 1,1,2,2, 3, 3,4,5,8

    int elements = 0;
    int check = 4;
    for(auto row : v) {        
        auto it =  upper_bound(row.begin(), row.end(), check);        
        elements += distance(row.begin(), it);
    }
    cout << elements << endl;


    return 0;
}