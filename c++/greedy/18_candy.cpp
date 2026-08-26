#include <iostream>
#include <vector>
#include  <climits>

using namespace std;

int find_candies(const vector<int>& kids) {
    int candy=1;
    int total = 0;

    int n = kids.size();
    // next child decides candy size
    // start with 1
    // increase -> increase candy_size
    // decrease-> decrease
        // maybe zero at this point, for the next child
        // this means we need to increase everyones candy by 1,
        // and allow the next child to have candy_size =1
    for(int i=0; i<n-1; i++){
        
        // diff increase 
        if(kids[i] < kids[i+1]){
            total += candy;
            candy++;        // next child gets +1
        }
        // diff decrease or equal
        // else if(kids[i] <= kids[i+1]){
        else{
            total += candy;
            candy--;
            if(candy == 0){
                // need to add +1 to each child uptill now
                total += (i+1);
                candy = 1;
            }            
        }        
    }
    // add last kids candy
    total += candy;
    return total;
}

int find_candies2(vector<int>& kids){
    int n = kids.size();
    // gradient array
    vector<int> grad(n, 0);
    bool neg = false;

    int candy_size = 1;
    grad[0] = candy_size;
    for(int i=1; i<n; i++){
        if(kids[i] > kids[i-1]){
            grad[i] = ++candy_size;
        }
        else{
            grad[i] = --candy_size;
            if(candy_size <= 0) neg=true;
        }
    }

    // find if any are negative
    if(neg){
        int check = INT_MAX;
        for(auto x : grad){
            if(x < check) check = x;
        }

        int total=0;
        check = abs(check)+1;
        for(auto x : grad){            
            total += x+check;
        }
        return total;
    }

    int total = 0;
    for(auto x : grad){        
        total += x;
    }
    return total;
}


int find_candies3(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> candies(n,1);
    

    for(int i=1; i<n; i++) {
        if(ratings[i] > ratings[i-1]){
            candies[i] = candies[i-1]+1;
        }
    }
    
    for(int i=n-2; i>=0; i--) {
        if(ratings[i] > ratings[i+1]){
            candies[i] = max(candies[i],candies[i+1]+1);
        }
    }

    // for(auto x : candies) cout << x << " ";
    // cout << "\n" ;

    int total = 0;
    for(auto c : candies){
        total += c;
    }
    return total;
}


int candy(vector<int>& ratings) {
    int n = ratings.size();
    if (n == 0) return 0;
    
    int total = 1;
    int up = 0, down = 0, peak = 0;
    
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i-1]) {
            up++;
            peak = up;
            down = 0;
            total += (1 + up);
        } 
        else if (ratings[i] == ratings[i-1]) {
            up = down = peak = 0;
            total += 1;
        } 
        else {
            down++;
            up = 0;

            total += down;

            // If the down-slope exceeds the peak height, 
            // the peak needs to be pushed up by 1.
            if (down > peak) 
                total++;
        }
    }
    return total;
}


int main() {
    vector<int> kids = {3, 2, 1};
    cout << find_candies3(kids) << endl;
    return 0;
}

/*
   4
  3  1
 2    2
1      3
        4


here the down slope is actually calculated in reverse order
so 



   4
  3 4
 2   3
1     2  
       1

but peak is 4 and first dip is 4
but it should be 5

total += down;
// If the down-slope exceeds the peak height, 
// the peak needs to be pushed up by 1.
if (down > peak) total++;

down is not greater than peak right
   how do we get the peak to be 5 and not 4

answer
   because we track edges instead
   now the formula works correctly
*/