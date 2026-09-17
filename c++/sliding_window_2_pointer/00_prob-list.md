# add
11 Minimum Size Subarray Sum          ★ ADD
12 Subarray Product Less Than K      ★ ADD
13 Permutation in String             ★ ADD
14 Find All Anagrams in a String     optional

Minimum Size Subarray Sum
    ↓
Subarray Product Less Than K
    ↓
Permutation in String
    ↓
your existing sliding-window problems
    ↓
harder/composite problems


    LC 209 — Minimum Size Subarray Sum ⭐
    LC 713 — Subarray Product Less Than K ⭐
    LC 567 — Permutation in String ⭐
    LC 30 — Substring with Concatenation of All Words 🔥
    LC 239 — Sliding Window Maximum 🔥
    LC 862 — Shortest Subarray with Sum at Least K 🔥

check these later
30   Substring with Concatenation    🔥
76   Minimum Window Substring        🔥
327  Count of Range Sum              🔥


🟢 Tier 1 — Core / must know
| # | Problem                                                               | Main pattern                           |
| - | --------------------------------------------------------------------- | -------------------------------------- |
| 1 | **LC 643 — Maximum Average Subarray I**                               | Fixed-size window                      |
| 2 | **LC 1456 — Maximum Number of Vowels in a Substring of Given Length** | Fixed-size window                      |
| 3 | **LC 209 — Minimum Size Subarray Sum**                                | Variable window, positive nums         |
| 4 | **LC 3 — Longest Substring Without Repeating Characters**             | Variable window + frequency/last index |
| 5 | **LC 904 — Fruit Into Baskets**                                       | At most 2 distinct                     |
| 6 | **Longest Substring with At Most K Distinct Characters**              | At most K distinct                     |
| 7 | **LC 424 — Longest Repeating Character Replacement**                  | Window − max frequency                 |
| 8 | **LC 76 — Minimum Window Substring**                                  | Minimum valid window                   |


🟡 Tier 2 — Important extensions
| #  | Problem                                                          | Pattern                   |
| -- | ---------------------------------------------------------------- | ------------------------- |
| 9  | **LC 567 — Permutation in String**                               | Fixed window + frequency  |
| 10 | **LC 438 — Find All Anagrams in a String**                       | Fixed window + frequency  |
| 11 | **LC 930 — Binary Subarrays With Sum**                           | `atMost` trick / prefix   |
| 12 | **LC 1248 — Count Number of Nice Subarrays**                     | `atMost(K) - atMost(K-1)` |
| 13 | **LC 1004 — Max Consecutive Ones III**                           | At most K violations      |
| 14 | **LC 1493 — Longest Subarray of 1's After Deleting One Element** | At most one zero          |
| 15 | **LC 1658 — Minimum Operations to Reduce X to Zero**             | Complementary subarray    |


🟠 Tier 3 — Deque / monotonic-window problems
| #  | Problem                                                              | Pattern                      |
| -- | -------------------------------------------------------------------- | ---------------------------- |
| 16 | **LC 239 — Sliding Window Maximum**                                  | Monotonic deque              |
| 17 | **LC 1438 — Longest Continuous Subarray With Absolute Diff ≤ Limit** | Two monotonic deques         |
| 18 | **LC 862 — Shortest Subarray With Sum at Least K**                   | Prefix sum + monotonic deque |


🔴 Tier 4 — Hard expansion
| Problem                                                            | Why                                 |
| ------------------------------------------------------------------ | ----------------------------------- |
| **LC 76 — Minimum Window Substring**                               | Already hard enough to master       |
| **LC 30 — Substring with Concatenation of All Words**              | Window + word chunks + frequency    |
| **LC 992 — Subarrays with K Different Integers**                   | Exactly K via atMost                |
| **LC 1358 — Number of Substrings Containing All Three Characters** | Counting valid windows              |
| **LC 480 — Sliding Window Median**                                 | Two multisets / balanced structures |
| **LC 2396-ish / harder variants**                                  | Specialized                         |
| **LC 1438**                                                        | Deques + window                     |
| **LC 862**                                                         | Prefix + deque                      |


643
 ↓
1456
 ↓
209
 ↓
3
 ↓
904
 ↓
K Distinct
 ↓
424
 ↓
1004
 ↓
567
 ↓
438
 ↓
76
 ↓
239
 ↓
992
 ↓
1438



FIXED WINDOW
    ↓
VARIABLE WINDOW
    ↓
COUNTING WINDOWS
    ↓
MORE ADVANCED WINDOWS
    ↓
MONOTONIC DEQUE
    ↓
HARD COMPOSITE

.
├── 00.1_notes_sliding.md
├── 00.2_brute_template.cpp
├── 00_prob_list.md
│
├── 01_maximum_average_subarray.cpp
├── 02_maximum_number_of_vowels.cpp
├── 03_maximum_points_from_cards.cpp
│
├── 04_minimum_size_subarray_sum.cpp
├── 05_longest_substring_without_repeating.cpp
├── 06_fruit_into_baskets.cpp
├── 07_longest_substring_k_distinct.cpp
├── 08_longest_repeating_character_replacement.cpp
│
├── 09_minimum_window_substring.cpp
│
├── 10_permutation_in_string.cpp
├── 11_find_all_anagrams.cpp
│
├── 12_binary_subarrays_with_sum.cpp
├── 13_nice_subarrays.cpp
├── 14_max_consecutive_ones_iii.cpp
├── 15_longest_subarray_after_deleting_one.cpp
├── 16_minimum_operations_reduce_x.cpp
│
├── 17_number_of_substrings_containing_all_three.cpp
├── 18_subarrays_with_k_distinct.cpp
│
├── 19_sliding_window_maximum.cpp
├── 20_longest_continuous_subarray_limit.cpp
├── 21_shortest_subarray_sum_at_least_k.cpp
│
├── 22_substring_concatenation_words.cpp
├── 23_sliding_window_median.cpp
│
└── test.cpp


01–03  Fixed window
04–08  Variable window
09     Minimum valid window
10–11  Fixed frequency window
12–13  AtMost / Exactly counting
14–16  Specialized variable windows
17–18  Hard counting extensions
19–21  Monotonic deque
22–23  Hard composite problems


missing
    Subarrays with K Different Integers
    Sliding Window Maximum
    Longest Continuous Subarray With Absolute Diff ≤ Limit
    Shortest Subarray With Sum at Least K
    Substring with Concatenation of All Words
    Sliding Window Median

17_number_of_substrings_containing_all_three.cpp   ← already present, just rename
18_subarrays_with_k_distinct.cpp                    ← NEW
19_sliding_window_maximum.cpp                       ← NEW
20_longest_continuous_subarray_limit.cpp            ← NEW
21_shortest_subarray_sum_at_least_k.cpp             ← NEW
22_substring_concatenation_words.cpp                ← NEW
23_sliding_window_median.cpp                        ← NEW