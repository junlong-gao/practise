//
//  main.cpp
//  Merge k Sorted Lists
//
//  Created by John on 9/22/15.
//  Copyright © 2015 John. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

 struct ListNode {
     int val;
	 ListNode *next;
	 ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		ListNode* first = NULL;
		ListNode* base = NULL;
		bool flag = true;
		if(buildHeap(lists)) return NULL; //>=2 if 1 means originally no good lists
		while (1) {
			if (lists.size() == 1) {
				break;
			}			
			if (flag) {
				first = lists[1];
				base = first;
				flag = false;
			}else{
				first->next = lists[1];
				first = first->next;
			}
			lists[1] = lists[1]->next;
			if (lists[1] == NULL) {
				heapPop(lists);
				if (flag) {
					base = first;
					flag = false;
				}
			}else{
				heapify(lists, 1);
			}
		}
		
		return base;
	}
	
	void heapify(vector<ListNode*>& heap, int i){ //fix at index 1
		int l = 2, r = 3, largest = i;
		while (1) {
			l = 2*i; r = 2*i+1;
			if (l < heap.size() && heap[l]->val<heap[i]->val) {
				largest = l;
			}else largest = i;
			if (r < heap.size() && heap[r]->val<heap[largest]->val) {
				largest = r;
			}
			if (largest!=i) {
				ListNode* tmp = heap[i]; heap[i]=heap[largest];heap[largest]=tmp;
				i = largest;
				continue;
			}else{
				break;
			}
		}
	}
	
	bool buildHeap(vector<ListNode*>& heap){
		//clean up
		for(auto it =heap.begin(); it != heap.end(); it++){
			if (*it == NULL) {
				heap.erase(it);
				it--;
			}
			if (heap.size() == 0) {
				return true;
			}
		}
		heap.insert(heap.begin(), NULL);
		for (int i = (heap.size()-1)/2; i>=1; i--) {
			heapify(heap, i);
		}
		return false;
	}
	
	ListNode* heapPop(vector<ListNode*>& heap){ //at least size 1
		ListNode* max = heap[1];
		heap[1] = heap[heap.size()-1];
		heap.pop_back();
		heapify(heap, 1);
		return max;
		
	}
};

int main(int argc, const char * argv[]) {
	ListNode t0(0),t1(1),t2(2),t3(3),t4(4),t5(5),t6(6),t7(7),t8(8),t9(9),t10(10),t11(11),t12(12);
	/*
	t10.next = &t7; t7.next=  &t4; t4.next=&t1;
	t11.next = &t8; t8.next = &t5; t5.next=&t2;
	t12.next = &t9; t9.next = &t6; t6.next=&t3;
	 */
	//vector<ListNode*> lists = {&t10, &t11, &t12};
	vector<ListNode*> lists = {NULL,NULL};
	/*
	t0.next=&t2; t2.next=&t5;
	t1.next=&t3; t3.next=&t9;
	t4.next=&t7;	t7.next=&t11;
	vector<ListNode*> lists = {&t4,&t1,&t0};
	 */
	Solution mysolutions;
	mysolutions.mergeKLists(lists);
    return 0;
}
