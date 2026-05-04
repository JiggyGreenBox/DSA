#include <iostream>
#include <vector>
#include <memory>
#include <vector>
#include <string>
using namespace std;


// ============================================================================


// ============================================================================


// Shared pointers and weak pointers
// the problem?
// what happens when there is a cycle of pointers?
struct Node {
    string name;
    shared_ptr<Node> next;
    shared_ptr<Node> prev;
    Node(string s) : name(s) {
        cout << "Node: " << name << " created" << endl;
    }
    ~Node() {
        cout << "Node: " << name << " destroyed" << endl;
    }
};


struct Node_Safe {
    string name;
    shared_ptr<Node_Safe> next;
    weak_ptr<Node_Safe> prev;
    Node_Safe(string s) : name(s) {
        cout << "Node: " << name << " created" << endl;
    }
    ~Node_Safe() {
        cout << "Node: " << name << " destroyed" << endl;
    }
};
int main(){

    {
        shared_ptr<Node> n1 = make_shared<Node>("A");
        shared_ptr<Node> n2 = make_shared<Node>("B");
        cout << n1.use_count() << endl; // 1
        cout << n2.use_count() << endl; // 1
    }   // output:
            // Node: A created
            // Node: B created
            // Node: B destroyed
            // Node: A destroyed

    {
        shared_ptr<Node> n1 = make_shared<Node>("C");
        shared_ptr<Node> n2 = make_shared<Node>("D");

        cout << n1.use_count() << endl; // 1
        cout << n2.use_count() << endl; // 1

        n1->next = n2;   // +1 , 2
        n2->prev = n1;   // +1 , 2

        cout << n1.use_count() << endl; // 2
        cout << n2.use_count() << endl; // 2
    }   // output:
            // Node: C created
            // Node: D created
            // NO DESTRUCTOR CALLED

    {
        shared_ptr<Node_Safe> n1 = make_shared<Node_Safe>("E");
        shared_ptr<Node_Safe> n2 = make_shared<Node_Safe>("F");        

        cout << n1.use_count() << endl; // 1
        cout << n2.use_count() << endl; // 1

        n1->next = n2; // +1
        n2->prev = n1; // +0, prev is weak so doesnt add to n1

        cout << n1.use_count() << endl; // 1 <---- MAIN POINT
        cout << n2.use_count() << endl; // 2
    }   // output:
            // Node: E created
            // Node: F created
            // 1
            // 1
            // 1  <----------MAIN POINT
            // 2
            // Node: E destroyed
            // Node: F destroyed
    

    
    
    return 0;
}