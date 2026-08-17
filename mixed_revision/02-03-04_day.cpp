/*
10th aug
last time was 3rd of aug

Day 1

    Binary Search
    Tree
    Stack

Day 2

    Linked List
    BST
    Binary Search

Day 3

    Stack
    Tree
    Linked List
*/


/*
Day 1

    Binary Search
    Tree
    Stack

problem 1
    Given a binary tree, return the maximum path sum.

    Example 1

             1
            / \
           2   3

        ans 6

    Example 2
       -10
       /  \
      9   20
          / \
         15  7
        and 42

    Constraints
        Number of nodes: 1 <= n <= 3 * 10^4
        Node values may be negative.

    Brute force:
    Observation:
    Invariant:
    Algorithm:
    Complexity:


        Brute force
            visit every node
                for each left and right subtree
                    calculate the left sum and right sum
                        keep a max value

        Observation
            if the left or right subtree sum is negative
            dont carry it, keep it capped at zero

        Invariant
            calcSum(Node* node, int &maxSum) {
                if(!node)
                    return 0

                int ls = max(calcSum(node->left), 0);
                int rs = max(calcSum(node->right), 0);

                int total = node->data + ls + rs;
                maxSum = max(maxSum, total)

                return total;
            }

        Complexity:
            every node is visited once
                O(n)

-------------------------
    Review
        for the return we return the best path
            so return node->data + max(rs, ls)

    Recognition
        green
    Implementation
        yellow
-------------------------



Problem 2

    You are given a sorted array of integers nums and an integer target.
    Return the first index at which target occurs.
    If target does not exist, return -1.

        nums = [1, 2, 2, 2, 4, 5]
        target = 2

        Output: 1

    Brute force:
        linear search from the idx 0
    Observation:
        we can use binary search to discard half
            and look for a smaller answer if found
        lowerbound implementation
    Invariant:
        
    Algorithm:

    lower(nums, target)
        n = nums.size()
        l = 0
        r = n

        while() {
            int m = l + (r-l)/2;

            if(nums[m] >= target) {
                r = m;
            }
            else {
                l = m + 1;
            }
        }
        return l;


    Complexity:
        O(logn) time
        O(1) space

-------------------------
    Review
        add the case where nothing was found

    Recognition
        green
    Implementation
        green
-------------------------

Problem 3

    You are given an integer array nums.
    For every element nums[i], find the next greater element to its right.
    The next greater element is the first element to the right of nums[i] that is strictly greater than nums[i].
    If no such element exists, return -1 for that position.

    nums    = [4,  5,  2, 10,  8]
    Output  = [5, 10, 10, -1, -1]


    Brute force:
        from each index we iterate right
            init to -1
            if we find something larger overwrite
        O(n^2)
            2 loops

    Observation:
    
        we can use a stack to store candidates
        since we want nextgreatest we can iterate from R-L

        when we find a larger element we pop the stack as the previous value is not useful
        [1,2,3,4,5]
        [2,3,4,5,-1]

        [5,4,3,2,1]
        [-1,-1,-1,-1,-1]

        [3,3,3]
        [-1,-1,-1]

    Invariant:


    Algorithm:

        nge(nums)
            n = nums.size()
            vector<int> ans(n, -1);

            for(i=n-1; i>=0; i--) {

                while(!st.empty() && nums[i] >= nums[st.top()])
                    st.pop()

                ans[i] = st.empty() ? -1 : nums[st.top()];

                st.push(i)
            }
            return ans

    Complexity:
        O(n) time
        O(n) space

*/

