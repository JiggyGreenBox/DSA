# shortest job first
* To understand Shortest Job First (SJF) intuition, you have to stop thinking about the "fairness" of arrival order
* and start thinking about minimizing the collective misery (waiting time).

* Imagine you are at a checkout line. There are two people in front of you:

    - Person A: Has a full cart (will take 20 minutes).

    - Person B: Has a single candy bar (will take 1 minute).

        - Scenario 1: First-Come, First-Served (FCFS) If Person A goes first:

            - Person A waits 0 mins.

            - Person B waits 20 mins.

            - Total Waiting Time: 20 mins. Average: 10 mins.

        - Scenario 2: Shortest Job First (SJF) If Person B goes first:

            - Person B waits 0 mins.

            - Person A waits 1 min (while the candy is scanned).

            - Total Waiting Time: 1 min. Average: 0.5 mins.

* 2️⃣ What is “waiting time” exactly?
  ```sh
  waiting time = sum of burst times of all processes executed before it
  ```

* 3️⃣ Why sorting is unavoidable
  ```sh
  bt = [7, 1, 2]

  7 → 1 → 2
  Waiting times: 0, 7, 8 (total = 15)

  1 → 2 → 7
  Waiting times: 0, 1, 3 (total = 4)
  ```

* waiting time for each
  ```sh
    Waiting time of:

    b[0] → 0

    b[1] → b[0]

    b[2] → b[0] + b[1]

    b[3] → b[0] + b[1] + b[2]
  ```

* Total waiting time:
  ```sh
    (b[0]) +
    (b[0] + b[1]) +
    (b[0] + b[1] + b[2]) +
  ```

* This is why you usually keep a running sum.

* solution
  ```cpp
  int average_waiting_time(vector<int>& nums) {
    sort(nums.begin(), nums.end());

    int waiting_i = 0;              // waiting[i] = sum of burst times of previous jobs
    int total_waiting = 0;
    int n = nums.size();
    for(auto num : nums) {
        total_waiting += waiting_i;
        waiting_i += num;           // next job's wait time includes this job's executing time        
    }
    int average = total_waiting/n;
  }
  ```

* why this works
    ```sh

    waiting time for each
    waiting[0] = 0
    waiting[1] = b[0]
    waiting[2] = b[0] + b[1]
    waiting[3] = b[0] + b[1] + b[2]    

    total_waiting_time = waiting[0] + waiting[1] + ... + waiting[n-1]

    total_waiting_time =
    0 +
    b[0] +
    (b[0] + b[1]) +
    (b[0] + b[1] + b[2]) +

    b[0] is added (n-1) times
    b[1] is added (n-2) times
    ...
    b[n-2] is added 1 time
    b[n-1] is added 0 times

    ```