#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
    void partition(ListNode* head, ListNode* end){
        if(head == nullptr || head==end) return;
        ListNode* walker = head->next;
        ListNode* sorted = head;
        int p = head->val;
        while(walker!=end){
            if(walker->val <p){
                sorted = sorted->next;
                int temp = walker->val;
                walker->val = sorted->val;
                sorted->val = temp;
            }
            walker = walker->next;
        }
        int temp = head->val;
        head->val = sorted->val;
        sorted->val = temp;
        partition(head, sorted);
        while(sorted!=end && sorted->next!=end && sorted->val==sorted->next->val){
            sorted = sorted->next;
        }
        partition(sorted->next, end);

    }
public:
    ListNode* sortList(ListNode* head) {
        ListNode* walker = head;
        while(walker!=nullptr){
            walker = walker->next;
        }
        partition(head, walker);
        return head;
    }
};

int main(){
    Solution s;
    ListNode s1(3), s2(2), s3(2);
    s1.next = &s2; s2.next = &s3;
    ListNode* rst =s.sortList(&s1);
    while(rst!=nullptr){
        cout << rst->val << " ";
        rst=rst->next;
    }
}
