/*
aug 30
    last aug 27th

----------------------
Problem 1

    You are given an array nums where nums[i] represents the maximum 
    number of positions you can jump forward from index i.

    You start at index 0.

    Return whether you can reach the last index.

    Examples
        nums = [2,3,1,1,4]
        Output: true

        0 → 1 → 4
    ---
        nums = [3,2,1,0,4]
        Output: false


Brute force:
    for each idx starting from 0
        take idx + nums[idx] steps
        track maxIdx reached

    return true if >= lastIdx

Observation:
    since we just want feasibility
        track the max and move ahead

        if we encounter a larger than max
            then we cant proceed
Invariant:
Algorithm:
    bool canJump(vector<int> &nums) {
        int n = nums.size();
        int farthest = 0;

        for(int i=0; i<n; i++) {
            farthest = max(farthest, i+nums[i]);

            if(i > farthest)
                return false;
        }
        return true;
    }
Complexity:
    O(n) time
    O(1) space
----------------------
Review
    green


----------------------

Problem 2

    You are given k sorted linked lists.

    Merge them into one sorted linked list and return its head.

    lists = [
        1 -> 4 -> 5,
        1 -> 3 -> 4,
        2 -> 6
        ]

    1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6

Brute force:
    we put all nodes into a vector
        then sort
        then create a new sorted list
Observation:
    lists are sorted
    we can just choose the lowest of the k lists
    then repeat

    using a minHeap
Invariant:
Algorithm:

    Node* kSortedLists(vector<Node*> lists) {
        int k = lists.size();

        auto cmp = [](const auto &a, const auto &b) {
            return a->val > b->val;
        }

        priority_queue<Node*, vector<Node*>, decltype(cmp)> pq(cmp);


        for(int i=0; i<k; i++)
            pq.push(lists[i]);


        Node dummy(-1);
        Node* curr = &dummy;

        while(!pq.empty()) {
            Node* node = pq.top();
            curr->next = node;

            if(node->next)
                pq.push(node->next)

            curr = node;
        }
        return dummy.next;
    }
Complexity:
    O(total nodes log k) time
    O(k) space

----------------------
Review
    green


----------------------
Problem 3 — Older Topic


    You are given a linked list.

    Determine whether the linked list contains a cycle.

    A cycle exists if, by repeatedly following next pointers, you 
    eventually reach a node that you have already visited.

Brute force:
    maintain a unordered_set of nodes
    if we find a duplicate during iteration we have a cycle
Observation:
    we can use 2 pointers
        move fast by 2 places
        slow by 1 place
    if theres a cycle
        they will meet
    if no cycle no meeting
Invariant:
Algorithm:
    bool hasCycle(Node* head) {
        if(!head)
            return false;

        Node* slow = head;
        Node* fast = head;

        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;

            if(fast == slow)
                return true;
        }
        return false;
    }
Complexity:
    O(n) time
    O(1) space

*/