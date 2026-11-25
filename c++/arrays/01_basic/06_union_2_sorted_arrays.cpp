#include <iostream>
#include <vector>

using namespace std;

vector<int> union_sorted_arrays(vector<int>& v1, vector<int>& v2) {

    int n = v1.size();
    int m = v2.size();

    int i=0, j=0;

    vector<int> ans;

    while(i<n && j<m) {
        if(v1[i] < v2[j]) {
            if(!ans.size() || ans.back() != v1[i]) {
                ans.push_back(v1[i]);
            }
            i++;
        }
        else if(v1[i] > v2[j]) {
            if(!ans.size() || ans.back() != v2[j]) {
                ans.push_back(v2[j]);
            }
            j++;
        }
        else {
            if(!ans.size() || ans.back() != v1[i]) {
                ans.push_back(v1[i]);
            }
            i++;
            j++;
        }
    }
    
    
    while(i<n){
        if(!ans.size() || ans.back() != v1[i]) {
            ans.push_back(v1[i]);
        }
        i++;
    }
    while(j<m){
        if(!ans.size() || ans.back() != v2[j]) {
            ans.push_back(v2[j]);
        }
        j++;
    }
    return ans;
}


int main() {
    vector<int> v1 = {1,1,1,1,1,1,7};
    vector<int> v2 = {6,6,6,7,8,8,8};

    vector<int> ans = union_sorted_arrays(v1, v2);
    for(auto x: ans){
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

/*
if arrays are not sorted we use a set
O(n+m)log(n+m)

but since arrays are sorted we can just check ans.back
O(m+n) T
O(1)   S

variations:
 - Merge Two Sorted Arrays (Keep Duplicates): 
        Output every element from both arrays in sorted order, including 
        repeats. Uses the same two-pointer scan without duplicate checks in 
        O(n + m) time.

- In-Place Merge (One Array Has Extra Buffer): 
        Merge arr2 into arr1 where arr1 has enough trailing capacity (m + n). 
        Scan from the back using three pointers so you do not overwrite 
        unread elements.

- Intersection of Two Sorted Arrays: 
        Return only common elements. Advance whichever pointer has the 
        smaller value; record and advance both when arr1[i] == arr2[j] 
        (skipping duplicates if needed).

- Union of k Sorted Arrays: 
        Combine multiple sorted arrays at once. Use a min-heap of size k to 
        repeatedly extract the smallest current element in  (O(N  log k) ) 
        time, where N is total elements.
- Unsorted Arrays Union: 
        Sort both arrays first in  (O(n  log n + m  log m) ) time and apply 
        two pointers, or use a hash set in O(n + m) time and O(n + m) space.
- Arrays with Large Size Differences: 
        When one array is much smaller than the other, use binary search on 
        the larger array for elements of the smaller one to reduce time 
        complexity to  (O(m  log n) ) (for  (m  << n )).
*/

/*
A = [2, 5, 8, 12, 16, 20, 25, 30, 35, 40]
B = [1, 10, 18]

we check B against A
    1 goes before A
    [1]

    10 upperbound is after 8 (pos3)
    insert [2,5,8]
        [1,2,5,8]

    18
        look after pos3
    
*/

#include <algorithm>
vector<int> mergeBinarySearch(vector<int>& A,
                              vector<int>& B) {
    int n = A.size();
    int m = B.size();

    vector<int> ans;
    int i = 0;

    // search from smaller
    for(int x : B) {

        // Find insertion position in remaining A
        int pos = upper_bound(
            A.begin() + i,
            A.end(),
            x
        ) - A.begin();

        // Emit elements from A before x
        while(i < pos) {
            ans.push_back(A[i++]);
        }

        // Emit B element
        ans.push_back(x);
    }

    // Emit remaining A elements
    while(i < n) {
        ans.push_back(A[i++]);
    }

    return ans;
}
/*
n = large
m = small
binary search
    O(mlogn)

copy large
    O(n)

copy small
    O(m)

total = n + mlogn
aux output space m+n

*/