/*
Day 1 B

Problem 1

    You are given the root of a binary tree.

    Return the vertical order traversal of its nodes.

    For each node, assign a column number:

    The root starts at column 0.
    A left child is at column - 1.
    A right child is at column + 1.

    Nodes should be returned column by column from the smallest column to 
    the largest column.

    Within the same column, nodes should appear from top to bottom.


        3
       / \
      9   20
          / \
         15  7


    [
    [9],
    [3,15],
    [20],
    [7]
    ]

        1
       / \
      2   3
     / \ / \
    4  5 6  7

    [
    [4],
    [2],
    [1,5,6],
    [3],
    [7]
    ]

Brute force:

Observation:
    if we consider the the root to be at x coord of zero
    then left child is x = +1 
    and right child is x = -1

    now we need to also account for column
        we can just consider root to be col=0
        and every row beneath as +1

    if we have 2 nodes that have the same row and col
        then we return the smaller node value first

    so the sorted ordering is [col, row, node]

Invariant:
    we can use bfs to add the nodes to a vector of tuple of col,row,node

    then we sort this once

    then we construct the return vector

Algorithm:


    vector<vector<int>> verticalOrderTraversal(Node* root) {
        vector<vector<int>> ans;

        if(!root)
            return ans

        vector<tuple<int,int,int>> nodes;
        queue<pair<pair<int,int>, Node*>> q;
        q.push({{0,0}, root});

        while(!q.empty()) {

            auto [cords,node] = q.front();
            q.pop();

            auto [row, col] = cords;

            nodes.push_back({col, row, node->val});

            if(node->left)
                q.push({{row+1, col-1}, node->left});

            if(node->right)
                q.push({{row+1, col+1}, node->right});
        }

        sort(node.begin(), nodes.end());

        int lastCol = -1;
        for(auto [col,row, nval] : nodes) {
            if(col != lastCol) {
                lastCol = col;
                ans.push_back({});
            }
                
            ans.back().push_back(nval);
        }
        return ans;
    }

Complexity:
    O(n) to push all nodes into vec of tuple
    nlogn to sort tuple
    O(n) to reconstruct ans vector

    total O(nlogn)


Review
    yellow for implementation details
    minor bugs



*/

/*
Problem 2 — Day 1B

    You are given a sorted array of integers nums and an integer k.

    Find the k-th missing positive integer.

    A positive integer is considered missing if it does not appear in nums.

Examples
    nums = [2, 3, 4, 7, 11]
    k = 5
    Output: 9

    The missing positive integers are:
        1, 5, 6, 8, 9, 10, ...
        The 5th missing number is 9.


    nums = [1, 2, 3, 4]
    k = 2
    Output: 6

    missing numbers are
        5, 6, ...


Constraints
    1 <= nums.length <= 1000
    1 <= nums[i] <= 1000
    1 <= k <= 1000

Brute force:
    we can put all nums inside a unordered_set
    then we start a loop from 1
        everytime there is a miss we reduce k
    when k is zero
        the result is i

    O(n) extra space
    O(n+k) time

Observation:

    if we have numbers [1,2,3,4]
    and we have [1,2,4,5]

    we can see that at idx 3, we should have idx+1 number present if no missing
    for 1st vec 3+1 == 4 no missing

    at idx 3+1 should 4 but we have 5
        so there are 5-4 = 1 missing element
    
    we can use binary search to reduce the search space

    lets try  
        nums = [2, 3, 4, 7, 11]
             = [0, 1, 2, 3,  4]
    k = 5

    low = 0
    high = 4
    mid = 2
        expected = 3
        actual = 4
        1 missing upto this point
    discard first half

    low = 3
    high = 4
        mid = 3
        expected = 4
        actual = 7
        missing = 7-3 = 4

    move ahead
    low = 4
    high = 4
    mid= 4
        expected = 5
        actual = 11
        missing = 11-5 = 6

    11 has missing at 6
    10 is the 6th
    9 is the 5th return



Invariant:
Algorithm:
Complexity:

Review
    this is a problem not in my sheet
    the final answer was not possible for me to derive
    this is present in the probl sheet

    Recognition: 🟢
    Derivation: 🟢
    Implementation: not tested

    find boundary where missing >= k
        then
        answer = boundary + k.

*/

/*
Problem 3 — Day 1B

    You are given an array height where height[i] represents the height of a vertical bar of width 1.

    Compute how much water can be trapped between the bars after raining.

    Example 1

this is trapping rainwater

Brute force:

    we can calculate for each i
        
        leftMax
            L-R
        then rightMax
            R-L
        then water for each
        3N pass

        we can use a stack
        or will an array work?
            an array should work for max arrays

    O(3n) time
    O(2N) space

Observation:

    for any bar we need the left and right bound
        then water for that bar is min(left,right) - height[i]

Invariant:
    we can also use a single stack to replace all these
        we keep an increasing stack

    when we find an element greater than top
        right = curr
        int mid = st.top
        st.pop
        int left = st.empty() ? -1: st.top();

        ans[i] = max(min(height[left], height[right]) - height[i], 0)



    we can also use a 2 pointer solution
        instead of calculating for each idx

        we use greedy choices to determine
        if we know that r pointer is higher than l
            then the leftMax is enough to calc water
        vice versa is also true

        l=0
        r =n-1

        water = 0
        while(l<r)
            leftMax = max(leftMax, height[l])
            rightMax = max(rightMax, height[r])

            if(height[l] < height[r]) {
                water += max(leftMax - height[l], 0)
                l++;
            }
            else {
                water += max(rightMax - height[r], 0)
                r--
            }
        return water
        
Algorithm:
Complexity:
    O(n) for stack
    O(n) space

    2 pointer
    O(n) time
    O(1) space
*/


