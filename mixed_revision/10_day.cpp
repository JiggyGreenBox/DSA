/*
sep 2
    last aug 30


Problem 1
    You are given a linked list and an integer k.
    Rotate the list to the right by k places.

Example

    head = 1 → 2 → 3 → 4 → 5
    k = 2
        4 → 5 → 1 → 2 → 3
        
    head = 0 → 1 → 2
    k = 4
        2 → 0 → 1

Brute force:
    put linkedlist values into array then perform rotation
    or get linkedlist length
        then place at i+k%n location

    then overwrite back into linked list

Observation:
    if we make the list cicular
    then we can move k places ahead and cut the list
        uses no extra space
Invariant:
    get length and connect head to tail
Algorithm:
    Node* rotateRight(Node* head, int k) {
        if(!head || k == 0)
            return head;

        Node* curr = head;

        int len = 1;
        while(curr->next) {
            curr = curr->next;
            len++;
        }
        
        

        k = k % len;
        if(k == 0)
            return head;

        // make circular
        curr->next = head;

        int steps = len - k;
        while(steps--) {
            curr = curr->next;            
        }

        Node* newHead = curr->next;
        curr->next = nullptr;
        return newHead;
    }
Complexity:
    O(n + (n-k)) time
        O(2n - k) time
    O(1) space
*/



/*
Problem 2 — Mixed Revision

    You are given an array nums containing n integers.

    Return the length of the longest consecutive sequence of integers.

    The sequence elements do not need to be adjacent in the original 
    array.

Example 1

    nums = [100, 4, 200, 1, 3, 2]
    Output: 4
    Explanation: [1, 2, 3, 4]

Example 2

    nums = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]
    Output: 9

Brute force
    run 2 loops for n^2
        and break if inner loop is not consecutive
        track max-len

    sort and count

Observation
    store every num in a set
    if we find num - 1 in the set
        its not the starting

    track max loop possible
Invariant
Algorithm
    int longestConsecutiveSequence(vector<int> &nums) {

        unordered_set<int> st;

        for(int num : nums)
            st.insert(num);

        int max_count = 0;
        for(int num : nums) {
            if(st.count(num - 1) > 0)
                continue;
            
            // num is the first of the sequence
            int count = 1;
            while(st.count(++num) > 0) {
                count++;
            }
            max_count = max(max_count, count);
        }    
        return max_count;
    }
Complexity
    O(n) + O(n) build set, check set
    total O(n) time
    space O(n) space
*/

/*
Problem 3

You are given a binary tree. Return its maximum width.

The width of a level is defined as the number of positions between 
the leftmost and rightmost non-null nodes, including the null 
positions between them.

        1
       / \
      3   2
     /       \
    5         9

The widths are:

    Level 0 → 1
    Level 1 → 2
    Level 2 → 4

Brute force / naive idea
    we use heap indexing to find the leftmost and right most for any level
    left child = 2*i + 1
    right child = 2*i + 2

    then we push these into a queue
    to check this level by level
    track max
Observation
    these numbers can explode in size 
    so we normalize
        we only care about numbers in the same level

    we we subtrack first and normalize the children per level
Invariant
    heap indexing with a queue and normalizing
Algorithm
    int maxWidth(Node* root) {
        if(!root)
            return 0;

        queue<pair<Node*,int>> q;
        q.push(0);

        int max_width = 0;
        while(!q.empty()) {

            int size = q.size();
            int first = q.front().second;
            int last = 0;


            for(int i=0; i<size; i++)
                auto [node, idx] = q.front();
                q.pop();

                

                if(i == 0)
                    first = idx;

                if(i == size-1)
                    last = idx;

                idx -= first;

                if(node->left)
                    q.push({node->left, 2*idx + 1});

                if(node->right)
                    q.push({node->left, 2*idx + 2});
            }
            max_width = max(max_width, last - first);
        }
        return max_width;
    }
Complexity    
    O(n) every node is visited once
    O(h) space
*/
#include <unordered_set>
#include <queue>
using namespace std;

struct Node
{
    Node* left;
    Node* right;
    int val;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};


int maxWidth(Node* root) {
    if (!root)
        return 0;

    queue<pair<Node*, long long>> q;
    q.push({root, 0});

    int ans = 0;

    while (!q.empty()) {
        int size = q.size();

        long long first = q.front().second;
        long long last = 0;

        for (int i = 0; i < size; i++) {
            auto [node, idx] = q.front();
            q.pop();

            long long normalized = idx - first;

            if (i == size - 1)
                last = normalized;

            if (node->left)
                q.push({node->left, 2 * normalized + 1});

            if (node->right)
                q.push({node->right, 2 * normalized + 2});
        }

        ans = max(ans, (int)(last + 1));
    }

    return ans;
}

