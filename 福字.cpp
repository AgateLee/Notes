#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstring>
using namespace std;

int mat[1002][1002], dp[1002][1002];
int n;

int main()
{
	scanf("%d", &n);
	memset(mat, 0, sizeof(mat));
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			scanf("%d", &mat[i][j]);
		}
	}
	memset(dp, 0, sizeof(dp));
	for(int i = 0; i < n; i++)
		dp[i][n - 1] = dp[n - 1][i] = 1;
	int ans = 1;
	for(int i = n - 2; i >= 0; i --)
	{
		for(int j = n - 2; j >= 0; j--)
		{
			if(mat[i][j] + 1 == mat[i + 1][j]
				&& mat[i][j] + 1 == mat[i][j + 1]
				&& mat[i][j] + 2 == mat[i + 1][j + 1])
			{
				dp[i][j] = min(min(dp[i + 1][j], dp[i][j + 1]), 
					dp[i + 1][j + 1]) + 1;
				ans = max(ans, dp[i][j]);
			}
			else dp[i][j] = 1;
		}
	}

	// for(int i = 0; i < n; i++)
	// {
	// 	for(int j = 0; j < n; j++)
	// 		cout << dp[i][j] << " ";
	// 	cout << endl;
	// }

	printf("%d\n", ans);
	return 0;
}