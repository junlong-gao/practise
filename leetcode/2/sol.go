package leetcode2

type ListNode struct {
     Val int
     Next *ListNode
}

func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
    ret := ListNode{0, nil}
    walker := &ret
    carry := 0
    for l1 != nil || l2 != nil {
        var l1Next, l2Next int
        if l1 != nil {
            l1Next = l1.Val
            l1 = l1.Next
        }
        if l2 != nil {
            l2Next = l2.Val
            l2 = l2.Next
        }
        walker.Next = &ListNode{(l1Next + l2Next + carry) % 10, nil}
        carry = (l1Next + l2Next + carry)/10
        walker = walker.Next
    }
    if carry != 0 {
        walker.Next = &ListNode{(carry) % 10, nil}
    }
    return ret.Next
}

