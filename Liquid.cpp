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

const int MAXN = 2005;
const int INF = 0x3F3F3F3F;
const double eps = 1e-6;
const int MOD = 1e9 + 7;

set<pair<int, int> > seg;

void doTask(int a, int b)
{
	if(!b) return;
	
	set<pair<int, int> >::iterator it1, it2;
	int st, ed;
	it1 = seg.upper_bound(make_pair(a, INF));
	it2 = it1;
	it1 --;
	
	int dis1 = a - it1->second, dis2;
	
	if(dis1 > 1)
	{
		st = a, ed = a + b - 1;
		
		dis2 = it2->first - ed;
		if(dis2 > 1)
		{
			seg.insert(make_pair(st, ed));
		}
		else 
		{
			ed = it2->first - 1;
			seg.insert(make_pair(st, it2->second));
			seg.erase(it2);
		}
	}
	else 
	{
		st = it1->second + 1, ed = st + b - 1;
		
		dis2 = it2->first - ed;
		if(dis2 > 1)
		{
			seg.insert(make_pair(it1->first, ed));
			seg.erase(it1);
		}
		else 
		{
			ed = it2->first - 1;
			seg.insert(make_pair(it1->first, it2->second));
			seg.erase(it1);
			seg.erase(it2);
		}
	}
	
	printf("%d %d\n", st, ed);
}

void doClean(int a)
{
	set<pair<int, int> >::iterator it1;
	
	it1 = seg.upper_bound(make_pair(a, INF));
	it1 --;
	
	int st = it1->first, ed = it1->second;

	if(st == ed)
	{
		if(st == a)
			seg.erase(it1);
	}
	else if(st == a)
	{
		seg.insert(make_pair(st + 1, ed));
		seg.erase(it1);
	}
	else if(ed == a)
	{
		seg.insert(make_pair(st, ed + 1));
		seg.erase(it1);
	}
	else if(st < a && ed > a)
	{
		seg.insert(make_pair(st, a - 1));
		seg.insert(make_pair(a + 1, ed));
		seg.erase(it1);
	}
}

void show()
{
	set<pair<int, int> >::iterator it1;
	
	for(it1 = seg.begin(); it1 != seg.end(); it1 ++)
	{
		cout << "(" << it1->first << "," << it1->second << ") ";
	}
	cout << endl;
}

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("1.txt", "r", stdin);
	#endif

	int n, a, b;

	while(scanf("%d", &n) != EOF)
	{
		seg.clear();
		seg.insert(make_pair(-INF,-INF));
		seg.insert(make_pair(INF, INF));
		
		for(int i = 0; i < n; i++)
		{
			scanf("%d", &a);
			if(a >= 0)
			{
				scanf("%d", &b);
				doTask(a, b);
			}
			else 
			{
				doClean(- a);
			}
//			show();
		}
	}

	return 0;
}
