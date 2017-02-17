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

const int MAXN = 1000010;

typedef struct Node{
    int val, lazy;

    Node(){val = lazy = 0;};
} Node;

Node tree[MAXN<<2];
int arr[MAXN];
int n, m, a, b, c, op;

int build(int pos, int l, int r)
{
    if(l == r)
        tree[pos].val = arr[l];
    else
    {
        int t = pos<<1;
        int mid = (l + r)>>1;
        int lv = build(t, l, mid);
        int rv = build(t + 1, mid + 1, r);
        tree[pos].val = lv + rv;
    }

    return tree[pos].val;
}

int range(int pos, int l, int r)
{
    if(l >= a && r <= b)
    {
        tree[pos].val = c * (r - l + 1);
        tree[pos].lazy = c;
    }
    else
    {
        int t = pos<<1;
        int mid = (l + r) >> 1;

        if(tree[pos].lazy)
        {
            tree[t].lazy = tree[pos].lazy;
            tree[t].val = tree[pos].lazy * (mid - l + 1);
            tree[t + 1].lazy = tree[pos].lazy;
            tree[t + 1].val = tree[pos].lazy * (r - mid);
            tree[pos].lazy = 0;
        }
    
        if(b <= mid)
            tree[pos].val = range(t, l, mid) + tree[t + 1].val;
        else if(a > mid)
            tree[pos].val = tree[t].val + range(t + 1, mid + 1, r);
        else
            tree[pos].val = range(t, l, mid) + range(t + 1, mid + 1, r);
    }

    return tree[pos].val;
}

int findSum(int pos, int l, int r)
{
    // cout << pos << " " << l << " " << r << endl;

    if(l >= a && r <= b)
        return tree[pos].val;
    
    int t = pos<<1;
    int mid = (l + r) >> 1;

    if(tree[pos].lazy)
    {
        tree[t].lazy = tree[pos].lazy;
        tree[t].val = tree[pos].lazy * (mid - l + 1);
        tree[t + 1].lazy = tree[pos].lazy;
        tree[t + 1].val = tree[pos].lazy * (r - mid);
        tree[pos].lazy = 0;
    }

    if(b <= mid)
        return findSum(t, l, mid);
    else if(a > mid)
        return findSum(t + 1, mid + 1, r);
    else
        return findSum(t, l, mid) + findSum(t + 1, mid + 1, r);
}

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &arr[i]);
    build(1, 1, n);

    scanf("%d", &m);
    for(int i = 1; i <= m; i ++)
    {
        scanf("%d %d %d", &op, &a, &b);

        if(op)
        {
            scanf("%d", &c);
            range(1, 1, n);
        }
        else
            printf("%d\n", findSum(1, 1, n));
    }

    return 0;
}
