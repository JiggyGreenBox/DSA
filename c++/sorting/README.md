## Sorting
 * Bubble sort
   - place the largest number at the back
   - repeat backwards till the first element
   - early exit possible
   - ```cpp
      for(int i=0; i<n-1; i++) 
      {          
        for(int j=0; j<(n-i-1); j++) 
        {
          if(vec[j] > vec[j+1]) {
            swap(vec[j] ,vec[j+1]);
          }
        }
      }
     ```

 * Insertion Sort
    - choose a key [1..n-1]
    - backward compare with [key-1..0]
    - insert into correct position
      - when the postion is found copy every other element forward
    - every element before the key will be sorted
    - repeat till the key is the last element
    -   ```cpp
        int j = i-1;
        while(vec[j] > key) {
            vec[j+1] = vec[j];
            j--;
        }
        vec[j+1] = key;
        ```

  * Selection Sort
    - we find the minimum and put it first
    - track the minimum value is not enough because we need to swap
    - so we track the minimum index
    - put this in the first position and repeat till the end
    - early exit not possible
    - ```cpp
      for(int i=0; i<n-1; i++) { // 0..second-last
          int idx_swap = i;
          for(int j=i+1; j<n; j++) { // 1..last
              if(vec[i] > vec[j]) {
                  idx_swap = j;
              }
          }
          if (idx_swap != i) {
              swap(vec[i], vec[idx_swap]);
          }  
      }
      ```
    



  * Count Sort
    - You count how many of each digit there is, and then you determine each digit's starting position by counting how many cells are taken up by the digits before it

  * Merge Sort
   - TODO
      - use 2 temp arrays for DSA
      - have improved version similar to STL
  * Quick Sort
    - partition is the heart of this algorithm
      - once an element is selected(many options are possible)
      - make sure left is less and right is more
      - continue this till the entire array is sorted
    - 3 types
      - naive
      - lomuto
      - hoare's