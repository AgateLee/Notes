#include <iostream>
#include <thread>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>
#include <stack>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 505;
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;

int arr[MAXN];
int sum[MAXN];
int dp[MAXN][MAXN];

int main()
{
	int T, n;

	scanf("%d", &T);

	for(int i = 1; i <= T; i++)
	{
		scanf("%d", &n);
		memset(arr, 0, sizeof(arr));
		memset(sum, 0, sizeof(sum));
		memset(dp, 0 , sizeof(dp));

		for(int j = 1; j <= n; j++)
			scanf("%d", &arr[j]);

		for(int j = 1; j <= n; j++)
			sum[j] = sum[j - 1] + arr[j];

		for(int l = 0; l < n; l++)
		{
			for(int i = 1; i <= n - l; i++)
			{
				dp[i][i + l] = max(sum[i + l - 1] - sum[i - 1]
					 - dp[i][i + l - 1] + arr[i + l], 
					 sum[i + l] - sum[i] - dp[i + 1][i + l] + arr[i]);
			}
		}

		
		printf("Case #%d: %d %d\n", i, dp[1][n], sum[n] - dp[1][n]);
	}

	return 0;
}