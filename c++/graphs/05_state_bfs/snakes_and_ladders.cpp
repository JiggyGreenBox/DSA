/*
Snakes and Ladders
    [https://leetcode.com/problems/snakes-and-ladders/description/]

1. Flatten the board into square numbers.

2. Each square is a graph node.

3. From square x:
       roll = 1..6
       next = x + roll

4. If next has a snake/ladder:
       next = destination[next]

5. Every dice throw costs 1.

        ↓

   unweighted shortest path

        ↓

       BFS

6. Use visited[] because we can reach the same
   square through multiple paths.

7. First time we reach the final square
   = minimum number of throws.

*/

#include <vector>
#include <iostream>
#include <queue>
using namespace std;

/*
board is square
    starting pos, is bottom left
        board[n-1][0]

board starts from 1
we can roll from 1..6
    then pos on board is 1 + [1,6]

    we need to find coords from this pos

6 7 8
5 4 3
0 1 2

    query 7
        7-1 = 6
        6/3 = 2nd row
            even - reverse
            odd - not reversed
        
        
        0 1 2
        3 4 5
        6 7 8

        

        make mat
            0..n^2-1

        if row = num/n odd
            no reverse
            else reverse

        insert into
            n-1-row
            [0..2] 3-1-0
            [3..5] 3-1-1
            [6..8] 3-1-2

            if row is even
                col = idx%n

            2 becomes 1
                1/3 = 0
                1%3 = 1
                0 is even
                    [0][1]

            4 becomes 3
                3/3 = 1
                3%3 = 0

                1 is odd
                    col is n-1-0
                        [1][2]
        
        


*/


#include <vector>
#include <queue>
using namespace std;

pair<int, int> getCoord(int square, int n) {

    int idx = square - 1;

    int row = idx / n;
    int col = idx % n;

    // alternate direction on every row
    if(row & 1)
        col = n - 1 - col;

    // board coordinates start from top
    row = n - 1 - row;

    return {row, col};
}

int snakesAndLadders(vector<vector<int>>& board) {

    int n = board.size();

    vector<bool> visited(n * n + 1, false);

    queue<int> q;
    q.push(1);
    visited[1] = true;

    int moves = 0;

    while(!q.empty()) {

        int size = q.size();

        while(size--) {

            int square = q.front();
            q.pop();

            if(square == n * n)
                return moves;

            // Try every dice roll
            for(int dice = 1; dice <= 6; dice++) {

                int next = square + dice;

                if(next > n * n)
                    continue;

                // Convert square number -> board coordinates
                auto [r, c] = getCoord(next, n);

                // Take snake / ladder if present
                if(board[r][c] != -1)
                    next = board[r][c];

                // Avoid revisiting states
                if(visited[next])
                    continue;

                visited[next] = true;
                q.push(next);
            }
        }

        moves++;
    }

    return -1;
}

int main() {


    vector<vector<int>> board  = {{-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1},{-1,35,-1,-1,13,-1},{-1,-1,-1,-1,-1,-1},{-1,15,-1,-1,-1,-1}};
    auto x = snakesAndLadders(board);

    return 0;
}

/*
shortest number of rolls
        ↓
unweighted graph
        ↓
BFS

V = n² states
each state has ≤ 6 edges

Time  = O(n²)
Space = O(n²)
*/