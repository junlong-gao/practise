isPrime=[1 for i in range(300006)]
isPrime[0]=isPrime[1]=0
isPrime[2]=1
primes=[0,0]
for i in range(2,300006):
    if isPrime[i]:
        primes.append(primes[-1]+1)
        for j in range(i*i,300006,i):
            isPrime[j]=0
    else:primes.append(primes[-1])
ans=[1,1,1,1]
ans.append(2)
for i in range(5,41):
    ans.append(ans[i-1]+ans[i-4])
t=input()
for i in range(t):
    print primes[ans[input()]]
