```cpp
#include <algorithm> // Required for std::swap

// Selects the median of the elements at indices low, mid, and high,
// and moves that median element to the 'high' index (the typical pivot position).
void medianOfThree(std::vector<int>& arr, int low, int high) {
    
    // Calculate the index of the middle element
    int mid = low + (high - low) / 2;

    // 1. Check low and mid: Ensure arr[low] <= arr[mid]
    if (arr[low] > arr[mid]) {
        std::swap(arr[low], arr[mid]);
    }

    // 2. Check low and high: Ensure arr[low] <= arr[high]
    if (arr[low] > arr[high]) {
        std::swap(arr[low], arr[high]);
    }

    // 3. Check mid and high: Ensure arr[mid] <= arr[high]
    // After step 2, arr[low] is the smallest of the three.
    // Now we swap arr[mid] and arr[high] if needed so the final pivot (arr[high])
    // is the median of the three values.
    if (arr[mid] > arr[high]) {
        std::swap(arr[mid], arr[high]);
    }
    
    // NOTE: After these 3 swaps, the elements are ordered: arr[low] <= arr[mid] <= arr[high].
    // The median is now at arr[mid]. For a standard Lomuto partition (pivot = last element), 
    // the median is typically moved to the 'high-1' position, or to the 'high' position
    // if the true last element is reserved for the pivot swap.
    
    // In many implementations, we move the median (now at arr[mid]) to the second to last spot (high - 1)
    // and reserve arr[high] for the final pivot placement after partitioning.
    // However, if we simplify and make arr[high] the pivot for the partition function:
    
    // To ensure the median is the final pivot (at 'high'):
    std::swap(arr[mid], arr[high]); 
    // Now, arr[high] holds the median and is used as the pivot value in the partition function.
}

/*
// Example of how it would be called inside a partition function setup:
int partition(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        medianOfThree(arr, low, high);
        
        // Now arr[high] is guaranteed to hold the median of the three indices,
        // making it the pivot for the rest of the partition logic.
        int pivot = arr[high]; 
        // ... rest of partition logic (e.g., Lomuto) ...
    }
    // ...
}
*/
```