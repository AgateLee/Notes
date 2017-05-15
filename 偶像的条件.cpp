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
#include <iomanip>
#define LL long long
using namespace std;

const int MAXN = 100005;
const int INF = 0x3F3F3F3F;
const double eps = 1e-6;
const int MOD = 1e9 + 7;

int A[MAXN], B[MAXN], C[MAXN];

int cal(int a, int b, int c)
{
	return abs(a - b) + abs(b - c) + abs(c - a);
}

int main()
{
	std::ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
		freopen("1.txt", "r", stdin);
	#endif
 
	int n, m, k;
	
	scanf("%d %d %d", &n, &m, &k);
	
	for(int i = 0; i < n; i++)
		scanf("%d", &A[i]);
	for(int i = 0; i < m; i++)
		scanf("%d", &B[i]);
	for(int i = 0; i < k; i++)
		scanf("%d", &C[i]);
	
	sort(A, A + n);
	sort(B, B + m);
	sort(C, C + k);
	
	int ans = INF;
	for(int i = 0; i < n; i++)
	{
		int pb = lower_bound(B, B + m, A[i]) - B;
		int pc = lower_bound(C, C + k, A[i]) - C;
		
		if(pb >= 0 && pb < m && pc >= 0 && pc < k)
			ans = min(ans, cal(A[i], B[pb], C[pc]));
		if(pb >= 0 && pb < m && pc >= 1 && pc < k)
			ans = min(ans, cal(A[i], B[pb], C[pc - 1]));
		if(pb >= 1 && pb < m && pc >= 0 && pc < k)
			ans = min(ans, cal(A[i], B[pb - 1], C[pc]));
		if(pb >= 1 && pb < m && pc >= 1 && pc < k)
			ans = min(ans, cal(A[i], B[pb - 1], C[pc - 1]));
	}
	
	printf("%d\n", ans);
	
	return 0;
}