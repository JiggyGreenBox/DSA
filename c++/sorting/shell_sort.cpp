#include <bits/stdc++.h>
using namespace std;

/*
==============================================
an improvement over shell sort
==============================================

[99,88,.....21,11,1]
key=21, every element is swapped
key=11, every element is swapped
key=1, every element is swapped

if we compared 99 with 21
imagine the number of swaps reduced

99..21 is the gap 
distance

efficiency depends on the gap
    finally gap=1

==============================================
[23,29,15,19,31,7,9,5,2]
    gap=4        

    [23,7,9,5,2,29,15,19,31]
        gap=4
        
        after 2
            we swap again
                why ?
                    because only at 2 we have an element at gap -4
                        works well for long arrays
[2,7,9,5,23,29,15,19,31]
    gap=2

    [2,7,9,5,23,29,15,19,31]
    i    j
    [2,5,9,7,23,29,15,19,31]
       i   j
    [2,5,9,7,23,29,15,19,31]
              i     j
    [2,5,9,7,15,29,23,19,31]  (23-15) (15-9) ()
              i   j
    [2,5,9,7,15,19,23,29,31]
                    i     j
        
        







*/