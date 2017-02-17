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

int tree[MAXN<<2];
int arr[MAXN];
int n, m, a, b, op;

int build(int pos, int l, int r)
{
    if(l == r)
        tree[pos] = arr[l];
    else
    {
        int t = pos<<1;
        int mid = (l + r)>>1;
        int lv = build(t, l, mid);
        int rv = build(t + 1, mid + 1, r);
        tree[pos] = min(lv, rv);
    }

    return tree[pos];
}

int change(int pos, int l, int r)
{
    if(l == r)
        tree[pos] = b;
    else
    {
        int t = pos<<1;
        int mid = (l + r) >> 1;
        if(a <= mid)
            tree[pos] = min(change(t, l, mid), tree[t + 1]);
        else
            tree[pos] = min(change(t + 1, mid + 1, r), tree[t]);    
    }

    return tree[pos];
}

int find(int pos, int l, int r)
{
    // cout << pos << " " << l << " " << r << endl;

    if(l >= a && r <= b)
        return tree[pos];
    
    int t = pos<<1;
    int mid = (l + r) >> 1;

    if(b <= mid)
        return find(t, l, mid);
    else if(a > mid)
        return find(t + 1, mid + 1, r);
    else
    {
        int lv = find(t, l, mid);
        int rv = find(t + 1, mid + 1, r);
        return min(lv, rv);
    }
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
            change(1, 1, n);
        else
            printf("%d\n", find(1, 1, n));
    }

    return 0;
}
