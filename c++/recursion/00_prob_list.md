 - add sudoku solver

core
permutations.cpp
permutations_ii.cpp
combination_sum_ii.cpp
partition_k_equal_sum_subsets.cpp


sde2/hard expansion
kth_permutation.cpp
restore_ip_addresses.cpp
expression_add_operators.cpp
remove_invalid_parentheses.cpp
m_coloring.cpp

1. Take / Don't Take
   ├── subsets
   ├── subsequences
   └── subset sums

2. Choose / Unchoose
   ├── permutations
   ├── combinations
   ├── combination sum
   └── letter combinations

3. Partition
   ├── palindrome partitioning
   ├── restore IP
   └── expression problems

4. Constraint Backtracking
   ├── word search
   ├── N-Queens
   ├── Sudoku
   └── graph coloring

5. Bucket / Assignment Backtracking
   ├── partition K subsets
   └── similar scheduling/assignment problems


RECURSION / BACKTRACKING

1. Linear recursion
   └── pow

2. Take / Don't Take
   ├── subsets
   ├── subsequences
   └── subset sums

3. Choose / Unchoose
   ├── combinations
   ├── permutations
   ├── combination sum
   └── letter combinations

4. Partition DFS
   ├── palindrome partitioning
   ├── restore IP
   └── expression add operators

5. Constraint Backtracking
   ├── N-Queens
   ├── Sudoku
   ├── graph coloring
   └── word search

6. Grid DFS
   ├── word search
   └── rat in a maze

7. Bucket / Assignment
   └── partition K subsets

8. State-based recursion
   ├── generate parentheses
   └── expression problems


So the actual additions I'd make

Definitely:

LC 77 — Combinations
LC 980 — Unique Paths III
LC 1219 — Path with Maximum Gold
LC 1255 — Maximum Score Words Formed by Letters

Optional hard expansion:

LC 1593 — Split a String Into the Max Number of Unique Substrings
LC 52 N-Queens II You have it


recursion/
├── 00_prob_list.md
├── 00_patterns.md
│
├── 01_linear_recursion/
│   └── 01_pow.cpp
│
├── 02_take_dont_take/
│   ├── 01_power_set.cpp
│   ├── 02_subsets_strings.cpp
│   ├── 03_subset_sums.cpp
│   ├── 04_check_subsequence_sum.cpp
│   └── 05_count_subsequences_with_target_sum.cpp
│
├── 03_choose_unchoose/
│   ├── 01_combinations.cpp                 # LC 77 NEW
│   ├── 02_permutations.cpp
│   ├── 03_permutations_ii.cpp
│   ├── 04_combination_sum.cpp
│   ├── 05_combination_sum_ii.cpp
│   ├── 11_combination_sum_iii.cpp
│   └── 12_letter_combinations.cpp
│
├── 04_partition/
│   ├── 13_palindrome_partitioning.cpp
│   ├── 14_restore_ip_addresses.cpp
│   ├── 15_expression_add_operators.cpp
│   ├── 16_split_string_max_unique_substrings.cpp  # LC 1593 optional
│   └── 17_remove_invalid_parentheses.cpp
│
├── 05_constraint_backtracking/
│   ├── 18_n_queens.cpp
│   ├── 19_n_queens_ii.cpp
│   ├── 20_sudoku_solver.cpp
│   └── 21_m_coloring.cpp
│
├── 06_grid_backtracking/
│   ├── 22_word_search.cpp
│   ├── 23_rat_in_a_maze.cpp
│   ├── 23_unique_paths_iii.cpp             # LC 980 NEW
│   └── 24_path_with_maximum_gold.cpp       # LC 1219 NEW
│
├── 07_bucket_assignment/
│   ├── 25_partition_k_equal_sum_subsets.cpp
│   └── 26_maximum_score_words.cpp          # LC 1255 NEW
│
└── 08_state_based/
    └── 27_generate_parentheses.cpp