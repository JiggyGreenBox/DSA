#include <iostream>
#include <vector>

using namespace std;



/*
wrong code
    greedy
    why?
    [1, 5, 500, 1], k=2

    it will take [1,5] as the answer

*/
int maxScoreWrong(vector<int>& cardScore , int k){
    int i = 0;
    int j = cardScore.size() - 1;
    int sum = 0;

    while(i<j && k--) {
        if(cardScore[i] > cardScore[j]) {
            sum += cardScore[i];
            i++;
        }
        else{
            sum += cardScore[j];
            j--;
        }
    }

    return sum;
}

// Time: O(k)
// Space: O(1)
int maxScore(const vector<int>& card_score , int k) {

    // a better way is to calculate the prefix sum from the first k elements
    // now we can choose to use an element from the back or not
    // so we can [k-1] + [1] and check max

    int n = card_score.size();
    int left_sum = 0;

    for(int i=0; i<k; i++) 
        left_sum += card_score[i];

    int ans = left_sum; // look for a better answer
    int right_sum = 0;

    for (int i = 1; i <= k; i++) { // this would be 0, but n-1
        left_sum -= card_score[k-i];
        right_sum += card_score[n-i];
        ans = max(ans, left_sum + right_sum);
    }
    return ans;
}



int main() {
    cout << maxScore({1, 2, 3, 4, 5, 6}, 3) << endl;

    cout << maxScore({5, 4, 1, 8, 7, 1, 3}, 3) << endl;

    vector<int> cardscore = {3826, 3728, 7146, 816, 4080, 4612, 668, 1309, 7906, 9465, 3440, 6772, 8833, 2604, 8800, 6409, 5844, 305, 4655, 7762, 8280, 9928, 2351, 3976, 9840, 5214, 6564, 3537, 9007, 5286, 1337, 6476, 2819, 2937, 993, 7644, 5621, 3580, 1680, 9353, 5854, 4018, 5484, 1651, 845, 3297, 8398, 9960, 3702, 969, 445, 2616, 6940, 2866, 5021, 9736, 1042, 4021, 3172, 5508, 8463, 7934, 1581, 9624, 8352, 560, 4257, 2256, 1875, 5914, 1778, 2142, 2497, 5225, 7034, 8972, 4795, 6990, 8532, 7762, 3560, 2001, 1112, 4891, 1037, 8550, 3805, 5172, 3631, 3583, 1082, 9476, 4213, 1618, 9581, 3074, 753, 6125, 3776, 3395, 7569, 7319, 8649, 5875, 8049, 2328, 3026, 1046, 4707, 4891, 8232, 9215, 3713, 547, 6183, 3121, 4850, 7421, 7269, 5541, 1100, 1605, 2606, 3931, 58, 4203, 4401, 3364, 7982, 1622, 7304, 2158, 3143, 5737, 4509, 6561, 6518, 1494, 3147, 4235, 3086, 4289, 9364, 9687, 5179, 5143, 9938, 964, 1140, 5998, 6815};
    int k = 142;
    cout << maxScore(cardscore, k) << endl;    // 698254
    return 0;
}