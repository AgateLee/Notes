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

int fa[MAXN], p[MAXN];

int find(int x)
{
	if(fa[x] == 0 || fa[x] == x)
		return fa[x] = x;
	else
	{
		int root = find(fa[x]);
		p[x] += p[fa[x]];
		return fa[x] = root;
	}
}

void merge(int x, int y, int s)
{
	int fx = find(x);
	int fy = find(y);
	
	if(fx != fy)
	{
		p[fy] = p[x] + s - p[y];
		fa[fy] = fx;
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
		freopen("1.txt", "r", stdin);
	#endif
 
	int n, m, k, a, b, c;
	
	scanf("%d %d %d", &n, &m, &k);
	memset(fa, 0, sizeof(fa));
	memset(p, 0, sizeof(p));
	
	for(int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		merge(a, b, c);
	}
	
	for(int i = 0; i < k; i++)
	{
		scanf("%d %d", &a, &b);
		
		int f1 = find(a), f2 = find(b);
		
		if(f1 == f2) printf("%d\n", p[b] - p[a]);
		else printf("-1\n");
	}
	
	return 0;
}