#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>

using namespace std;

void print(const vector<int>& v) {
    cout << "[ ";
    for(int n : v) cout << n << " ";
    cout << "]\n";
}

vector<int> asteroidCollision(const vector<int> &asteroids) {
    stack<int> st;
    vector<int> res;

    for(int a : asteroids) {
        // pos, add to stack
        if(a > 0) st.push(a);
        // neg
        else{
/*
[1,2,3,4,5] // no collision
[-1,-2,-3,-4,-5] // no collision

[10,-5] // collision, dont add 5
[10,-15] // collision, pop and add -15

[1,2,3,10,-15] // collision, pop all, and add -15
[15,-15] // collision consume both
*/          
            // asteroid is negative

            // no top
                // push 

            // top is pos
                // check sum
                // == 0 pop, no push
                // < 0 pop, with push
                    // keep doing this
                // > 0 no pop no push

            if(st.empty() || st.top() < 0) {
                st.push(a);                
            }
            else{
                // st top greater than zero
                while(!st.empty() && st.top() + a < 0) {
                    st.pop();
                }
                if(st.empty()) st.push(a);

                if(!st.empty() && st.top() + a == 0) {
                    st.pop();
                }
            }
        }        
    }


    while(!st.empty()){
        res.push_back(st.top());
        st.pop();
    }

    reverse(res.begin(), res.end());

    return res;
}

vector<int> asteroidCollision2(const vector<int> &asteroids) {
    stack<int> st;    

    for(int a : asteroids) {
        bool destroyed = false;

        
        // push positives without any checks        
        // push negatives if no positives so far (empty stack)
        // push negatives if stack-top is negative
        while(!st.empty() && a < 0 && st.top() > 0) {
            // pop if sum is < 0, keep checking
            // top + a < 0 || top < -a
            if(st.top() < -a) {
                st.pop();
            }

            // pop if sum == 0, dont add this asteroid
            // top + a = 0 || top == -a
            else if(st.top() == -a) {
                st.pop();
                destroyed = true;
                break; // stop while loop
            }

            // if sum > 0, dont add this asteroid
            else {
                destroyed = true;
                break; // stop while loop
            }
        }

        // use only 1 push
        if(!destroyed) {
            st.push(a);
        }
    }

    vector<int> res;
    while(!st.empty()){
        res.push_back(st.top());
        st.pop();
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    print(asteroidCollision({1, 2, 3, -4, -2}));
    print(asteroidCollision2({1, 2, 3, -4, -2}));    
    print(asteroidCollision({5, 10, -5, -10, 8, -8, -3, 12}));
    print(asteroidCollision2({5, 10, -5, -10, 8, -8, -3, 12}));
    return 0;
}


