#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
	ListNode* swapPairs(ListNode* head){
		if(head == NULL){
			return NULL;
		} else if (head->next == NULL){
			return head;
		} else {
			ListNode* first = head;
			ListNode* second = head->next;
			ListNode* tail = swapPairs(head->next->next);
			first->next = tail;
			second->next = first;
			head = second;
			return head;
		}
	}
};

int main(){
	ListNode n1(1);
	ListNode n2(2);
	ListNode n3(3);
	ListNode n4(4);
	ListNode n5(5);
	n1.next = &n2;
	n2.next = &n3;
	n3.next = &n4;
	n4.next = &n5;
	Solution mysolutions;


	ListNode* walker = mysolutions.swapPairs(&n1);
	while(walker!=NULL){
		cout<<walker->val<<" ";
		walker = walker->next;
	}
	return 0;
}