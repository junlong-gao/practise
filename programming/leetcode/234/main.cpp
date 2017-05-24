#include <iostream>
#include <vector>

using namespace std;

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x = 0) : val(x), next(NULL) {}
 };
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast){
            fast = fast->next;
             slow = slow->next;
            if(fast==nullptr) break;
            fast = fast->next;
        }
        ListNode* pw = slow;
        if(pw!=nullptr){
            ListNode* w = slow->next;
            pw->next = nullptr;
            while(w){
                ListNode* t = w->next;
                w->next = pw;
                pw = w;
                w = t;
            }
        } 
        while(pw!=nullptr){
                if(pw->val!=head->val) return false;
                pw = pw->next;
                head = head->next;
        }
        
        return true;
    }
};

int main(){
    Solution s;
    ListNode a1, a2, a3, a4;
    a1.val = 1; a1.next = &a2;
    a2.val = 2; a2.next = &a3;
    a3.val = 2; a3.next = &a4;
    a4.val = 1; a4.next = nullptr;
    cout << (s.isPalindrome(&a1)? "YES":"NO") <<endl;
    return 0;
}
