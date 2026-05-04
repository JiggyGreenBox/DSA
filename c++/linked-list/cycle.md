# cycles in a linked list
* detect a cycle in a linked list
  ```cpp
  bool isCycle(Node* head){
    Node* slow = head;
    Node* fast = head;
    while(fast && fast->next){
      slow = slow->next;
      fast = fast->next->next;
      if(slow == fast) return true;
    }
    return false;
  }
  
  ```

* when the cycle is found. we can use this algorithm to find the node at which the cycle starts:
  ```cpp
  Node* findStartingPoint(Node* head){
    Node* slow = head;
    Node* fast = head;
    while(fast && fast->next){
      slow = slow->next;
      fast = fast->next->next;
      if(slow == fast) {
        slow = head;
        while(slow != fast){
          slow = slow->next;
          fast = fast->next;
        }
        return slow;
      }
    }
    return nullptr;
  }
  ```
## why does this work? explain the algorithm
* our linked list with a cycle:
```sh
1-2-3-4-5-6-7-8-9
          ^     |
          |     |
          <------
```

* nomenclature
```cpp
6 is the starting node of the cycle
1,2,3,4,5 == D (5 nodes before 6)  [Length before cycle]

6,7,8,9,6 == C (4 unique nodes)  [Cycle Length]

6,7,8,9   == K (3 steps after 6)  [Meeting point (9)]
```

* pointer movement
```cpp
nodes per step
s = 1
f = 2

1 2 3 4 5 6 7 8 9
s
f

1 2 3 4 5 6 7 8 9
  s
    f
...
...
1 2 3 4 5 6 7 8 9
        s
                f

1 2 3 4 5 6 7 8 9
                s
                f
               (K)
```

* equations
```sh
# after meeting at K
distF = 2 * distS   ...(1)

distS = D + K       ...(2)

distF = D + K + nC  ...(3)
# nC means a few cycles were completed
```

```sh
distF = 2 * distS

# substituing eq(2), eq(3) in eq(1)
(D + K + nC) = 2*(D + K)
(D + K + nC) = 2D + 2K
nC = D + K

D = nC - K          ...(4)
```

* lets use this formula and the fast and slow nodes to find the cycle start
```sh
# for nodes fast and slow
slow = fast = D+K places 
# move fast to head
increment fast and slow till fast == slow
# this is the cycle start

why??
```

```sh
if fast is at head, and we move it exactly D places ahead
we are at the start of the cycle
1,2,3,4,5 == D (5)  [Length before cycle]

if slow is at K and we move it ahead D places
the final position will be:
posS = K + D steps
posS = K + (nC - K) ...(from eq(4))
posS = nC


nC is a complete cycle from any starting point
so posS is now at the starting point

we know when D steps are taken
not because we know D
but rather when fast_from_head == slow_from_K after D increments
```
---
```
nC = D + K
this means that from K we can take D steps and complete the cycle. 
n maybe >=1 or more

and after moving fast to head, we can reach the start of the cycle, after D steps

after this arrangement D is still unknown

but after each step we check if slow==fast
it is satified at D steps
```

```sh
1,2,3,4,5,6,7,8,9
9 is connected to 6
6,7,8,9,6

D = 1,2,3,4,5 (5)
C = 6,7,8,9,6 (4 distinct nodes)
K = @9 = 3 [6,7,8,9]
    3 nodes after 6, which is the starting node

D + K = 5 + 3 = 8
nC = (2)(4) fast requires 2 complete loops to reach slow

# f not looped yet
1 2 3 4 5 6 7 8 9
        s
                f
# f loop 1
1 2 3 4 5 6 7 8 9
          s
            f
# f loop 1
1 2 3 4 5 6 7 8 9
            s
                f
# f loop 2
1 2 3 4 5 6 7 8 9
              s
            f
# f loop 2
1 2 3 4 5 6 7 8 9
                s
                f

at slow = K=3 (node 9)
and fast = head
lets take D steps (5 steps ahead)

        slow(9)        fast(1)
1       6              2
2       7              3
3       8              4
4       9              5
5       6              6

our equation to find D==5 doesnt matter
all we care is that 6==6 which is the loop start happens after D steps
```