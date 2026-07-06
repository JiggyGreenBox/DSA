#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Shortest Job First

A software engineer is tasked with using the shortest job first (SJF) 
policy to calculate the average waiting time for each process. The 
shortest job first also known as shortest job next (SJN) scheduling 
policy selects the waiting process with the least execution time to 
run next.

You are given an array of integers bt of size n representing the 
burst times (execution times) of n processes.

Your task is to calculate the average waiting time for all processes 
when scheduled using the SJF policy. The waiting time of a process is 
the total time a process has to wait before its execution starts, 
which is the sum of burst times of all previously executed processes.

Return the floor of the average waiting time, i.e., the largest whole 
number less than or equal to the actual average.

*/

/*

if have a list of jobs and their waiting time


    A,B,C
    A = 5
    B = 3
    C = 2

    lets say we have 3 tasks
    B waits for A
    A finishes at 5
    B finishes at 5+3
    C finishes at 5+3+2

    what ever order we keep it the finishing time remains the same
    so what are we trying to optimize here

    Not the final completion time.
    The waiting experienced by each individual job.

    A waits 0 
    B waits 5
    C waits 8
        avg waiting is 5+8+0/3 = 4.33
    
    can we have a better combination
    B waits 0
    A waits 3
    C waits 8
        avg waiting is 3+8+0/3 = 3.66

    C waits 0
    B waits 2
    A waits 5
        avg waiting is 3+8+0/3 = 2.33

simple proof
    if x > y
    x=0
    y=x
        larger wait time

    OR
    y=0
    x=y
        smaller wait time        


for any job:
    total_time = prev_waiting + prev_execution time

    then average = total_time / n


    
*/

long long solve(vector<int>& bt) {
    sort(bt.begin(), bt.end());
    long long t_waiting = 0;
    long long t_total = 0;
    int n = bt.size();
    
    for(auto job : bt) {
        t_waiting += t_total;
        t_total   += job;
    }
    return t_waiting / n;
}

int main() {
    vector<int> bt = {4, 1, 3, 7, 2};
    cout << solve(bt) << endl;
    return 0;
}