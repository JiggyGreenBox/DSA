#include <iostream>
#include <vector>
using namespace std;

class Solution{
    private:
        vector<int> heap;

        void heapify_up(int i) {
            while(i>0) {
                int parent = (i-1) / 2;

                if(heap[parent] <= heap[i]) break;

                swap(heap[parent], heap[i]);
                i = parent;
            }
        }
        void heapify_down(int i) {
            int n = heap.size();
            while(true) {
                int left = 2*i + 1;
                int right = 2*i + 2;
                int smallest = i;
                if(left < n && heap[left] < heap[smallest]) {
                    smallest = left;
                }
                if(right < n && heap[right] < heap[smallest]) {
                    smallest = right;
                }
                if(smallest == i) break;
                swap(heap[i], heap[smallest]);
                i = smallest;
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

        void changeKey(int index, int new_val){
            if(heap.empty() || index >= heap.size()) return;

            int old = heap[index];
            heap[index] = new_val;

            if(new_val > old) {
                heapify_down(index);
            }
            else{
                heapify_up(index);
            }
        }

        void extractMin(){
            if(heap.empty()) return;
            
            heap[0] = heap.back();
            heap.pop_back();
            heapify_down(0);
        }

        bool isEmpty(){
            return heap.empty();
        }

        int getMin(){
            if(!heap.empty()) return heap[0];
        }

        int heapSize(){
            return heap.size();
        }
};