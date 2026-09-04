#include <iostream>
#include <vector>

using namespace std;

void print_permutations(vector<vector<int>>& permutations) {
    for(auto single_permutation: permutations){
        cout << "[";
        for(auto elem: single_permutation){
            cout << elem << " ";
        }
        cout << "]\n";
    }
}

// [1,2,3]
vector<vector<int>> get_permutations(vector<int>& v, int choice) {

    vector<vector<int>> results;
    if(v.empty()) return results; // base case, empty vector

    vector<int> remaining = v;
    remaining.erase(remaining.begin() + choice); // erase element
    
    // [1] [2,3]
    cout << "Picked: " << v[choice] << " | Remaining: ";
    for (int x : remaining) cout << x << " ";
    cout << "\n";

    // could be the last element
    if(remaining.empty()){
        results.push_back({v[choice]});
        return results; // 2nd base case, vector with 1 elem
    }

    // 2 or more elems
    // [2,3]    
    for(int i=0; i<remaining.size(); ++i) {
        // [2,3] choice: [2] returns 3
        // [2,3] choice: [3] returns 2
        vector<vector<int>> child_results;
        child_results = get_permutations(remaining, i); // returns [2,3], [3,2]

        for(auto& cr: child_results) {
            cr.insert(cr.begin(), v[choice]); // insert choice at the begining [1,2,3], [1,3,2]
            results.push_back(cr);
        }
    }    
    return results; // [[1,2,3], [1,3,2]]
}

void print_permutations_learning(vector<int>& v) {

    vector<vector<int>> permutations;

    for (int i = 0; i < v.size(); i++) {
        vector<vector<int>> perms;
        perms = get_permutations(v, i); // (1),2,3  1,(2),3  1,2,(3)
        for(auto x: perms){
            permutations.push_back(x);
        }
    }

    print_permutations(permutations);
}

int main(){
    vector<int> v = {1,2,3,4,5};
    print_permutations_learning(v);

    // output
    // [1 3 2 ]
    // [2 3 1 ]
    // [3 2 1 ]
    return 0;
}