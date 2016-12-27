#include <iostream>
#include <cstring>
#include <cmath>
#include <stack>
#include <queue>
using namespace std;

const int MAXN = 100005;

int dp[MAXN][26];
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

	for(int i = 0; i < 26; i++)
	{
		if(dp[n][i])
		cout << char('a' + i) << " " << dp[n][i] << endl;
	}
}

int main()
{
	cin >> K >> s;
	
	init();

	return 0;
}