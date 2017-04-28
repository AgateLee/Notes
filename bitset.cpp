#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <unordered_map>
#include <algorithm>
#define LL long long
using namespace std;

const int MAXN = 30005;
const int INF = 0x3F3F3F3F;
const double eps = 1e-6;
const int MOD = 1e9 + 7;

int arr[MAXN][6];
int order[6][MAXN];
bitset<MAXN> mark[6][MAXN];

int main()
{
	std::ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
		freopen("1.txt", "r", stdin);
	#endif
 
	int n;
	scanf("%d", &n);
	memset(arr, 0, sizeof(arr));
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= 5; j++)
		{
			scanf("%d", &arr[i][j]);
			order[j][arr[i][j]] = i;
		}
	}	
	
	for(int i = 1; i <= 5; i++)
	{
		for(int j = 2; j <= n; j++)
		{
			bitset<MAXN> cur;
			cur[order[i][j - 1]] = 1;
			mark[i][j] = mark[i][j - 1] | cur;
		}
	}
	
	for(int i = 1; i <= n; i++)
	{
		bitset<MAXN> ans;
		ans = ~ans;
		for(int j = 1; j <= 5; j++)
		{
			ans &= mark[j][arr[i][j]];
		}
		
		printf("%ld\n", ans.count());
	}
	
	return 0;
}