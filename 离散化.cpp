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

int n, len, tl, tr, lz;
int arrs[MAXN], arrt[MAXN], tree[MAXN<<2];
unordered_map<int, int> des;
set<int> ans;

void mark(int pos, int l, int r)
{
    if(tl <= l && tr >= r)
    {
        tree[pos] = lz;
    }
    else
    {
        int t = pos<<1;
        int mid = (l + r)>>1;

        if(tree[pos])
        {
            tree[t] = tree[pos];
            tree[t + 1] = tree[pos];
            tree[pos] = 0;
        }

        if(tr <= mid)
            mark(t, l, mid);
        else if(tl > mid)
            mark(t + 1, mid + 1, r);
        else
        {
            mark(t, l, mid);
            mark(t + 1, mid + 1, r);
        }
    }
}

void cal(int pos, int cur, int h)
{
    // cout << pos << " " << tree[pos] << endl;
    if(cur <= h)
    {
        if(tree[pos]) 
            ans.insert(tree[pos]);
        else
        {
            int t = pos<<1;
            cal(t, cur + 1, h);
            cal(t + 1, cur + 1, h);
        }
    }
} 
    
int main()
{
    int i;

    scanf("%d %d", &n, &len);
    set<int> s;
    set<int>::iterator it;
    s.clear();
    ans.clear();
    for(i = 1; i <= n; i++)
    {
        scanf("%d %d", &arrs[i], &arrt[i]);
        s.insert(arrs[i]);
        s.insert(arrt[i]);
    }

    for(i = 1, it = s.begin(); it != s.end(); i ++, it ++)
    {
        des[* it] = i;
    }

    int all = s.size();
    memset(tree, 0, sizeof(tree));
    for(int i = 1; i <= n; i++)
    {
        tl = des[arrs[i]];
        tr = des[arrt[i]] - 1;
        lz = i;
        // cout << tl << " " << tr << " " << lz << endl;
        mark(1, 1, all);
    }

    int h = 0;
    while((1<<h) < all) h++;
    cal(1, 0, h);

    printf("%lu\n", ans.size());
    return 0;
}