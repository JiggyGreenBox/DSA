#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    int NthRoot(int N, int M) {

        // modulo
        // division
        // multiplication

        int start = 1;
        int end = M;

        while(start <= end) {

            long long mid = start + (end-start)/2;

            cout << start;
            cout << " | ";
            cout << mid;
            cout << " | ";
            cout << end;
            cout << endl;
            cout << endl;


            long long n_root = pow(mid, N);

            cout << start;
            cout << " | ";
            cout << mid;
            cout << " | ";
            cout << end;
            cout << " | n_root: ";
            cout << n_root;
            cout << endl;
            cout << endl;

            if(n_root == M) return mid;

            if(n_root < M){
                start = mid + 1;
            }
            else{
                end = mid - 1;
            }
        }
        return -1;
    }
};


int main(){
    Solution sol;

    // cout << sol.NthRoot(7,128) << endl;

    cout << sol.NthRoot(9,512) << endl;
}