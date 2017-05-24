Two ideas:
1. use left and right to reuse the partial sum in row wise
2. store the partial sum in ordered fastion to find the best val that just above cur_sum - k
    since we need best prev such that cur - prev <= k, ie, the smallest prev in solution prev >= cur - k