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