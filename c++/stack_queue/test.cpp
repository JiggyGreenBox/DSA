#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

/*
we have wrap around indices with this DS

lets say count is 10
we move rear ahead with push
we also move front ahead with pop

so both can move ahead
but since we could be under capacity,
we wrap around
    for eg.
    cap = 10
    push, pop 8 times
    count = 0
    front-idx = rear-idx = 7

    if we push and cross idx 9
    we can occupy idx 0 onwards
        by arr[(idx+1) % cap]
*/

class MyQueue {

};

int main() {
    return 0;
}