#include <iostream>
using namespace std;


class Solution {
public:
    int floorSqrt(int n)  {

        // lets use binary search
        // the solution is between 0..n
        // reduce the search space by 2 every time
        int start = 0;
        int end = n;
        int mid;

        while(start <= end){
            mid = start + (end-start)/2;

            cout << start;
            cout << " | ";
            cout << mid;
            cout << " | ";
            cout << end;
            cout << endl;
            cout << endl;

            if(mid*mid < n){
                // go right
                start = mid + 1;
            }
            else{
                // go left
                end = mid - 1;
            }
        }
        return mid;
    }
};



int main(){

    Solution sol;
    std::cout << sol.floorSqrt(36) << std::endl;

    std::cout << sol.floorSqrt(28) << std::endl;

    return 0;

}