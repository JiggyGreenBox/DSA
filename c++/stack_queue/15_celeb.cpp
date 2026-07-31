#include <bits/stdc++.h>
using namespace std;

/*
brute force
    celeb know no one, all zeros
    all zero row may not be a celeb
    unless everyone else knows them
        ..1..
        ..1..
        ..0..
        ..1..
*/
int celebrity_brute_force(const vector<vector<int>>& mat) {
    int n = mat.size();
    for(int i=0; i<n; i++) {
        bool isCeleb = true;

        // celebs know no one
        // should be all zeros
        for(int j=0; j<n; j++) {
            if(i!=j && mat[i][j] == 1) {
                isCeleb = false;
                break;
            }
        }

        if(!isCeleb) continue;

        // confirm if others know the celeb
        // check the entire column
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

hence there can only be 1 celeb
2 celebs cannot exist, its a violation

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