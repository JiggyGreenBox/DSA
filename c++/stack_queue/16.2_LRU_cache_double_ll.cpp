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
    Node* head;
    Node* tail;    
    unordered_map<int, Node*> mpp;


    // consider head to be a sentinel
    // insert between head and head->next
    void insert(Node* node) {
        
        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
    }

    // remove from dll
    void remove(Node* node) {
        // unlink old pointers
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

public:
    LRUcache(int cap) {
        capacity = cap;
        head = new Node(-1,-1);
        tail = new Node(-1,-1);
        head->next = tail;
        tail->prev = head;
    }    

    int get(int key) {
        if(mpp.find(key) == mpp.end())
            return -1;
        
        Node* node = mpp[key];

        remove(node);
        insert(node);

        return node->val;
    }
    
    // 1. update if existing return
    // 2. check cap and delete last dll node
    // 3. put new node in the front of dll
    void put(int key, int value) {
        // update existing node
        if(mpp.find(key) != mpp.end()) {
            
            Node* node = mpp[key];
            node->val = value;

            remove(node);
            insert(node);
            return;
        }
        
        // tail is also a sentinel
        if(mpp.size() == capacity) {
            Node *lru = tail->prev;

            remove(lru);
            mpp.erase(lru->key);            
            delete lru;
        }

        Node* node = new Node(key, value);

        insert(node);
        mpp[key] = node;
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

/*

head and tail are dummy (sentinel) nodes. They do not store real cache entries.

HEAD <-> TAIL
HEAD <-> 1 <-> TAIL
HEAD <-> 2 <-> 1 <-> TAIL
HEAD <-> 3 <-> 2 <-> 1 <-> TAIL


head->next = Most Recently Used
tail->prev = Least Recently Used

we use dummy nodes to prevent null checks
and simplify code implementation

    Dummy nodes:
    - Prevent null checks.
    - Remove special-case logic.
    - Make insert/remove uniform.
*/