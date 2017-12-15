#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#define SIZE 50005
#define BT 1<<7
#define MOD 1000000007

using namespace std;

struct BIT
{
	int bit[SIZE];
	
	void init()
	{
		memset(bit,0,sizeof(bit));
	}
	void add(int k,int x)
	{
		while(k<SIZE)
		{
			bit[k]+=x;
			if(bit[k]>=MOD) bit[k]-=MOD;
			k+=k&-k;
		}
	}
	int sum(int k)
	{
		int ret=0;
		while(k>0)
		{
			ret+=bit[k];
			if(ret>=MOD) ret-=MOD;
			k-=k&-k;
		}
		return ret;
	}
};
BIT bit[BT];

int main()
{
	int n,k;
	scanf("%d %d",&n,&k);
	int ret=0;
	for(int i=0;i<1<<k;i++) bit[i].init();
	bit[0].add(1,1);
	for(int i=0;i<n;i++)
	{
		int h,c;
		scanf("%d %d",&h,&c);h++;c--;
		for(int S=(1<<k)-1;S>=0;S--)
		{
			int d=bit[S].sum(h-1);
			bit[S|1<<c].add(h,d);
		}
	}
	printf("%d\n",bit[(1<<k)-1].sum(SIZE-1));
	return 0;
}
