#include <iostream>
#include <vector>
using namespace std;

class Solution {
    private:
        vector<int> heap;

        void heapify_up(int i) {
            while(i > 0) {
                int parent = (i-1) / 2;

                if(heap[parent] >= heap[i]) break;

                swap(heap[parent], heap[i]);
                i = parent;
            }
        }

        void heapify_down(int i) {
            int n = heap.size();
            while(true) {
                int left = 2*i + 1;
                int right = 2*i + 2;
                int largest = i;

                if(left < n && heap[left] > heap[largest]) {
                    largest = left;
                }

                if(right < n && heap[right] > heap[largest]) {
                    largest = right;
                }

                if(largest == i) break;
                swap(heap[largest], heap[i]);
                i = largest;
            }
        }
    public:

        void initializeHeap(){
            heap.clear();
        }

        void insert(int key){
            heap.push_back(key);
            heapify_up(heap.size()-1);
        }

        // Does the new value want to go closer to the root?
        // → YES → heapify_up
        // → NO  → heapify_down
        void changeKey(int index, int new_val){
            if(heap.empty() || index >= heap.size()) return;
            int old_val = heap[index];
            heap[index] = new_val;

            if(new_val > old_val) {
                heapify_up(index);
            }
            else {
                heapify_down(index);
            }
        }

        void extractMax(){
            if(heap.empty()) return;

            heap[0] = heap.back();
            heap.pop_back();

            heapify_down(0);
        }

        bool isEmpty(){
            return heap.empty();
        }

        int getMax(){            
            return heap[0];
        }

        int heapSize(){
            return heap.size();
        }
};