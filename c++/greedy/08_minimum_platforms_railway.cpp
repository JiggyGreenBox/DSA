#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canUsePlatform(vector<int>& platforms, pair<int,int>& p) {    
    for(int i=0; i<platforms.size(); i++){
        if(p.first > platforms[i]) { // check arrival clash
            platforms[i] = p.second; // store departure time for next trains
            return true;
        }
    }
    return false;
}

int findPlatform(vector<int>& Arrival, vector<int>& Departure){
    vector<pair<int, int>> trains;
    for(int i=0; i<Arrival.size(); i++){
        trains.push_back({Arrival[i], Departure[i]});
    }
    sort(trains.begin(), trains.end());

    vector<int> platforms;

    for(auto p : trains) {
        if(!canUsePlatform(platforms, p)) {
            platforms.push_back(p.second);
        }        
    }
    return platforms.size();
}


int findPlatform2(vector<int>& Arrival, vector<int>& Departure){
    sort(Arrival.begin(), Arrival.end());
    sort(Departure.begin(), Departure.end());
    
    int i=0;
    int j=0;
    int n = Arrival.size();

    int count = 0;
    int max_count = 0;
    while(i<n && j<n){
        // a train arrives
        if(Arrival[i] <= Departure[j]){
            count++;
            i++;
        }
        else{
            count--;
            j++;
        }
        max_count = max(max_count, count);
    }
    return max_count;
}

int main() {
    vector<int> Arrival   = {900,  940,  950, 1100, 1500, 1800};
    vector<int> Departure = {910, 1200, 1120, 1130, 1900, 2000};
    cout << findPlatform2(Arrival, Departure) << endl;
    return 0;
}