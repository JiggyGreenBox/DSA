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
    int cap;
    int size;
    Node* head;
    Node* tail;    
    unordered_map<int, Node*> cache;
public:
    LRUcache(int capacity) {
        size = 0;
        cap = capacity;
        head = new Node(-1,-1);
        tail = new Node(-1,-1);
        head->next = tail;
        tail->prev = head;
    }

    void moveAfterHead(Node* node) {
        // adjust head pointer 
        // update forward pointers
        head->next->prev = node;
        node->next = head->next;
        // update backward pointers
        head->next = node;
        node->prev = head;
    }

    void remove(Node* node) {
        // unlink old pointers
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void deleteBeforeTail() {
        // delete node before tail
        Node* toDelete = tail->prev;
        remove(toDelete);
        cache.erase(toDelete->key);        
        delete toDelete;
        size--;
    }

    int get(int key) {
        if(cache.find(key) == cache.end()) return -1;
        
        Node* node = cache[key];
        remove(node);
        moveAfterHead(node);
        return node->val;
    }

    // 1. update key and move if exists
    // 2. check size
    // 3. size < capacity-1: insert head
    // 4. size == capacity-1: delete last and insert head
    
    void put(int key, int value) {
        // update existing node
        if(cache.find(key) != cache.end()) {
            
            Node* node = cache[key];
            node->val = value; // update node with new value

            remove(node);
            moveAfterHead(node);
        }
        // insert new node
        else{
            if(size == cap) {
                deleteBeforeTail();
            }

            Node* node = new Node(key, value);
            cache[key] = node;
            moveAfterHead(node);
            size++;
        }
    }

    ~LRUcache() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};

int main() {
    LRUcache cache(2);

    cache.put(1,1);
    cache.put(2,2);
    cout << cache.get(1) << endl;   // 1
    cache.put(3,3);
    cout << cache.get(2) << endl;   // -1
    cout << cache.get(3) << endl;   // 3
    cache.put(5,5);
    cache.put(10,10);
    cout << cache.get(3) << endl;   // -1
    cout << cache.get(10) << endl;  // 10

    return 0;
}