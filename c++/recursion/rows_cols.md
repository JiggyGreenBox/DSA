In C++, the canonical way to iterate over a matrix depends on whether you are using **row-major** indexing (standard for 2D arrays and `std::vector<vector>`) or **Range-based** loops (modern C++).

---

## 1. The Standard Index-Based Loop

This is the most common structure used in competitive programming and technical interviews.

**Canonical Variables:**

* `i` or `r` for **Rows**.
* `j` or `c` for **Columns**.
* `n` or `rows` for the number of rows.
* `m` or `cols` for the number of columns.

```cpp
int n = matrix.size();
int m = matrix[0].size();

for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
        // Access element at matrix[i][j]
        std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
}

```

### Why this order? (Row-Major Order)

C++ stores 2D arrays in **row-major order**. This means all elements of the first row are stored contiguously in memory, followed by the second row.

By keeping the row loop (`i`) on the outside and the column loop (`j`) on the inside, you access memory sequentially. This is **cache-friendly** and significantly faster than column-major iteration.

---

## 2. The Modern C++ Way (Range-Based)

If you don't need the index values (`i` and `j`) and just need to process the data, use range-based `for` loops. This is cleaner and prevents "off-by-one" errors.

```cpp
for (auto& row : matrix) {       // Use reference to avoid copying the row
    for (auto& element : row) {  // Access each element
        element *= 2;            // Example: modify element
    }
}

```

---

## 3. Best Practices for Backtracking

When you are doing backtracking on a grid (like your Word Search or N-Queens solutions), the canonical structure often includes **boundary checks** and **direction vectors**.

### Direction Vectors

Instead of writing four `if` statements for Up, Down, Left, and Right, we use "Direction Vectors" to loop through neighbors:

```cpp
// Canonical direction vectors: Up, Down, Left, Right
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

for (int i = 0; i < 4; ++i) {
    int next_r = curr_r + dr[i];
    int next_c = curr_c + dc[i];
    
    // Check boundaries before recursing
    if (next_r >= 0 && next_r < n && next_c >= 0 && next_c < m) {
        // Explore next_r, next_c
    }
}

```

---

## Comparison Table

| Style | Syntax | Best Use Case |
| --- | --- | --- |
| **Index-based** | `matrix[i][j]` | When indices are needed for math or backtracking. |
| **Range-based** | `auto& x : row` | Simple traversal, reading/writing all values. |
| **Flat-loop** | `matrix[i/m][i%m]` | Converting a 2D problem into a 1D loop. |

**Pro Tip:** Always use `prefix increment` (`++i`) rather than `postfix increment` (`i++`) in C++ loops. While modern compilers optimize both for integers, `++i` is the canonical habit as it is more efficient for custom iterators.

Would you like to see how to implement the **Direction Vector** approach in your Word Search code to make it more compact?