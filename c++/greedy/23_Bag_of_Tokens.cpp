#include <iostream>
#include <vector>
using namespace std;

int main() {
    return 0;
}


/*
Bag of Tokens
    [https://leetcode.com/problems/bag-of-tokens/description/]

You start with an initial power of power, an initial score of 0, and 
a bag of tokens given as an integer array tokens, where each 
tokens[i] denotes the value of tokeni.

Your goal is to maximize the total score by strategically playing 
these tokens. In one move, you can play an unplayed token in one of 
the two ways (but not both for the same token):

Face-up: If your current power is at least tokens[i], you may play 
tokeni, losing tokens[i] power and gaining 1 score.
Face-down: If your current score is at least 1, you may play tokeni, 
gaining tokens[i] power and losing 1 score.
Return the maximum possible score you can achieve after playing any 
number of tokens.

 

Example 1:

    Input: tokens = [100], power = 50

    Output: 0

    Explanation: Since your score is 0 initially, you cannot play the 
    token face-down. You also cannot play it face-up since your power 
    (50) is less than tokens[0] (100).

Example 2:

    Input: tokens = [200,100], power = 150

    Output: 1

    Explanation: Play token1 (100) face-up, reducing your power to 50 and 
    increasing your score to 1.

    There is no need to play token0, since you cannot play it face-up to 
    add to your score. The maximum score achievable is 1.

Example 3:

    Input: tokens = [100,200,300,400], power = 200

    Output: 2

    Explanation: Play the tokens in this order to get a score of 2:

    Play token0 (100) face-up, reducing power to 100 and increasing score 
    to 1.
    Play token3 (400) face-down, increasing power to 500 and reducing 
    score to 0.
    Play token1 (200) face-up, reducing power to 300 and increasing score 
    to 1.
    Play token2 (300) face-up, reducing power to 0 and increasing score 
    to 2.
    The maximum score achievable is 2.
*/

/*
play token face up
    +1 to score
    face up is possible when power > token
        then power = old_power - token

    we can only play face up if we have power > any token
        as this move consumes power
    
play token down
    -1 to score

    face down means
        power = old_power + token
    
    we can only play face down if we have score > 0
        as this move consumes score


we need power or points to play
    we want max points
*/

/*
Bag of Tokens
    [https://leetcode.com/problems/bag-of-tokens/description/]
 [100,200,300,400], power = 200

 score-0, power-200
 200 options i have
    100,200

        100
            get +1, have 100 power

        200
            get +1, have 0 power
                return score 1

score-1, power-100
100
    options
        increase power
            options
                score-0, power-300
                score-0, power-400
                score-0, power-500
        increase points
            no options as all tokens are greater


score-0, power-500
    options
        increase points
            score-1, power-200
            score-1, power-300

    
score-1, power-200
    options
        increase points            
            score-2, power-0
                return 2

can i sort and have a L and R pointer
    if we have power larger than L
        we take smallest L

    if we have points
        we take the largest R

i was right!

canonical
    sort

    L = 0
    R = n-1

    while(L <= R)

        if(power >= tokens[L])

            buy smallest
            score++

            best = max(best, score);

        else if(score > 0)

            sell largest

        else

            break


*/

#include <algorithm>
using namespace std;

int bagOfTokensScore(vector<int>& tokens, int power) {

    sort(tokens.begin(), tokens.end());

    int L = 0;
    int R = tokens.size() - 1;

    int score = 0;
    int best = 0;

    while (L <= R) {

        // Gain score using the cheapest token.
        if (power >= tokens[L]) {
            power -= tokens[L];
            L++;

            score++;
            best = max(best, score);
        }

        // Can't gain score, so sacrifice one score
        // to recover as much power as possible.
        else if (score > 0) {
            power += tokens[R];
            R--;

            score--;
        }

        // Can't buy and can't sell.
        else {
            break;
        }
    }

    return best;
}