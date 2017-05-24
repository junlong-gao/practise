func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func findLHS(nums []int) int {
    n := len(nums)
    if n == 0 || n == 1 {return 0}
    
    f:=make(map[int]int) //best len end at i so far as high
    g:=make(map[int]int) //best len end at i so far as low
    best := 0
    f[nums[0]] = 1
    g[nums[0]] = 1
    
    for i:=1; i < n; i++{
        //update f:
        old_f := 0
        if v, ok := f[nums[i]]; ok{
            old_f = v
        }
        t:=0
        if v, ok := g[nums[i] - 1]; ok{
            t = v
        }
        new_f := max(old_f + 1, t + 1)
        if t > 0 {
            best = max(new_f, best)
        }
        
        //update g:
        old_g := 0
        if v, ok := g[nums[i]]; ok{
            old_g = v
        }
        t = 0
        if v, ok := f[nums[i] + 1]; ok{
            t = v
        }
        new_g := max(old_g + 1, t + 1)
        if t > 0 {
            best = max(new_g, best)
        }

        f[nums[i]] = max(old_f, new_f)
        g[nums[i]] = max(old_g, new_g)
    }
    return best
    
}