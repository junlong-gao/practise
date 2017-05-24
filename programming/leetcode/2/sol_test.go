package leetcode2

import "testing"

func TestLeetcode2(t *testing.T){
	cases := []struct {
		l1 *ListNode
		l2 *ListNode
		want *ListNode
	}{
		{
			&ListNode{1, &ListNode{2, nil} } ,
			&ListNode{2, &ListNode{1, nil} } ,
			&ListNode{3, &ListNode{3, nil} } ,
		},
		{
			&ListNode{9, nil } ,
			&ListNode{1, nil } ,
			&ListNode{0, &ListNode{1, nil} } ,
		},
	}

	for idx, c := range cases {
		t.Logf("start test %d!", idx)
		got := addTwoNumbers(c.l1, c.l2)
		for got != nil {
			if got.Val != c.want.Val {
				t.Errorf("failed at case %d", idx)
			}
			got = got.Next
			c.want = c.want.Next
		}
		t.Logf("passed test %d!", idx)
	}
}
