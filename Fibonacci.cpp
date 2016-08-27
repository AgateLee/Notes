#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int maxn = 26;
const int mod = 1000000007;
int dp[maxn], arr[11];
int f[maxn];

void init()
{
	f[0] = 0;
	f[1] = 1;
	f[2] = 1;
	for(int i = 3; i < maxn; i++)
	{
		f[i] = f[i - 1] + f[i - 2];
	}
	
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
}

int check(int n)
{
	for(int i = 2; i < maxn; i++)
	{
		if(n == f[i])
			return i;
	}
	
	return -1;
}

int main()
{
	init();
	
	int n, a, id;
	scanf("%d", &n);
	
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &a);
		id = check(a);
		
		if(id != -1)
		{
			dp[id] = (dp[id - 1] + dp[id]) % mod;
			if(a == 1)
				dp[1] = (dp[1] + dp[0]) % mod;
		}
	}
	
	int ans = 0;
	
	for(int i = 1; i < maxn; i ++)
		ans = (ans + dp[i]) % mod;
		
	printf("%d\n", ans);
	
	return 0;
}