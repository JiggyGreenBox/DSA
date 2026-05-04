#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// n^2 TC
int findMaximumCookieStudents1(vector<int>& Student, vector<int>& Cookie){    
    // brute force is n2 loop
    int count=0;
    for(int i=0; i<Student.size(); i++){
        // check each cookie 
        // for each student
        int min_cookie=INT_MAX;
        int min_idx = -1;
        for(int j=0; j<Cookie.size(); j++){
            // lets mark used cookie with -1
            
            if(Cookie[j]>=Student[i] && Cookie[j] < min_cookie){
                min_cookie = Cookie[j];
                min_idx = j;
            }            
        }
        if(min_idx != -1){
            Cookie[min_idx] = -1;
            count++;
        }
    }
    return count;
}

int findMaximumCookieStudents2(vector<int>& Student, vector<int>& Cookie){
    sort(Student.begin(), Student.end());
    sort(Cookie.begin(), Cookie.end());

    // for(auto x : Student) cout << x << " ";
    // cout << "\n";

    // for(auto x : Cookie) cout << x << " ";
    // cout << "\n";

    int i=0;
    int j=0;
    int n=Student.size();
    int m=Cookie.size();
    // int count=0;

    while(i<n && j<m){
        if(Cookie[j] >= Student[i]) { // cookie satisfied student
            i++;            
            // count++;
        }        
        j++;        // move ahead in any case
    }
    return i;// or count
}

int main() {
    // vector<int> students = {1, 2, 3};
    // vector<int> cookies = {1, 1};
    // vector<int> students = {3, 1};
    // vector<int> cookies = {1, 3};

    vector<int> students = {5, 1, 4};
    vector<int> cookies = {1, 3, 4, 5};
    // cout << findMaximumCookieStudents1(students, cookies) << endl;
    cout << findMaximumCookieStudents2(students, cookies) << endl;    
    return 0;
}

// 1,4,5
// 1,3,4,5