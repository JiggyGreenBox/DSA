# Monotonic Stack
- What does monotonic mean?
  - A stack is **monotonic** if its elements are kept in **sorted order**.
    - Monotonic increasing: bottom → top is increasing
    - Monotonic decreasing: bottom → top is decreasing
- The Key Intuition:
  - If an element is worse than the current one for all future queries, discard it immediately.
  - The stack keeps only **useful candidates**. 

- Example: Next Greater Element (Right):
    - ```cpp
      // input
      [2, 1, 5, 3]

      // answer
      [5, 5, -1, -1]
      ```
    - Element = 3
        - Stack empty → answer = -1
        - Push 3
        - Stack: [3]
    - Element = 5
        - Pop 3 (why? 3 can never be next greater for anyone left of 5)
        - Stack empty → answer = -1
        - Push 5
        - Stack: [5]
    - Element = 1
        - Stack top 5 > 1 → answer = 5
        - Push 1
        - Stack: [5, 1]
    - Element = 2
        - Pop 1 (1 < 2 → useless)
        - Stack top 5 > 2 → answer = 5
        - Push 2
        - Stack: [5, 2]