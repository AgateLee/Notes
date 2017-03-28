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

const int MAXN = 55;
const int INF = 0x3F3F3F3F;
const double eps = 1e-6;

int a[MAXN];
int dp[MAXN][102410];

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("1.txt", "r", stdin);
	#endif

	int n;
	int sum = 0;

	while(cin >> n)
	{
		for(int i = 1; i <= n; i++)
		{
			cin >> a[i];
			a[i] /= 1024;
			sum += a[i];
		}

		int target = (sum>>1) + 1;
		memset(dp, 0, sizeof(dp));

		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= target; j++)
			{
				dp[i][j] = dp[i - 1][j];

				if(j >= a[i])
					dp[i][j] = max(dp[i][j], dp[i - 1][j - a[i]] + a[i]);
			}
		}

		int ans = 0;
		for(int i = target - 1; i >= 0; i--)
		{
			if(dp[n][i] > 0)
			{
				ans = dp[n][i];
				break;
			}
		}

		ans = max(ans, sum - ans);
		cout << ans * 1024 << endl;
	}

	return 0;
}
