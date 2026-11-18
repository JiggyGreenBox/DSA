/*
Minimum insertions or deletions to convert string A to B
    [https://takeuforward.org/practice/dsa/minimum-insertions-or-deletions-to-convert-string-a-to-b?category=dp-on-strings&source=strivers-a2z-dsa-sheet]

Given two strings str1 and str2, find the minimum number of 
insertions and deletions in string str1 required to transform str1 
into str2.

Insertion and deletion of characters can take place at any position 
in the string.

Example 1:
    Input: str1 = "kitten", str2 = "sitting"

    Output: 5

    Explanation: To transform "kitten" to "sitting", delete "k" to get 
    "itten", insert "s" at the beginning to get "sitten", delete "e" to 
    get "sittn", then insert "i" to get "sittin", and insert "g" at the 
    end to get "sitting".To transform "kitten" to "sitting", delete "k" 
    and insert "s" to get "sitten", then insert "i" to get "sittin", and 
    insert "g" at the end to get "sitting".

Example 2:
    Input: str1 = "flaw", str2 = "lawn"

    Output: 2

    Explanation: To transform "flaw" to "lawn", delete "f" and insert "n" 
    at the end. Hence minimum number of operations required is 2".
*/

//

#include <bits/stdc++.h>
using namespace std;

int LCS(const string &str1, const string &str2) {
    
    int n = str1.size();
    int m = str2.size();
    vector<int> dp(m+1, 0);
    int diagonal = 0;

    for(int i=n-1; i>=0; i--) {

        diagonal = 0;

        for(int j=m-1; j>=0; j--) {
            
            int old = dp[j];

            if (str1[i] == str2[j])
                dp[j] = 1 + diagonal; // j+1, inital value is 0 aka dp[m]
            else
                dp[j] = max(dp[j], dp[j+1]);
                
            diagonal = old; // becomes the j+1 in the next iter
        }
    }
    return dp[0];
}

int minOperations(string str1, string str2) {
    int n = str1.size();
    int m = str2.size();
    return m + n - 2*(LCS(str1, str2));
}

int main() {
    string str1 = "kitten";
    string str2 = "sitting";
    assert(minOperations(str1, str2) == 5);

    str1 = "flaw"; str2 = "lawn";
    assert(minOperations(str1, str2) == 2);
}