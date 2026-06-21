#include <iostream>
#include <vector>
#include <memory> // smart pointer
using namespace std;

struct ListNode_smart {
    int val;    
    std::shared_ptr<ListNode_smart> next;
    ListNode_smart():val(0), next(nullptr){}
    ListNode_smart(int data):val(data), next(nullptr){}    
    ListNode_smart(int data, std::shared_ptr<ListNode_smart> node):val(data), next(node){} // ADD
    ~ListNode_smart(){
        cout << "Node with data->" << this->val << " destroyed" << endl;
    }
};


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int v) : val(v), next(nullptr) {}
    ListNode(int v, ListNode* node) : val(v), next(node) {}
    ~ListNode(){
        cout << "Node with data->" << this->val << " destroyed" << endl;
    }
};

int main() {

    // block to force destructors
    {
        // shared pointer version
        std::shared_ptr<ListNode_smart> y1 = std::make_shared<ListNode_smart>(2);
        std::shared_ptr<ListNode_smart> y2 = std::make_shared<ListNode_smart>(5);
        std::shared_ptr<ListNode_smart> y3 = std::make_shared<ListNode_smart>(8);
        std::shared_ptr<ListNode_smart> y4 = std::make_shared<ListNode_smart>(7);

        y1->next = y2;
        y2->next = y3;
        y3->next = y4;

        std::shared_ptr<ListNode_smart> temp1 = y1;
        while(temp1 != nullptr){
            cout << temp1->val << endl;
            temp1 = temp1->next;
        }
    }
    
    
    

    ListNode *n1 = new ListNode(1, nullptr);
    ListNode *n2 = new ListNode(2, n1);
    ListNode *n3 = new ListNode(3, n2);
    ListNode *n4 = new ListNode(4, n3);
    ListNode *n5 = new ListNode(5, n4);

    ListNode *head = n5;

    ListNode *temp = n5;
    while (temp) {
        cout << temp->val << endl;
        temp = temp->next;
    }    


    while(head) {
        ListNode *del = head;
        head = head->next;
        delete del;
    }

    return 0;
}