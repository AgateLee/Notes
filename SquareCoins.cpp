#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 2005;
const int INF = 0x3F3F3F3F;
const double eps = 1e-6;
const int MOD = 1e9 + 9;

int coin[600] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100,
				121, 144, 169, 196, 225, 256, 289};
int dp[MAXN];

void init()
{
	memset(dp, 0, sizeof(dp));
	
	dp[0] = 1;
	for(int i = 1; i <= 17; i++)
	{	
		for(int j = coin[i]; j < MAXN; j++)
		{
			if(dp[j - coin[i]])
			{
				dp[j] += dp[j - coin[i]];
				dp[j] %= MOD;
			}
		}
	}
}

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("1.txt", "r", stdin);
	#endif

	init();

	int n, t;
	cin >> t;
	
	while(t --)
	{
		cin >> n;
				
		cout << dp[n] << endl;
	}

	return 0;
}