/*
Day 2

    Linked List
    BST
    Binary Search

-------------------------------
Problem 1

    You are given the head of a singly linked list.

    Return the list after rotating it to the right by k places.

    A rotation moves the last node to the front.

    Example 1
        head = [1,2,3,4,5]
        k = 2

        Output = [4,5,1,2,3]

    Example 2
        head = [0,1,2]
        k = 4

        Output = [2,0,1]

    0 <= k <= 10^9
    0 <= number of nodes <= 500


Brute force:
    store linked list in vector
        use temp vector with modulo to store answer
    overwrite back rotated ans into linked list
    
Observation:
    we can save the extra space by connecting the tail to head
    then we need to know where the new head or new tail will be
    disconnect it

    to understand where the new head / new tail 
    will be we need the length of the linked list
    then k = k%n

Invariant:
Algorithm:

    Node* f(Node* head) {

        if(!head || !head->next || k==0)
            return head
        
        Node* curr = head;
        int n = 1;
        while(curr->next) {
            curr = curr->next;
            n++;
        }
        
        k = k % n;
        if(k==0)
            return head;

        curr->next = head; // make circular
        for(int i=0; i<n-k; i++) {
            curr = curr->next;
        }
        Node* newHead = curr->next;
        curr->next = nullptr;
        return newHead;
    }

Complexity:
    O(n) for len
    O(k) for find newHead
    O(n+k) total
    O(1) space

-------------------------------
Review
    green
    O(n) to find new head after connection
    to total is O(n)



-------------------------------
Problem 2 — Day 2
    You are given the root of a binary search tree and two nodes p and q 
    that are guaranteed to exist in the tree.

    Return their lowest common ancestor (LCA).

    The lowest common ancestor is the deepest node that has both p and q 
    as descendants. A node can be considered a descendant of itself.


Brute force:

    store path to node into vector for 1st node
    store path to node into vector for 2nd node
    use 2 pointer and walk down both nodes
        last common node is answer

Observation:
    BST allows us to scan for range in logn time
    we can discard left or right or we can return current node
Invariant:

    if both are lesser
        look left
    if both are more
        look right

    check left and right
    then decide

Algorithm:

    Node* helper(Node* node, Node* a, Node* b) {
        if(!node)
            return node;

        if(node->val > a->val && node->val > b->val)
            return helper(node->left, a, b);

        if(node->val < a->val && node->val < b->val)
            return helper(node->right, a, b);

        return nullptr;
    }

    Node* lca(Node* node, Node* a, Node* b) {

        if(!node)
            return node        

        Node* left  = helper(node->left, a, b);
        Node* right = helper(node->right, a, b);

        if(left && right)
            return node

        return left ? left : right;
    }
    
Complexity:
    O(n) to check every node, not sure


---------------------------------------------------------------------

Problem 3 — Day 2

    You are given an integer array nums of length n where:

    nums[i] ∈ [1, n]

    Every integer appears once or twice, and exactly one integer appears 
    twice.

    Find the integer that appears twice.

    You must solve it in:

    O(n) time
    O(1) extra spac

    Example 1
        nums = [1, 3, 4, 2, 2]
        Output: 2
        
    Example 2

        nums = [3, 1, 3, 4, 2]
        Output: 3

    Example 3
        nums = [1, 1]
        
        Output: 1


i will sort and then use index to discard half
    This is a 🔴 recognition for the constrained version — and that's 
    okay. This is exactly why we're doing mixed practice.
*/

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// day 2 was 14th aug
// 15 aug
/*
Day 3

    Stack
    Tree
    Linked List
---------------------------

Problem 1

    You are given a binary tree.

    Return the maximum width of the tree.

    The width of a level is defined as the distance between the leftmost 
    and rightmost non-null nodes at that level, counting the positions of 
    the null nodes between them.

              1
            /   \
           3     2
          / \     \
         5   3     9

    level 0 → 1
    level 1 → 2
    level 2 → 4

    5  3  null  9
    ↑                 ↑
    leftmost       rightmost

    Brute force:
        we use heap indexing
            left child  = (idx*2) + 1
            right child = (idx*2) + 2

        then for each level:
            width = last - first
        
        track max_width for all levels
            and return

    Observation:
        value if index will explode
            instead we can normalize them
            let: 
                first = first-first
                second = second - first
                ...
                last = last - first

        

    Invariant:
    Algorithm:
        int max_width(Node* root) {

            if(!root)
                return 0

            // node, idx
            queue<pair<Node*,int>> q;
            q.push({root, 0});
            int max_width = 0;

            while(!q.empty()) {
                int size = q.size();

                int first = 0, last = 0;
                int curr = 0;

                for(int i=0; i<size; i++) {
                    auto &[node, idx] = q.front();
                    q.pop();

                    if(i==0)
                        first = idx;
                    if(i==size-1)
                        last = idx;
                    
                    curr -= idx;

                    if(node->left)
                        q.push({node->left, (curr*2)+1});

                    if(node->right)
                        q.push({node->right, (curr*2)+2});
                }
                int width = last - first;
                max_width = max(max_width, width);
            }

            return max_width;
        }

    Complexity:
        O(n) every node gets pushed once
        O(h) space? not sure about space complexity here
---------------------------
Review
    Recognition: 🟢
    You remembered the positional-index trick and even remembered the 
    normalization idea after ~5 days.

    Implementation: 🟡
    You knew what you wanted to do, but confused the queue position i 
    with the heap index idx, and missed the +1.

---------------------------

Problem 2

    You are given the head of a singly linked list.

    Reverse the nodes of the list in groups of k and return the modified list.

    If the number of nodes remaining is less than k, leave those nodes unchanged.


    Example 1
        head = [1,2,3,4,5]
        k = 2

        Output = [2,1,4,3,5]

    Example 2
        head = [1,2,3,4,5]
        k = 3

        Output = [3,2,1,4,5]
        
    Example 3
        head = [1,2,3,4]
        k = 4

        Output = [4,3,2,1]

Brute force:
    copy to vector
        use pointers to reverse the array values
        overwrite linked list
Observation:
    we can k value to count the nodes to be reversed
    then we have
        groupPrev -> 1 -> 2 -> 3 -> groupNext
    
        we reverse the nodes inbetween
            groupPrev -> 3 -> 2 -> 1 -> groupNext
Invariant:
Algorithm:

    Node* reverseKGroup(Node* head, int k) {

        if(!head || !head->next || k == 0)
            return head;

        Node* dummy(-1);
        Node* groupPrev = &dummy;

        while(true) {

            Node* kth = groupPrev->next;

            for(int i=0; i<k; i++) {
                kth = kth->next;
                if(!kth)
                    return dummy.next;
            }

            Node* groupNext = kth->next;
            Node* prev = groupNext;
            Node* curr = groupPrev->next;

            while(curr != groupNext) {
                Node* next = curr->next;
                curr->next = prev;

                
                prev = curr;
                curr = next;
            }
            
            Node* oldStart = groupPrev->next;
            groupPrev->next = kth;
            groupPrev = oldStart;

        }
        return dummy.next;
    }
Complexity:
    O(n) time
    O(1) space

-----------------
Review
    Reverse K Group

    Recognition: 🟢
    Implementation: 🟡

    This is a good Yellow, not a conceptual problem. You knew the entire 
    pointer structure; you just made the classic prev/curr reversal 
    mistake.

-----------------
Problem 3

    You are given the root of a binary tree. Return the right-side view 
    of the tree.

    Imagine you are standing on the right side of the tree. Return the 
    nodes you can see, from top to bottom.

        1
       / \
      2   3
       \   \
        5   4

    [1, 3, 4]

Brute force:
    we can perform the bfs level order into vector of vector
        then we only take back of each level into final answer
Observation:
    instead we can just push once per level
    and skip other nodes at the same level
    process right child first
    by pushing right children into the queue first
Invariant:
Algorithm:

    vector<int> rightView(Node* root) {

        vector<int> ans;

        if(!root)
            return ans;

        queue<pair<Node*, int>> q;
        q.push({root, 0});

        while(!q.empty()) {
            auto [node, level] = q.front();
            q.pop();

            if(ans.size() == level) {
                ans.push_back(node->val);
            }

            if(node->right) {
                q.push({node->right, level + 1});
            }

            if(node->left) {
                q.push({node->left, level + 1});
            }            
        }
        return ans;
    }

Complexity:
    O(n) every node processed
    O(n) max level is stored in queue, can be worst O(n) 

-----------------------
Review
    This is 🟢 Green. Your reasoning and implementation are both solid.
*/