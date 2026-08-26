#include <iostream>
#include <vector>
#include <algorithm> // Required for std::nth_element

int main() {
    // An unsorted vector
    std::vector<int> numbers = {9, 2, 7, 1, 5, 8, 3, 6, 4};

    // Define the 0-indexed position you want to find
    // Index 3 means the 4th smallest element
    size_t target_index = 3; 

    // Point an iterator to our target index
    auto nth_position = numbers.begin() + target_index;

    // Run the algorithm
    // Syntax: std::nth_element(start, target, end);
    std::nth_element(numbers.begin(), nth_position, numbers.end());

    // Output the result
    std::cout << "The element at index " << target_index 
              << " is: " << *nth_position << "\n\n";

    // Show the state of the vector after partitioning
    std::cout << "Vector state after nth_element:\n";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    return 0;
}


/*
to find the nth element
we only sort the area of interest
*/

#include <iostream>
#include <vector>
#include <utility> // For std::swap

// 1. Partition function: Groups elements around a pivot
// Elements <= pivot go to the left; elements > pivot go to the right
size_t partition(std::vector<int>& arr, size_t low, size_t high) {
    // Choose the last element as the pivot
    int pivot = arr[high];
    size_t i = low;

    for (size_t j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    // Place the pivot in its correct sorted position
    std::swap(arr[i], arr[high]);
    return i; 
}

// 2. Core Quickselect function: Recursively narrows down the search space
void custom_nth_element(std::vector<int>& arr, size_t low, size_t high, size_t target_idx) {
    if (low >= high) return;

    // Partition the array and get the final position of the pivot
    size_t pivot_idx = partition(arr, low, high);

    // If the pivot landed exactly on our target index, we are done!
    if (pivot_idx == target_idx) {
        return;
    }
    // If our target is to the left, only look at the left part
    else if (target_idx < pivot_idx) {
        if (pivot_idx > 0) { // Prevent underflow
            custom_nth_element(arr, low, pivot_idx - 1, target_idx);
        }
    }
    // If our target is to the right, only look at the right part
    else {
        custom_nth_element(arr, pivot_idx + 1, high, target_idx);
    }
}

int main() {
    std::vector<int> numbers = {9, 2, 7, 1, 5, 8, 3, 6, 4};
    size_t target_index = 3; // We want to find the 4th smallest element (index 3)

    std::cout << "Original vector: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n\n";

    // Run our under-the-hood simulation
    custom_nth_element(numbers, 0, numbers.size() - 1, target_index);

    std::cout << "The element at index " << target_index << " is: " << numbers[target_index] << "\n\n";

    std::cout << "Vector state after partitioning: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    return 0;
}
