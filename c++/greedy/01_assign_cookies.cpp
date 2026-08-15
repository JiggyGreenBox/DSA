#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/*
Assign Cookies
    [https://takeuforward.org/plus/dsa/problems/assign-cookies?subject=dsa&approach=optimal]

    Consider a scenario where a teacher wants to distribute cookies to 
    students, with each student receiving at most one cookie.

    Given two arrays, student and cookie, the ith value in the Student 
    array describes the minimum size of cookie that the ith student can 
    be assigned. The jth value in the Cookie array represents the size of 
    the jth cookie. If Cookie[j] >= Student[i], the jth cookie can be 
    assigned to the ith student.

    Maximize the number of students assigned with cookies and output the 
    maximum number.


Example 1

    Input : student = [1, 2, 3] , cookie = [1, 1]

    Output :1

    Explanation : You have 3 students and 2 cookies.

    The minimum size of cookies required for students are 1 , 2 ,3.

    You have 2 cookies both of size 1, So you can assign the cookie only 
    to student having minimum cookie size 1.

    So your answer is 1.

Example 2

    Input : student = [1, 2] , cookie = [1, 2, 3]

    Output : 2

    Explanation : You have 2 students and 3 cookies.

    The minimum size of cookies required for students are 1 , 2.

    You have 3 cookies and their sizes are big enough to assign cookies 
    to all students.

    So your answer is 2.

Example 3

    Input : student = [4, 5, 1] , cookie = [6, 4, 2]

    Output: 3
*/

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

/*
1. Goal

    Maximize number of satisfied children.

2. Greedy choice

    Satisfy the least demanding child with the smallest sufficient cookie.

3. Why safe

    Don't waste a larger cookie on a child that can take a smaller one.

4. What happens when it fails

    If the smallest cookie can't satisfy the least greedy child, discard it.

5. Implementation

    Sort + two pointers.

6. Complexity

    O(n log n + m log m) time, O(1) auxiliary space apart from sorting.
*/