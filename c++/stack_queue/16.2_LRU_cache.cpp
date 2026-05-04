#include <iostream>
#include <unordered_map>
using namespace std;

struct Node{
    Node* prev;
    Node* next;
    int key;
    int val;
    Node(int k, int v): key(k), val(v), prev(nullptr), next(nullptr){}
};

class LRUcache {
private:
    int capacity;
    int size;
    Node* head;
    Node* tail;    
    unordered_map<int, Node*> mpp;
public:
    LRUcache(int c) {
        size = 0;
        capacity = c;
        head = new Node(-1,-1);
        tail = new Node(-1,-1);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if(mpp.find(key) == mpp.end()) return -1;

        // access node
        Node* node = mpp[key];

        // unlink old pointers
        node->prev->next = node->next;
        node->next->prev = node->prev;

        // adjust head pointer 
        // update forward pointers
        head->next->prev = node;
        node->next = head->next;
        // update backward pointers
        head->next = node;
        node->prev = head;        

        return node->val;
    }

    // 1. update key and move if exists
    // 2. check size
    // 3. size < capacity-1: insert head
    // 4. size == capacity-1: delete last and insert head
    
    void put(int key, int value) {
        if(mpp.find(key) != mpp.end()) {
            // update node with new value
            Node* node = mpp[key];
            node->val = value;

            // unlink old pointers
            node->prev->next = node->next;
            node->next->prev = node->prev;

            // adjust head pointer 
            // update forward pointers
            head->next->prev = node;
            node->next = head->next;
            // update backward pointers
            head->next = node;
            node->prev = head;
        }
        // just insert
        else if(size < capacity){
            // create new node
            Node* node = new Node(key, value);
            mpp[key] = node;
            size++;

            // adjust head pointer
            // update forward pointers
            head->next->prev = node;
            node->next = head->next;
            // update backward pointers
            head->next = node;
            node->prev = head;
        }
        // insert and delete
        else{
            Node* node = new Node(key, value);
            mpp[key] = node;
            // size++;

            // adjust head pointer
            // forward pointers
            head->next->prev = node;
            node->next = head->next;
            // backward pointers
            head->next = node;
            node->prev = head;

            // delete node before tail
            Node* toDelete = tail->prev;            
            tail->prev = toDelete->prev;
            toDelete->prev->next = tail;

            mpp.erase(toDelete->key);
            delete toDelete;
        }
    }

};

int main() {
    LRUcache cache(2);

    cache.put(1,1);
    cache.put(2,2);
    cout << cache.get(1) << endl;
    cache.put(3,3);
    cout << cache.get(2) << endl;
    cout << cache.get(3) << endl;
    cache.put(5,5);
    cache.put(10,10);
    cout << cache.get(3) << endl;
    cout << cache.get(10) << endl;

    return 0;
}