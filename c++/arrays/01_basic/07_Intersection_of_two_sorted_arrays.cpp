/*
Intersection of two sorted arrays

Given two sorted arrays, nums1 and nums2, return an array containing 
the intersection of these two arrays. Each element in the result must 
appear as many times as it appears in both arrays; that is, if an 
element appears x times in nums1 and y times in nums2, it should 
appear min(x, y) times in the result.

The intersection of two arrays is an array where all values are 
present in both arrays.


Example 1

    Input: nums1 = [1, 2, 2, 3, 5], nums2 = [1, 2, 7]

    Output: [1, 2]

    Explanation:

    The elements 1, 2 are the only elements present in both nums1 and 
    nums2

Example 2

    Input: nums1 = [1, 2, 2, 3, 3, 3], nums2 = [2, 3, 3, 4, 5, 7]

    Output: [2, 3, 3]

    Explanation:

    The element 2 appears in both arrays only one time.

    The element 3 appears in both arrays two times so we add element 3 
    equal to its number of occurrences.

*/

/*
use a unordered_map
    if freq > 2
        then for freq/2 times
            insert
*/
#include <vector>
#include <iostream>
using namespace std;

vector<int> intersectionArray(vector<int>& v1, vector<int>& v2) {
    int n = v1.size();
    int m = v2.size();

    int i=0, j=0;

    vector<int> ans;

    while(i<n && j<m) {
        if(v1[i] < v2[j]) {            
            i++;
        }
        else if(v1[i] > v2[j]) {
            j++;
        }
        else {            
            ans.push_back(v2[j]);
            i++;
            j++;
        }
    }
    return ans;
}


// skip duplicates
vector<int> intersectionArray2(vector<int>& A, vector<int>& B) {

    int i=0, j=0;

    vector<int> ans;

    while (i < A.size() && j < B.size()) {
        if (A[i] < B[j]) {
            i++;
        }
        else if (A[i] > B[j]) {
            j++;
        }
        else {
            ans.push_back(A[i]);

            int x = A[i];
            while (i < A.size() && A[i] == x) i++;
            while (j < B.size() && B[j] == x) j++;
        }
    }
    return ans; 
}

void print(const vector<int> & v) {
    cout << "[";
    for(auto x : v) cout << x << " ";
    cout << "]\n";
}

int main() {     
    vector<int> v1 = {1, 2, 2, 3, 3, 3};     
    vector<int> v2 = {2, 3, 3, 4, 5, 7};    
    print(intersectionArray(v1, v2));
    return 0;
}