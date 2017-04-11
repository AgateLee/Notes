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

const int MAXN = 100005;
const int INF = 0x3F3F3F3F;
const double eps = 1e-6;
const int MOD = 1e9 + 7;

int a[MAXN];
int c[MAXN];
int g[MAXN];

struct node{
	int key, val, fa, l, r;
} tree[MAXN];

int root = -1;
int sz = 0;

// 左旋
void rotate_to_left(int u, int v)
{
	int t = tree[u].fa;
	
	tree[u].r = tree[v].l;
	
	if(tree[v].l != -1)
		tree[tree[v].l].fa = u;
	
	tree[u].fa = v;
	tree[v].l = u;
	tree[v].fa = t;
	
	if(t != -1)
	{
		if(tree[t].l == u)
			tree[t].l = v;
		else 
			tree[t].r = v;
	}
}

//右旋
void rotate_to_right(int u, int v)
{
	int t = tree[u].fa;
	
	tree[u].l = tree[v].r;
	
	if(tree[v].r != -1)
		tree[tree[v].r].fa = u;
	
	tree[u].fa = v;
	tree[v].r = u;
	tree[v].fa = t;
	
	if(t != -1)
	{
		if(tree[t].l == u)
			tree[t].l = v;
		else 
			tree[t].r = v;
	}
}

void insert(int st, int key, int val)
{
	int p = st, pre = -1, dir = -1;
	bool flag = true;
	while(flag)
	{
		if(tree[p].key == -1)
		{
			tree[p].key = key;
			tree[p].val = val;
			tree[p].fa = pre;
			
			if(dir == 1)
				tree[pre].r = p;
			else if(dir == 0)
				tree[pre].l = p;
			
			while(tree[p].fa != -1 && tree[p].val <= tree[tree[p].fa].val)
			{
				if(p == tree[tree[p].fa].r)
					rotate_to_left(tree[p].fa, p);
				else 
					rotate_to_right(tree[p].fa, p);
			}
			
			if(tree[p].fa == -1)
				root = p;
			flag = false;
		}
		else if(tree[p].key > key)
		{
			pre = p;
			p = tree[p].l;
			if(p == -1)
				p = sz++;
				
			dir = 0;
		}
		else if(tree[p].key < key)
		{
			pre = p;
			p = tree[p].r;
			if(p == -1)
				p = sz++;
			dir = 1;
		}
	}
}

int find(int st, int l, int r, int base)
{
	int p = st;
		
	while(p != -1)
	{
		if(tree[p].key <= r && tree[p].key >= l)
		{
			if(tree[p].val > base)
				return base ? tree[p].val - 1 : 0;
			else 
			{
				int a = 0, b = 0;
				if(tree[p].l != -1) a = find(tree[p].l, l, tree[p].key - 1, base + 1);
				if(tree[p].r != -1) b = find(tree[p].r, tree[p].key + 1, r, base + 1);
				
				return max(max(a, b), tree[p].val + 1);
			}
		}
		else if(tree[p].key > r)
			p = tree[p].l;
		else
			p = tree[p].r;
	}

	return -1;
}

void out(int s){
	if(s == -1) return;  
	out(tree[s].l);  
	printf("%d ", tree[s].key);  
	out(tree[s].r);  
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
		
		for(int i = 0; i < n; i++)
		{
			scanf("%d", &a[i]);
		}
		
		for(int i = 0; i < n; i++)
		{
			scanf("%d", &c[i]);
		}
		
		memset(g, -1, sizeof(g));
		memset(tree, -1, sizeof(tree));
		g[0] = 0;
		root = 0;
		sz = 1;
		insert(root, 0, 0);
		
		for(int i = 1; i < n; i++)
		{			
			g[i] = find(root, i - c[i], i - 1, 0);
			insert(root, i, g[i]);
		}
	
		for(int i = 0; i < n; i++)
			printf("%d ", g[i]);
		printf("\n");
		
		int ans = g[0];
		for(int i = 1; i < n; i++)
		{
			if(a[i]%2)
				ans ^= g[i];
		}
		
		ans ^= g[0];
		
		if(ans)
			printf("Win\n");
		else 
			printf("Lose\n");
	}
	return 0;
}