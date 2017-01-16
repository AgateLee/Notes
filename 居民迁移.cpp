#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

typedef struct seg{
    int l, r, n;

    bool operator < (const struct seg & t) const
    {
        return l == t.l ? r < t.r : l < t.l;
    }
} seg;

seg s[100002];
int city[100002];
int n, m, R;

bool check(int tar)
{
    int pos = 0, ava = tar, cur = s[0].n, i;

    for(i = 0; i < m && pos < m;)
    {
        if(city[pos] > s[i].r)
            return false;

        if(city[pos] >= s[i].l)
        {
            if(ava >= cur)
            {
                ava -= cur;
                i ++;
                cur = s[i].n;
            }
            else
            {
                cur -= ava;
                pos ++;
                ava = tar;
            }
        }
        else
        {
            pos ++;
            ava = tar;
        }
    }

    if(i == m)
        return true;
    else
        return false;
}

int main()
{
    int st, mid, ed = 0, ans;

    scanf("%d", &n);
    while(n --)
    {
        scanf("%d %d", &m, &R);
        memset(city, 0, sizeof(city));
        memset(s, 0, sizeof(s));

        for(int i = 0; i < m; i++)
        {
            scanf("%d %d", &city[i], &s[i].n);
            s[i].l = city[i] - R;
            s[i].r = city[i] + R;
            ed = max(ed, s[i].n);
        }

        sort(s, s + m);
        sort(city, city + m);

        st = 0;
        ans = ed;
        while(st <= ed)
        {
            mid = (st + ed) >> 1;
            if(check(mid))
            {
                ed = mid - 1;
                ans = mid;
            }
            else
            {
                st = mid + 1;
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}