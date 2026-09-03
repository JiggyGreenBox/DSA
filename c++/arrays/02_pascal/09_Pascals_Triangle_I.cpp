#include <iostream>
#include <vector>
using namespace std;

/*
Pascal's Triangle I

    Given two integers r and c, return the value at the rth row and cth 
    column (1-indexed) in a Pascal's Triangle.

    In Pascal's triangle:

        The first row contains a single element 1.

        Each row has one more element than the previous row.

        Every row starts and ends with 1.

    

    triangle[i][j] =
        triangle[i-1][j-1] +
        triangle[i-1][j];


        we want 1 as first element of each row, and last

            Row 0: 1              -> 1 element
            Row 1: 1 1            -> 2 elements
            Row 2: 1 2 1          -> 3 elements
            Row 3: 1 3 3 1        -> 4 elements
            Row 4: 1 4 6 4 1      -> 5 elements

            Row i contains (i+1) elements

            valid indices are: 0 ... i

            ans[4][0] = 1;
            ans[4][4] = 1;


*/

/*
nCr = Number of ways to choose r items from n items
    Order does not matter.

        A B C D

        Choose 2:

        AB AC AD BC BD CD

        4C2 = 6

    nCr
        = n! / r! * (n-r)!

    4C2
        = 4! / 2! * 2!

        = 4*3*2*1 / 2*2
        = 6

    Important Properties
        Edge Values
        nC0 = 1   
            Choose nothing from n items → 1 way
        nCn = 1
            Choose all n items → 1 way

    Symmetry
        nCr = nC(n-r)
        5C2 = 5C3 = 10

        Useful optimization:
            r = min(r, n-r);


    Pascal Triangle Relationship
        Each row is:
            Row n
            nC0 nC1 nC2 ... nCn
*/


/*

Deriving the formulae

    nCr = n! / r! * (n-r)!

    if we use the recursive formula, we would need O(2^r)

    we can use dp as well O(n^2)

    5C2 = 10
        5*4*3*2*1 / 3*2*1 * 2*1 = 10
    
    5C3 = 10
        [5!/3!*2!]  / [5!/2!*3!] = 1

    5C0 = 1
    5C1 = 5! / 4!*1! = 5

    nCr+1 / nCr 
    =
    [n!/(r+1)! * (n-r-1)!] / [n!/r! * (n-r)!]

    = 
        r! * (n-r)! / (r+1)! * (n-r-1)!

    =
        n-r / r+1
        
        
    nC(r+1) = nCr * (n-r)/(r+1)

    and we know that nC0 = 1,
        so we can start at any row and generate the entire row, or stop at a target


    entire row

    long long val = 1; // nC0

    for(int r=0; r<n; r++) {
        row.push_back(val);
        val = val * (n-r) / (r+1);
    }


    target
    long long nCr(int n, int r) {

        r = min(r, n-r);

        long long ans = 1;

        for(int i=0; i<r; i++) {
            ans = ans * (n-i);
            ans = ans / (i+1);
        }

        return ans;
    }
*/

/*
another thing to note
    n is 0 based
    so each row has n+1 elements

    if we wanted nCr for the entire row then
        val = 1

        for r=0; r <=n; r++
            push val
            val = val * n-r / r+1

    val = val* ...
        is actually the next answer
        val stores the NEXT answer.

    so when we want nCr
        we stop at r-1
            then val is val for r
*/


int pascalTriangleI(int r, int c) {
    if(c == 1 || r == c) return 1;

    return pascalTriangleI(r-1,c-1) + pascalTriangleI(r-1, c);
}

int nCr(int n, int r) {
    long long val = 1; // nC0

    r = min(r, n-r); // r<=n
    

    for(int i=0; i<r; i++) {
        val = val * (n-i) / (i+1);
    }

    return val;    
}

/*
pascal triangle is 0 based
if question says 1 based then row 5 == 4c0..4c4
*/
int pascalTriangleI_2(int n, int r) {
    return nCr(n-1, r-1);
}

int main() {

    cout << pascalTriangleI(4, 2) << endl;
    cout << pascalTriangleI_2(4, 2) << endl;
    
    cout << pascalTriangleI(5, 3) << endl;
    cout << pascalTriangleI_2(5, 3) << endl;
    return 0;
}


