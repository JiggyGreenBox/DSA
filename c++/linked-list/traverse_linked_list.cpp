#include <iostream>
#include <vector>
#include <memory> // smart pointer
using namespace std;

struct ListNode {
    int val;
    // ListNode *next;
    std::shared_ptr<ListNode> next;
    ListNode():val(0), next(nullptr){}
    ListNode(int data):val(data), next(nullptr){}
    // ListNode(int data, ListNode *next1):val(data), next(next1){}    
    ListNode(int data, std::shared_ptr<ListNode> next1):val(data), next(next1){} // ADD
    ~ListNode(){
        cout << "Node with data->" << this->val << " destroyed" << endl;
    }
};

int main() {

    // ListNode* y1 = new ListNode(2);
    // ListNode* y2 = new ListNode(5);
    // ListNode* y3 = new ListNode(8);
    // ListNode* y4 = new ListNode(7);

    std::shared_ptr<ListNode> y1 = std::make_shared<ListNode>(2);
    std::shared_ptr<ListNode> y2 = std::make_shared<ListNode>(5);
    std::shared_ptr<ListNode> y3 = std::make_shared<ListNode>(8);
    std::shared_ptr<ListNode> y4 = std::make_shared<ListNode>(7);

    y1->next = y2;
    y2->next = y3;
    y3->next = y4;

    // ListNode *temp = y1;
    std::shared_ptr<ListNode> temp = y1;
    while(temp != nullptr){
        cout << temp->val << endl;
        temp = temp->next;
    }

    // delete y1;
    // delete y2;
    // delete y3;
    // delete y4;

    return 0;
}