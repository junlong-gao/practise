#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const long long M = 100000007;
const int maxN = 110002;
int n, m ;
long long f[maxN][20] ;
long long g[maxN * 5] ;
int main()
{
	int cs ;
	cin>>cs ;
	while (cs--)
	{
		cin >> n >> m;
		memset(f ,0, sizeof(f));
		memset(g, 0, sizeof(g));
		for (int i = n; i >= 1; --i)
			if (2*i<=n) f[i][0] = f[i+1][0] ;
			else f[i][0] = f[i+1][0] + 1;
		for (int k=1; (1<<k) <= n; ++k)
			for (int i = n; i >= 1; --i)
				if (2*i>n) f[i][k] = f[i+1][k];
				else f[i][k] = (f[i+1][k] + f[2*i][k-1]) % M;
		g[0] = 1;
		for (int len= 1;len<=m;len++)
		{
			int k = 0 ;
			while (1)
			{
				if ((1<<k)>n) break ;
				if (k>len) break ;
				g[len] = (g[len] + (g[len-1-k]*f[1][k]) % M) % M ;
				k++ ;
			}
		}
		cout<<g[m]<<endl ;
	}
}

