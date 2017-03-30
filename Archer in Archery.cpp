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
#include <algorithm>
#define LL long long
using namespace std;

const int MAXN = 10005;
const int INF = 0x3F3F3F3F;
const double eps = 1e-6;
const int MOD = 1e9 + 7;

struct node{
	int h, sp;
	int t;
	
	bool operator < (const node & a) const
	{
		return t < a.t;
	}
} b[MAXN];

bool check(int h, int n)
{
	for(int i = 0; i < n; i++)
	{
		b[i].t = (h - b[i].h)/b[i].sp;
	}
	
	sort(b, b + n);
	
	for(int i = 0; i < n; i++)
	{
		if(b[i].t < i)
			return false;
	}
	
	return true;
}

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("1.txt", "r", stdin);
	#endif
	
	int t, n;
	scanf("%d", &t);
	while(t --)
	{
		scanf("%d", &n);
		
		int dh = 0, ds = 0;
		for(int i = 0; i < n; i++)
		{
			scanf("%d", &b[i].h);
			dh = max(dh, b[i].h);
		}
		
		for(int i = 0; i < n; i++)
		{
			scanf("%d", &b[i].sp);
			ds = max(ds, b[i].sp);
		}
		
		int l = dh, r = dh + ds * (n - 1);
		int ans = 0;
		while(l <= r)
		{
//			cout << l << " " << r << endl;
			int m = (l + r)>>1;
			
			if(check(m, n))
			{
				ans = m;
				r = m - 1;
			}
			else 
			{
				l = m + 1;
			}
		}
		
		printf("%d\n", ans);
	}
	return 0;
}
