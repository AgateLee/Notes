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

const int MAXN = 1000000005;
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;

// int dp[MAXN];

// void init()
// {
// 	dp[0] = 0;
// 	dp[1] = 1;
// 	int turn = 0, cur = 2, turn2 = 1;
	
// 	while(cur < MAXN)
// 	{
// 		dp[cur] = dp[cur - 1] + 1;
		
// 		turn ++;
// 		cur ++;

// 		if(turn == turn2)
// 		{
// 			dp[cur] = dp[cur - 1] - 1;
// 			cur ++;
// 			turn = 0;
// 			turn2 ++;
// 		}
// 	}
// }

int cal(int n)
{
	int k = sqrt(n<<1) - 1, s;
	
	while(1)
	{
		s = (k * (k + 1))>>1;

		cout << k << " " << s << endl;
		if(s + k + 1 <= n && s + (k<<1) + 3 >= n)
			break;
		else if(s + k + 1 > n)
			k --;
		else 
			k ++;
	}

	int p = n - 1 - s - k;
	if(p <= k + 1)
		return 1 + s - k + p;
	else
		return 1 + s - k + p - 2;
}

int main()
{
	int n;

	init();

	while(scanf("%d", &n) != EOF)
	{
		// printf("%d %d\n", dp[n], cal(n));
		printf("%d\n", cal(n));
	}

	return 0;
}