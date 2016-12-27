#include <iostream>
#include <cstring>
#include <cmath>
#include <stack>
#include <queue>
using namespace std;

const int MAXN = 100005;

int dp[MAXN][26]; // dp[pos][target] 第pos位前target的数量（不含pos）
string s;
int n, K, ans, d;

void init()
{
	n = s.length();

	memset(dp[0], 0, sizeof(dp[0]));

	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j < 26; j++)
		{
			dp[i][j] = dp[i - 1][j];
		}
		dp[i][s[i - 1] - 'a'] ++;
	}

	// for(int i = 0; i < 26; i++)
	// {
	// 	if(dp[n][i])
	// 	cout << char('a' + i) << " " << dp[n][i] << endl;
	// }
}

int find(int target, int st, int ed) // find in [l, r)
{
	int l = st, r = ed, mid;

	while(l <= r)
	{
		mid = (l + r) >> 1;

		// cout << l << " " << r << " " << mid << " " << dp[mid][target] << " " << dp[l][target] << endl;

		if(dp[mid][target] == dp[l][target]) // [l, mid)
		{
			if(dp[mid + 1][target] - dp[mid][target] == 1)
				return mid;

			l = mid + 1;
		}
		else 
		{
			r = mid - 1;
		}
	}

	return -1;
}

int main()
{
	cin >> K >> s;
	
	init();
	int st = 0, ed;

	for(int i = 0; i < K;)
	{
		ed = n - K + i;
		for(int j = 0; j < 26; j++)
		{
			int pos = find(j, st, ed);
			// cout << "try " << (char)('a' + j) << " " << pos << " " << st << " " << ed << endl;
			if(pos != -1)
			{
				st = pos + 1;
				i ++;
				printf("%c", s[pos]);

				break;
			}
		}
	}

	printf("\n");

	return 0;
}