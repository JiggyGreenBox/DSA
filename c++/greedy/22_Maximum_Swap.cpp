#include <iostream>
#include <vector>
using namespace std;

/*
Maximum Swap
    [https://leetcode.com/problems/maximum-swap/description/]


You are given an integer num. You can swap two digits at most once to 
get the maximum valued number.

Return the maximum valued number you can get.

 

Example 1:

Input: num = 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.
Example 2:

Input: num = 9973
Output: 9973
Explanation: No swap.

*/


/*
Maximum Swap
to get the max number we can sort in descending order
by we are only allowed to swap 2 digits


we want rightLargest number swapped with leftSmallest number
use a increasing stack

    if num > st.top
        pop
    push stack


first = pop

while stack
    last = top
    pop

swap(first, last)
*/

/*
maximum swap
    We want the leftmost digit to be as large as possible.
    2736
        if we swap 7,6
        its less than if we swap 2,7

    98368
        9 optimal
        8 optimal
        3 next best is 8
            swap

    1993
        1 and 9
            but which 9
                rightmost


    The canonical solution
        Store the last occurrence of every digit.

                2736

                last

                2 -> 0
                3 -> 2
                6 -> 3
                7 -> 1
        build last_idx for each O(n)
        for each digit from left
            check if larger exits where last_idx > curr_idx
                swap
                break
        O(10*n)
*/