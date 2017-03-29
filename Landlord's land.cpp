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
#define LL long long
using namespace std;

const int MAXN = 25;
const int INF = 0x3F3F3F3F;
const double eps = 1e-6;
const int MOD = 1e9 + 7;

char land[MAXN][MAXN];
int sum[MAXN][MAXN];

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("1.txt", "r", stdin);
	#endif

	int t, n, m, k, xx, xy;
	scanf("%d", &t);
	for(int t0 = 1; t0 <= t; t0++)
	{
		scanf("%d %d %d", &n, &m, &k);
		getchar();
		for(int i = 1; i <= n; i++)
		{
			scanf("%s", land[i] + 1);
		}
		
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				if(land[i][j] == 'x')
					xx = i, xy = j;
			}
		}
		
		memset(sum, 0, sizeof(sum));
		
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				sum[i][j] = sum[i][j - 1];
				if(land[i][j] == 'x' || land[i][j] == 'y')
					sum[i][j] ++;
			}
		}
		
		for(int j = 1; j <= m; j++)
		{
			for(int i = 1; i <= n; i++)
			{
				sum[i][j] += sum[i - 1][j];
			}
		}
		
//		for(int i = 1; i <= n; i++)
//		{
//			for(int j = 1; j <= m; j++)
//			{
//				printf("%d ", sum[i][j]);
//			}
//			printf("\n");
//		}
//		printf("\n");
		
		int ans = 0;
		for(int i = 0; i < xx; i++)
		{
			for(int j = 0; j < xy; j++)
			{
				for(int i2 = xx; i2 <= n; i2++)
				{
					for(int j2 = xy; j2 <= m; j2++)
					{
						if(sum[i2][j2] + sum[i][j] - sum[i2][j] - sum[i][j2] == 1)
						{
							ans = max(ans, (i2 - i) * (j2 - j));
						}
					}
				}	
			}
		}
		
		printf("Case #%d: %d\n", t0, ans);
	}

	return 0;
}
