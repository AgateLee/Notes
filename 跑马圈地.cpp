#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int n, m, L;
int l, r, t, b;

int check(int pl, int pr, int pt, int pb) {
    if(pr <= l || pl >= r || pt >= b || pb <= t)
      return (pr - pl) * (pb - pt);

    int inside = 0, sign = 0;
    if(l < pr && l > pl && t > pt && t < pb)
        inside ++, sign = 1;
    if(l < pr && l > pl && b > pt && b < pb)
        inside ++, sign = 2;
    if(r < pr && r > pl && t > pt && t < pb)
        inside ++, sign = 3;
    if(r < pr && r > pl && b > pt && b < pb)
        inside ++, sign = 4;

    if(inside == 1)
    {
      switch(sign)
      {
          case 1: 
          return (pr - pl) * (pb - pt) - (pr - l) * (pb - t);
          case 2:
          return (pr - pl) * (pb - pt) - (pr - l) * (b - pt);
          case 3:
          return (pr - pl) * (pb - pt) - (r - pl) * (pb - t);
          case 4:
          return (pr - pl) * (pb - pt) - (r - pl) * (b - pt);
          default:
          return 0;
      }
    }
    else if(inside == 4)
      return (pr - pl) * (pb - pt) - (r - l) * (b - t);
    else
      return 0;
}

int main()
{
    int w, h;
    int ans = 0;

    scanf("%d %d %d", &n, &m, &L);
    scanf("%d %d %d %d", &l, &r, &t, &b);

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            w = 1;
            h = (L - (w<<1))>>1;

            while(h > 0)
            {
                ans = max(ans, check(i, min(m, i + w), j, min(n, j + h)));
                w ++;
                h = (L - (w<<1))>>1;
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}