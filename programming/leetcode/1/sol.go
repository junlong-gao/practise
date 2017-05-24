package leetcode1

func twoSum(nums []int, target int) []int {
    inv_map := make(map[int]int)
    for i := 0; i < len(nums); i++ {
        if val, ok := inv_map[target-nums[i]]; ok{
            return []int{val, i}
        }else{
            inv_map[nums[i]] = i
        }
    }
    return []int{-1, -1}
}

