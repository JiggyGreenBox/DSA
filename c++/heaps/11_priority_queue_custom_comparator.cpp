#include <iostream>
#include <queue>
using namespace std;


void print(priority_queue<int>& pq) {
    while(!pq.empty()) {
        cout << pq.top() << endl;
        pq.pop();
    }
    cout << endl;
}

void print(priority_queue<int, vector<int>, greater<int>> &pq) {
    while(!pq.empty()) {
        cout << pq.top() << endl;
        pq.pop();
    }
    cout << endl;
}


struct Node
{
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};


int main() {

    priority_queue<int> pq;

    pq.push(1);
    pq.push(2);
    pq.push(3);

    print(pq);

    priority_queue<int, vector<int>, greater<int>> pq2;
    pq2.push(3);
    pq2.push(2);
    pq2.push(1);
    print(pq2);
    
    
    
    // return true means a comes after b
    // true means the second comes before first
    // think inverted
    auto cmp = [](const Node &a, const Node &b) {
        return a.val < b.val;
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> pq3(cmp);

    for(int i=0; i<5; i++) {
        pq3.push(Node(i));
    }

    while(!pq3.empty()) {
        cout << "node:" << pq3.top().val << endl;
        pq3.pop();
    }

    return 0;
}