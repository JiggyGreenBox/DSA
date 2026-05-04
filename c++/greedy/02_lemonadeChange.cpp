#include <iostream>
#include <vector>
using namespace std;

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