#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;

const int MAXN = 100005;

struct Node{
	int val, add, set;

	Node(){val = add = 0; set = -1;};
} tree[MAXN<<2];

int n, m, op, x, y, z;
int arr[MAXN];

int build(int pos, int l, int r)
{
	if(l == r)
		tree[pos].val = arr[l];
	else
	{
		int t = (pos<<1) + 1;
		int mid = (l + r)>>1;

		tree[pos].val = build(t, l, mid) + build(t + 1, mid + 1, r);
	}

	return tree[pos].val;
}

void pass(int pos, int l, int r)
{
	if(r > l)
	{
		int t = (pos<<1) + 1;
		int mid = (l + r)>>1;

		if(tree[pos].set != -1)
		{
			tree[t].set = tree[t + 1].set = tree[pos].set;
			tree[t].add = tree[t + 1].add = 0;
			tree[t].val = (mid - l + 1) * tree[pos].set;
			tree[t + 1].val = (r - mid) * tree[pos].set;
			tree[pos].set = -1;
		}

		if(tree[pos].add)
		{
			tree[t].add += tree[pos].add;
			tree[t + 1].add += tree[pos].add;
			tree[t].val += (mid - l + 1) * tree[pos].add;
			tree[t + 1].val += (r - mid) * tree[pos].add;
			tree[pos].add = 0;
		}
	}
}

void setP(int pos, int l, int r)
{
	if(x <= l && y >= r)
	{
		tree[pos].set = z;
		tree[pos].add = 0;
		tree[pos].val = (r - l + 1) * z;
	}
	else
	{
		int t = (pos<<1) + 1;
		int mid = (l + r)>>1;

		pass(pos, l, r);

		if(y <= mid)
			setP(t, l, mid);
		else if(x > mid)
			setP(t + 1, mid + 1, r);
		else
		{
			setP(t, l, mid);
			setP(t + 1, mid + 1, r);
		}

		tree[pos].val = tree[t].val + tree[t + 1].val;
	}
}

void addP(int pos, int l, int r)
{
	if(x <= l && y >= r)
	{
		tree[pos].add += z;
		tree[pos].val += (r - l + 1) * z;
	}
	else
	{
		int t = (pos<<1) + 1;
		int mid = (l + r)>>1;

		pass(pos, l, r);

		if(y <= mid)
			addP(t, l, mid);
		else if(x > mid)
			addP(t + 1, mid + 1, r);
		else
		{
			addP(t, l, mid);
			addP(t + 1, mid + 1, r);
		}

		tree[pos].val = tree[t].val + tree[t + 1].val;
	}
}
    
int main()
{
    scanf("%d %d", &n, &m);

    for(int i = 0; i <= n; i++)
    	scanf("%d", &arr[i]);

    build(0, 0, n);

    for(int i = 0; i < m; i++)
    {
    	scanf("%d %d %d %d", &op, &x, &y, &z);

    	if(op)
    		setP(0, 0, n);
    	else
	    	addP(0, 0, n);

	    printf("%d\n", tree[0].val);
    }

    return 0;
}