```cpp
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        
        vector<vector<int>> results;
        sort(candidates.begin(), candidates.end());
        vector<int> current;
        backtrack(0, target, current, candidates, results);
        return results;
    }
private:
    void backtrack( int idx, 
                    int curr_sum, 
                    vector<int>& current, 
                    vector<int>& candidates,
                    vector<vector<int>>& results)
    {
        // base cases
        if(curr_sum == 0) {
            results.push_back(current);
            return;
        }
        if(curr_sum < 0 || idx == candidates.size()) return;

        // IGNORE 
        // // pick element
        // current.push_back(candidates[idx]);
        // backtrack(idx+1, curr_sum-candidates[idx], current, candidates, results);
        // current.pop_back();

        // // ignore element
        // // ensure next element is different from the current selected one
        // for(int i=idx+1; i<candidates.size(); i++){
        //     if(candidates[i]!=candidates[idx]){
        //         backtrack(i, curr_sum, current, candidates, results);
        //         break;
        //     }
        // }
        

        // SKIP WITH LOOP
        for(int i=idx; i < candidates.size(); i++) {
            // skip duplicates
            // first pass always goes thru
            if(i>idx && candidates[i] == candidates[i-1]) continue;

            if(candidates[i] > curr_sum) break; // target will be -ve

            current.push_back(candidates[i]);
            backtrack(i+1, curr_sum-candidates[i], current, candidates, results);
            current.pop_back();
        }
    }
};
```