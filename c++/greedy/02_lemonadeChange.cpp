#include <iostream>
#include <vector>
using namespace std;

/*
Lemonade Change
    [https://takeuforward.org/plus/dsa/problems/lemonade-change?subject=dsa&approach=optimal]

    Each lemonade at a booth sells for $5. Consumers are lining up to 
    place individual orders, following the billing order. Every consumer 
    will purchase a single lemonade and may pay with a $5, $10, or $20 
    bill. Each customer must receive the appropriate change so that the 
    net transaction is $5. Initially, there is no change available.

    Determine if it is possible to provide the correct change to every 
    customer. Return true if the correct change can be given to every 
    customer, and false otherwise.

    Given an integer array bills, where bills[i] is the bill the ith 
    customer pays, return true if the correct change can be given to 
    every customer, and false otherwise.


Example 1

    Input : bills = [5, 5, 10, 5, 20]

    Output : true

    Explanation : Initially we have $0 available for change.

    From first two customers, we will collect two $5 bills in order. 
    After the first two customers we have two $5 bills available with us 
    for change.

    From the third customer , we collect bill of $10 and give back $5. 
    After third customer we have one $5 and one $10 bill available with 
    us for change.

    From fourth customer , we collect $5 bill. After fourth customer we 
    have two $5 and one $10 bills available with us for change if 
    required.

    From fifth customer , we collect bill of $20 and give back $15 (one 
    $10 + one $5 bill).

    Since all the customers did receive the change correctly , so we 
    return true.

Example 2

    Input : bills = [5, 5, 10, 10, 20]

    Output : false

    Explanation : From first two customers, we will collect two $5 bills 
    in order. After the first two customers we have two $5 bills 
    available with us for change.

    From third customer , we collect $10 and give back $5. After the 
    third customer we have one $5 and one $10 bill available with us for 
    change.

    From fourth customer , we collect $10 and give back $5. After the 
    fourth customer we have two $10 bill available with us for change.

    From fifth customer , we collect $20 , we cannot give the $15 change 
    as we have two $10 bills.

    Since all the customers did not receive the change correctly , the we 
    return false.
*/

bool lemonadeChange(const vector<int>& bills){
    const int lemonade_cost = 5;    
    // store bills for 5,10,20
    int b_5 = 0;
    int b_10 = 0;
    int b_20 = 0;

    for(int bill : bills) {
        // process the 5,10,15 bills
        if(bill == 5) {
            b_5++;
        }
        else if(bill == 10){
            if(b_5 == 0) return false; // we didnt have 5
            b_10++; // add the 10 bill
            b_5--;  // give back 5
            
        }
        else if(bill == 20){

            // WRONG
                // can give back 10 bills
                // that is greedy

            // b_20++; // add the 20 bill
            // b_5--;  // try give back 5
            // b_10--;  // try give back 10
            // if(b_5 < 0) return false; // we didnt have 5
            // if(b_10 < 0) return false; // we didnt have 5

            // first check if 10 bill is available
            if(b_10 > 0 && b_5 > 0){
                b_10--;
                b_5--;
            }
            else if(b_5>=3){
                b_5-=3;
            }
            else{
                return false;
            }
        }
    }
    return true;
}

void printBool(bool b){
    if(b) cout << "true\n";
    else cout << "false\n";
    cout << "\n";
}

int main() {    
    printBool(lemonadeChange({5, 5, 5, 10, 20})); // true
    printBool(lemonadeChange({5, 5, 10, 10, 20})); // false
    return 0;
}

/*
$5
    no change needed
    → keep the $5

$10
    need $5
    → use one $5

$20
    need $15
    → prefer $10 + $5
    → otherwise use 3 × $5
*/