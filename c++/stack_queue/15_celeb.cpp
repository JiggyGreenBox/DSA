#include <bits/stdc++.h>
using namespace std;

int celebrity1(const vector<vector<int>>& mat) {
    int n = mat.size();    

    vector<int> check(n, 0);

    for(int i=0; i<n; i++) {
        bool check_celeb = true;
        for(int j=0; j<n; j++) {
            if(i==j) continue;
            if(mat[i][j] == 1){
                check_celeb = false;
                break;
            } 
        }
        if(check_celeb) check[i] = 1;
    }

    for(int i=0; i<n; i++) {
        if(check[i] == 1) {
            int c=0;
            for(int j=0; j<n; j++){
                if(i==j) continue;
                if(mat[j][i] == 1) c++;
            }
            if(c == n-1) return i;
        }
    }    
    return -1;
}


int celebrity2(const vector<vector<int>>& mat) {
    int n = mat.size();
    for(int i=0; i<n; i++) {
        bool isCeleb = true;

        for(int j=0; j<n; j++) {
            if(i!=j && mat[i][j] == 1) {
                isCeleb = false;
                break;
            }
        }

        if(!isCeleb) continue;

        for(int j=0; j<n; j++) {
            if(i!=j && mat[j][i] == 0) {
                isCeleb = false;
                break;
            }
        }
        if(isCeleb) return i;
    }
    return -1;
}

/*
everyone knows the celeb
the celeb knows no one
if A knows B eliminate A
if A doesnt know B eliminate B
for n there will be n-1 comparisions
*/
int celebrity3(const vector<vector<int>>& mat) {
    int n = mat.size();
    int l = 0, r = n-1;

    while(l < r) {
        // A knows B, eliminate A
        if(mat[l][r] == 1) l++;
        // A does not know B, eliminate B
        else r--;
    }

    // l is now a candidate
    // need to verify
    // does cand not know everyone    
    // does everyone know cand
    for(int i=0; i<n; i++) {
        if (i == l) continue;

        // celebrity should not know anyone
        if (mat[l][i] == 1) return -1;

        // everyone should know celebrity
        if (mat[i][l] == 0) return -1;
    }
    return l;
}

int celebrity4(const vector<vector<int>>& mat) {
    int n = mat.size();
    stack<int> st;
    for(int i=0; i<n; i++) {
        st.push(i);
    }

    while( st.size() > 1 ) {
        int A = st.top(); st.pop();
        int B = st.top(); st.pop();

        // A knows B, discard A
        if(mat[A][B] == 1) {
            st.push(B);
        }
        // A does not know B, discard B
        else{
            st.push(A);
        }
    }

    int cand = st.top();
    for(int i=0; i<n; i++) {
        if (i == cand) continue;

        // celebrity should not know anyone
        if (mat[cand][i] == 1) return -1;

        // everyone should know celebrity
        if (mat[i][cand] == 0) return -1;
    }
    return cand;
}

int main() {

    cout << celebrity3({{1, 1, 0},{0, 1, 0},{0, 1, 1}}) << endl;
    cout << celebrity4({{1, 1, 0},{0, 1, 0},{0, 1, 1}}) << endl;
    cout << celebrity3({{1, 1},{1, 1}}) << endl;    
    cout << celebrity4({{1, 1},{1, 1}}) << endl;
    return 0;
}