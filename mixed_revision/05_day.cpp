// 17th aug
/*
Problem 1

    You are given a rotated sorted array of distinct integers nums.

    Return the minimum element in the array.

    A rotated sorted array is obtained by taking a sorted array and 
    moving some number of elements from the beginning to the end.

    Examples

        nums = [4,5,6,7,0,1,2]
        Output: 0

        nums = [3,4,5,1,2]
        Output: 1

        nums = [1,2,3,4,5]
        Output: 1

1 <= nums.length <= 5000
All values are distinct.

Brute force:

    run a for loop
        and track min
    O(n) time, O(1) space

Observation:
    take advantage of sorted array
        use binary search
            find sorted half
            discard larger half
Invariant:
    answer lies in [l,r]
Algorithm:
    int minelement(vector<int>& nums) {
        int l = 0;
        int r = nums.size() - 1;

        while(l < r) {
            int m = l + (r-l)/2;

            // discard left
            if(nums[l] <= nums[m] && nums[m] > nums[r])
                l = m + 1

            // discard right
            else
                r = m;
        }
        return nums[l]
    }   
Complexity:
    O(logn) time
    O(1) space
--------------------------
Review
    green


while(l < r) {
    int m = l + (r-l)/2;

    if(nums[m] > nums[r])
        l = m + 1;
    else
        r = m;
}

return nums[l];




--------------------------
Problem 2

You are given the head of a singly linked list. Remove the n-th node 
from the end of the list and return the new head.

Examples
    head = [1,2,3,4,5]
    n = 2

    Output:
    [1,2,3,5]

    head = [1]
    n = 1

    Output:
    []

    head = [1,2]
    n = 2

    Output:
    [2]


Brute force:
    store node-vals into array
        then delete node with size-n-1th value
Observation:
    we can use slow and fast pointers
    to keep slow at the pointer we want to delete
    we will keep a prev pointer as well
Invariant:
Algorithm:
    Node* deleteNth(Node* head, int n) {
        if(!head || n==0)
            return head;

        Node dummy(-1);
        Node* prev = &dummy;
        Node* slow = head;
        Node* fast = head;
        int count = 1;

        while(fast && count < n) {
            fast = fast->next;
            count++;
        }

        // n was larger than ll len
        if(!fast)
            return head;

        while(fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next;
        }
        
        prev->next = slow->next;
        delete slow;

        return dummy.next;
    }

Complexity:
    O(n) time
    O(1) space

-------------------------
review
    🟡 Recognition, 🟡 Implementation.

    didnt connect dummy to head
    canonical uses slow instead of prev



Node* removeNthFromEnd(Node* head, int n) {
    Node dummy(-1);
    dummy.next = head;

    Node* slow = &dummy;
    Node* fast = &dummy;

    // Create a gap of n nodes
    for(int i = 0; i < n; i++)
        fast = fast->next;

    // Move until fast reaches the last node
    while(fast->next) {
        slow = slow->next;
        fast = fast->next;
    }

    Node* toDelete = slow->next;
    slow->next = toDelete->next;
    delete toDelete;

    return dummy.next;
}



-------------------------

Problem 3

You are given the root of a binary tree. Return the diameter of the 
tree.

The diameter is the number of edges on the longest path between any 
two nodes in the tree.

        1
       / \
      2   3
     / \
    4   5

    4 → 2 → 1 → 3

    1
     \
      2
       \
        3

    2

Brute force:
    for each node check left and right height        
Observation:
    calculate max at each step to avoid recalculating 
Invariant:
Algorithm:
    int helper(Node* root, int &diameter) {
        if(!root)
            return 0;

        int lh = helper(root->left, diameter);
        int rh = helper(root->right, diameter);

        diameter = max(diameter, lh + rh);

        return 1 + max(lh, rh);
    }
Complexity:
    O(n) time
    O(h) stack space
*/