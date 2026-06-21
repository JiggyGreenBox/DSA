#include <iostream>
#include <vector>
using namespace std;

/*

Matrix Median

    Given a 2D array matrix that is row-wise sorted. The task is to find 
    the median of the given matrix.

    Example 1

        Input: matrix=[ [1, 4, 9], [2, 5, 6], [3, 7, 8] ] 
        Output: 5
        Explanation: If we find the linear sorted array, the array becomes 1 
        2 3 4 5 6 7 8 9. So, median = 5

    Example 2

        Input: matrix=[ [1, 3, 8], [2, 3, 4], [1, 2, 5] ] 
        Output: 3
        Explanation: If we find the linear sorted array, the array becomes 1 
        1 2 2 3 3 4 5 8. So, median = 3
*/



/*
Rows are sorted.
Columns are NOT sorted.

    top-right
    bottom-left
    staircase

    not possible

    median a is number where #smaller = #larger

    9/2 = 4
    Need the 5th smallest element.

    we need num of elements smaller == 4
    search range will be min, max


---------------------------------------------------
solve this problem first

How many elements in the entire matrix
are <= X ?

1  3  8
2  3  4
1  2  5

X = 3
1  3
2  3
1  2

X = 4
1  3
2  3  4
1  2

---------------------------------------------------
can we 
countLessEqual(X):
    for each row
        int idx = lower_bound(row)
        
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

in this example for X=2, elements are 4
and X=3 elements are 6
for X=4 elements are 7

we want median X, such that count of elements <= X == half
to handle duplicates we want min X where countofelements > half

ans in min, max
    F F F T T T T

cOe(X) > half
    reduce mid
else
    increase mid

    */



/*
Answer space:
    [min(first column), max(last column)]

countLessEqual(X):
    sum of upper_bound(X) from each row

Feasible(X):
    countLessEqual(X) > half

Monotonic:
    F F F F T T T

Find first True.*/


int main() {
    return 0;
}