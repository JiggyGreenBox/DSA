/*
https://leetcode.com/problems/bus-routes/description/

graph modelling problem
*/

#include <unordered_set>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

int numBusesToDestination(vector<vector<int>>& routes,
                          int source, int target) 
{
    if(source == target)
        return 0;

    // stop -> buses containing this stop
    unordered_map<int, vector<int>> stopToBuses;

    for(int bus = 0; bus < routes.size(); bus++) {
        for(int stop : routes[bus]) {
            stopToBuses[stop].push_back(bus);
        }
    }

    queue<int> q; // stops
    unordered_set<int> visitedStops;
    unordered_set<int> usedBuses;

    q.push(source);
    visitedStops.insert(source);

    int busesTaken = 0;

    while(!q.empty()) {
        int size = q.size();
        busesTaken++;

        while(size--) {
            int stop = q.front();
            q.pop();

            // Which buses can I take from this stop?
            for(int bus : stopToBuses[stop]) {

                // Don't process the same bus again
                if(usedBuses.count(bus))
                    continue;

                usedBuses.insert(bus);

                // Taking this bus gives us all its stops
                for(int nextStop : routes[bus]) {

                    if(nextStop == target)
                        return busesTaken;

                    if(visitedStops.count(nextStop))
                        continue;

                    visitedStops.insert(nextStop);
                    q.push(nextStop);
                }
            }
        }
    }

    return -1;
}
