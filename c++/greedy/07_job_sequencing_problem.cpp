#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(vector<int>& a, vector<int>& b){
    return (a[2] > b[2]);
}

// return true if job could be added
// allow bigger deadlines to fit earlier
// 2 can be put in 1
bool add_job(int deadline, vector<bool>& slots_occupied) {
    for(int i=deadline; i>0; i--){
        if(!slots_occupied[i]){
            slots_occupied[i] = true;
            return true;
        }
    }
    return false; // could not find a slot
}

vector<int> JobScheduling(vector<vector<int>>& Jobs) { 

    // sort(Jobs.begin(), Jobs.end(), comp);
    sort(Jobs.begin(), Jobs.end(), [](vector<int>& a, vector<int>& b){
        return a[2] > b[2];
    });

    // vector of bools to store slots?
    int max_deadline = 0;
    for(auto job : Jobs){
        if(job[1] > max_deadline){
            max_deadline = job[1];
        }            
    }

    int num_jobs = 0;
    int max_profit = 0;
    vector<bool> slots_occupied(max_deadline+1, false);

    for(auto Job : Jobs) {
        int deadline = Job[1];
        int profit = Job[2];

        // check if we can add the job
        if(add_job(deadline, slots_occupied)) {            
            num_jobs++;
            max_profit += profit;
        }
    }
    return {num_jobs, max_profit};
}

// if i sort by profit
// and choose spot based on profit
// will i block better combinations
// this doesnt matter because each job takes 1 unit of time
// this allows us to blindly select
// if the time to complete a job was variable 
// then it would not be greedy and maybe DP

// Because each job takes equal time,
// selecting the highest profit job never prevents a better schedule.



void printJobs(const vector<vector<int>>& jobs) {
    for(const auto& row : jobs){
        cout << "[";
        for(int x : row) {
            cout << x << " ";
        }
        cout << "]\n";
    }
    cout << "\n";
}

void printRes(const vector<int>& res){
    cout << res[0] << " " << res[1] << endl;
    cout << endl;
}

int main() {
    
    vector<vector<int>> Jobs = { {1, 2, 100}, {2, 1, 19}, {3, 2, 27}, {4, 1, 25}, {5, 1, 15} };    
    printRes(JobScheduling(Jobs));

    Jobs = { {1,4,20}, {2,1,10}, {3,1,40}, {4,1,30} };
    printRes(JobScheduling(Jobs));

    // printJobs(Jobs);
    // sort(Jobs.begin(), Jobs.end(), comp);
    // printJobs(Jobs);
    return 0;
}

/*
Job sequencing Problem

Given an 2D array Jobs of size Nx3, where Jobs[i][0] represents JobID 
, Jobs[i][1] represents Deadline , Jobs[i][2] represents Profit 
associated with that job. Each Job takes 1 unit of time to complete 
and only one job can be scheduled at a time.

The profit associated with a job is earned only if it is completed by 
its deadline. Find the number of jobs and maximum profit.


Example 1

    Input : 
        Jobs = [ [1, 4, 20] , [2, 1, 10] , [3, 1, 40] , [4, 1, 30] ]
    Output : 2 60

    Explanation : Job with JobID 3 can be performed at time t=1 giving a 
    profit of 40.
    Job with JobID 1 can be performed at time t=2 giving a profit of 20.
    No more jobs can be scheduled, So total Profit = 40 + 20 => 60.
    Total number of jobs completed are two, JobID 1, JobID 3.
    So answer is 2 60.

Example 2
    Input : 
        Jobs = [ [1, 2, 100] , [2, 1, 19] , [3, 2, 27] , [4, 1, 25] , [5, 1, 15] ]
    Output : 2 127

    Explanation : Job with JobID 1 can be performed at time time t=1 
    giving a profit of 100.
    Job with JobID 3 can be performed at time t=2 giving a profit of 27.
    No more jobs can be scheduled, So total Profit = 100 + 27 => 127.
    Total number of jobs completed are two, JobID 1, JobID 3.
    So answer is 2 127.

Example 3
    Input : 
        Jobs = [ [1, 1, 100] , [2, 2, 200] , [3, 3, 300] , [4, 4, 400] ]
    Output: 4 1000



The hidden assumptions:

The problem should really have said something like:

 - There is a single processor.
 - Each job takes exactly one unit of time.
 - At most one job can execute during any unit of time.
 - A job with deadline d must complete by the end of time slot d.
 - You may choose to skip jobs.
 - Maximize total profit.

Those six bullets completely specify the problem. Unfortunately, many 
versions omit them, which is why it's confusing on first read.

One more thing to keep in mind: the deadline is not the start time. 
It's the latest slot in which the job may be scheduled. That's why, 
when you eventually derive the greedy algorithm, you'll see people 
trying to place each chosen job in the latest available slot ≤ 
deadline rather than the earliest one. That "schedule as late as 
possible" idea is the key insight behind the solution.
*/

class Solution {
public:
    vector<int> jobSequencing(vector<vector<int>> &jobs) {

        // Sort by profit (highest first)
        sort(jobs.begin(), jobs.end(),
             [](const auto &a, const auto &b) {
                 return a[2] > b[2];
             });

        // Find the maximum deadline
        int maxDeadline = 0;
        for (auto &job : jobs)
            maxDeadline = max(maxDeadline, job[1]);

        // slot[i] = true if day i is already occupied
        vector<bool> slot(maxDeadline + 1, false);

        int jobsDone = 0;
        int totalProfit = 0;

        for (auto &job : jobs) {

            int deadline = job[1];
            int profit   = job[2];

            // Schedule as late as possible
            for (int day = deadline; day >= 1; day--) {

                if (!slot[day]) {
                    slot[day] = true;
                    jobsDone++;
                    totalProfit += profit;
                    break;
                }
            }
        }

        return {jobsDone, totalProfit};
    }
};

/*


1. Sort by profit descending.
2. Maintain a calendar (the slot array).
3. For each job, book the latest available day on or before its deadline.
4. If no such day exists, skip the job.

That's the mental model that makes the implementation easy to 
reconstruct even if you haven't seen it in months.

*/