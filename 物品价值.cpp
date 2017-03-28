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

const int MAXN = 1005;
const int INF = 0x3F3F3F3F;
const double eps = 1e-6;

typedef struct node{
	int val;
	int sign;
} node;

node a[MAXN];
int dp[2][1024];

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("1.txt", "r", stdin);
	#endif

	int n, t, m;
	cin >> t;
	while(t --)
	{
		cin >> n >> m;
		int sum = 0, as, each;
		memset(a, 0, sizeof(a));
		memset(dp, -1, sizeof(dp));
		
		int up = 0;
		up = (1<<m) - 1;

		for(int i = 1; i <= n; i++)
		{
			cin >> a[i].val >> as;
			
			while(as --)
			{
				cin >> each;
				a[i].sign |= (1<<(each - 1));
			}
		}
		
		int p = 1, ans = -1;
		dp[0][0] = 0;
		dp[1][0] = 0;
		for(int i = 1; i <= n; i++)
		{			
			for(int j = up; j >= 0; j--)
			{
				int pre = j^a[i].sign;
				dp[p][j] = dp[1 - p][j];
				if(dp[1 - p][pre] != -1)
					dp[p][j] = max(dp[p][j], dp[1 - p][pre] + a[i].val);
			}
			
			p = 1 - p;
		}
		p = 1 - p;
		
//		for(int i = up; i >= 0; i --)
//		{
//			ans = max(ans, dp[p][i]);
//		}
		
		ans = dp[p][up];
		
		cout << ans << endl;
	}

	return 0;
}
