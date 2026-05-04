#include <bits/stdc++.h>
using namespace std;

void printResults(const vector<vector<int>>& results) {
    for(auto each : results){
        cout << "[ ";
        for(auto x: each) cout << x << " ";
        cout << "]\n";
    }
    cout << "\n\n";    
}

void backtrack( int idx,
                int sum,
                int k,
                vector<int>& current, 
                vector<vector<int>>& results)
{
    // base cases
    // checking order  
    // faster but wrong logic  
    
    // 750ns            
    // if(sum < 0 || current.size() == k) return;
    // if(sum == 0 && current.size() == k){
    //     results.push_back(current);
    //     return;
    // }    

    // 830ns
    // if(current.size() == k || sum < 0 ) return;    
    // if(current.size() == k && sum == 0){
    //     results.push_back(current);
    //     return;
    // }

    // 1465ns
    if(current.size() == k && sum == 0){
        results.push_back(current);
        return;
    }
    if(current.size() == k || sum < 0 ) return;    
    
    
    
    // 1..9 allowed
    for(int i=idx; i<10; i++) {

        // Average time over 1000 runs:
        // no check 
        //      3130.34
        // if(current.size() >= k) break; // saves cycles in my opinion
        //      2861.5 ns
        // if(current.size() >= k || i > sum) break; // saves cycles in my opinion
        //      2148.16 ns
        if(i > sum || current.size() >= k) break; // saves cycles in my opinion
        //      1938.08 ns
        

        current.push_back(i);
        backtrack(i+1, sum-i, k, current, results);
        current.pop_back();                
    }
}

vector<vector<int>> combinationSum3(int k, int n) {
    // backtrack by selecting or skipping 
    // numbers from 1..9
    // no dups
    // subset.size() == k
    // subset.sum == n

    vector<vector<int>> results;
    vector<int> current;
    backtrack(1, n, k, current, results);
    return results;
}

int main() {

    using Clock = std::chrono::high_resolution_clock;
    using ns = chrono::nanoseconds;
    

    long long total_duration = 0;
    int iterations = 10000;
    
    // 1. WARM UP (Optional but recommended)
    // Run the function once to populate the CPU cache and avoid "cold start" latency.
    combinationSum3(3, 9);
    
    for(int i = 0; i < iterations; i++){
        auto start = Clock::now();
        
        // 2. RUN FUNCTION
        // Store the result to prevent the compiler from optimizing the call away,
        // but do NOT print it here.
        volatile auto result = combinationSum3(3, 9); 
        
        auto end = Clock::now();
        
        // 3. ACCUMULATE
        auto duration = std::chrono::duration_cast<ns>(end - start);
        total_duration += duration.count();
    }

    // 4. CALCULATE AVERAGE
    // Cast to double for precision
    double average_time = (double)total_duration / iterations;

    std::cout << "Total time: " << total_duration << " ns" << std::endl;
    std::cout << "Average time over " << iterations << " runs: " << average_time << " ns" << std::endl;
    

    
    
}