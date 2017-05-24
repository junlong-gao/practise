def find_kth(a, b, k):
    if len(a) > len(b):
        a, b = b, a
        
    # 2 boundary conditions
    if len(a) == 0:
        return b[k]
    if k < 3:
        c = a[0:min([k+1, len(a)])] + b[0:min([k+1, len(b)])]
        return sorted(c)[k]
    
    # induction, find cutpoint
    # cutpoint: a[n - 1] and b[l - 1]
    n = (len(a) + 1) / 2
    if n >= k:
        assert(len(a) >= 4) # => n+1 < len(a)
        return find_kth(a[0:n + 1], b, k)
    l = min(k - n, len(b))
    
    # compare cutpoint a[n - 1] and b[l - 1] and make the binary choice
    if a[n - 1] <= b[l - 1]:
        return find_kth(a[n:], b, k - n)
    return find_kth(a, b[l:], k - l)
