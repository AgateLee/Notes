#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

typedef struct TM{
    int hr, mn;
    
    TM(const int h, const int m): hr(h), mn(m){};
    bool operator < (TM a) const
    {
        return a.hr == hr ? a.mn > mn : a.hr > hr;
    }
} TM;

set<TM> ans;
set<TM>::iterator it;

void dfs(int len, int hr, int mn, int rest)
{
    if(hr > 23 || mn > 59 || rest < 0)
        return;

    if(len < 0)
    {
        if(rest == 0)
        {
            TM temp(hr, mn);
            ans.insert(temp);
        }
        return;
    }

    if(len >= 5)
    {
        dfs(len - 1, hr, mn + (1<<(10 - len)), rest - 1);
        dfs(len - 1, hr, mn, rest);
    }
    else
    {
        dfs(len - 1, hr + (1<<(4 - len)), mn, rest - 1);
        dfs(len - 1, hr, mn, rest);
    }
}

int main()
{
    int x;
    int hr, mn;

    scanf("%d", &x);
    ans.clear();
    dfs(10, 0, 0, x);
    for(it = ans.begin(); it != ans.end(); it++)
    {
        printf("%02d:%02d\n", (*it).hr, (*it).mn);
    }

    return 0;
}