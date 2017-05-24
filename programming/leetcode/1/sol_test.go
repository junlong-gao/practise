package leetcode1

import "testing"

func TestTwoSum(t *testing.T){
    cases := []struct {
		nums []int
        target int
        want []int
	}{
		{[]int{1, 2, 3}, 3, []int{0, 1}},
		{[]int{3, 2, 1}, 3, []int{1, 2}},
		{[]int{3, 2, 1}, 4, []int{0, 2}},
		{[]int{3, 2, 1}, 6, []int{-1, -1}},
    }

    for idx, c := range cases {
		t.Logf("start test %d", idx)
		got := twoSum(c.nums, c.target)
		if len(got) != len(c.want) {
			t.Errorf("size miss match")
		}
        for idx, val := range got {
			if val != c.want[idx] {
				t.Errorf("want %d, get %d at index %d", c.want[idx], val, idx)
			}
		}
		t.Logf("passed test %d!", idx)
	}
}


