#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


double fractionalKnapsack(vector<int>& val, vector<int>& wt, int capacity) {

	int n = val.size();

	vector<pair<double, int>> items;

	// {value per unit weight, index}
	for (int i = 0; i < n; i++) {
		items.push_back({(double)val[i] / wt[i], i});
	}

	sort(items.begin(), items.end(),
		[](const auto& a, const auto& b) {
			return a.first > b.first;
		});

	double total = 0.0;

	for (const auto& [ratio, idx] : items) {

		if (capacity >= wt[idx]) {
			total += val[idx];
			capacity -= wt[idx];
		} else {
			total += ratio * capacity;
			break;
		}
	}

	return total;
}

int main() {
	return 0;
}

/*

Fractional Knapsack
	[https://www.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1]

Given two arrays, val[] and wt[] , representing the values and 
weights of items, and an integer capacity representing the maximum 
weight a knapsack can hold, determine the maximum total value that 
can be achieved by putting items in the knapsack. You are allowed to 
break items into fractions if necessary.
Return the maximum value as a double, rounded to 6 decimal places.

Examples :

	Input: val[] = [60, 100, 120], wt[] = [10, 20, 30], capacity = 50
	Output: 240.000000

	Explanation: By taking items of weight 10 and 20 kg and 2/3 fraction 
	of 30 kg. Hence total price will be 60+100+(2/3)(120) = 240


	Input: val[] = [500], wt[] = [30], capacity = 10
	Output: 166.670000

	Explanation: Since the item’s weight exceeds capacity, we take a 
	fraction 10/30 of it, yielding value 166.670000.

*/

/*
Fractional Knapsack

observation
	we can only take an item once
	but we can take fractions of items
	so the best choice is the most dense item
	wt =   10,  50
	val = 100, 100

	10,100 is more dense
	well take it


	then fit it into capacity

	for each sorted density:
		if(cap >= wt[idx])
			cap -= wt[idx]
			val += val[idx]
		else
			val += cap * density
			break

we break after a partial entry
because we would always prefer a whole high density item
if we go partial it should be the last entry
	
*/