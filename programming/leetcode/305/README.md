1. Use union find is the way to go, yet need a counter to maintain
2. When doing union, counter is decresed only when union something not in the 
same set
3. When doing find, use half compression instead of full compression to reduce stack 
trace: p[n] = p[p[n]], n = p[n], they are fast.
4. Union by rank is a good heristic, and pratically fast.
