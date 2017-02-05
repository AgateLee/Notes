#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

const double eps = 0.000001;

typedef struct node{
    int x, y;

    void operator = (const struct node & t)
    {
        x = t.x;
        y = t.y;
    };

    bool operator == (const struct node & t) const
    {
        return x == t.x && y == t.y;
    }

    node(){x = y = 0;};
    node(int x1, int y1):x(x1), y(y1){};
} node;

class vec
{
public:
    int x, y;
    node s, t;

    vec()
    {
        x = y = 0;
    }

    vec(int x1, int y1)
    {
        x = x1;
        y = y1;
        s = node(0, 0);
        t = node(x, y);
    }

    vec(node s1, node t1)
    {
        x = t1.x - s1.x;
        y = t1.y - s1.y;
        s = s1;
        t = t1;
    }

    ~vec(){};

    double length()
    {
        return (double)sqrt(pow(t.y - s.y, 2) + pow(t.x - s.x, 2));
    }

    bool vertical(vec & v)
    {
        return x * v.x + y * v.y == 0;
    }
};

int px1[4], px2[4], py1[4], py2[4];

bool check2(vec & l1, vec & l2, vec & l3, vec & l4)
{
    if(l1.vertical(l2) && l1.vertical(l4) && l3.vertical(l2))
    {
        if(l1.s == l2.s)
        {
            if(l2.t == l3.s)
            {
                if(l3.t == l4.s)
                {
                    return l4.t == l1.t;
                }
                else if(l3.t == l4.t)
                {
                    return l4.s == l1.t;
                }
            }
            else if(l2.t == l3.t)
            {
                if(l3.s == l4.s)
                {
                    return l4.t == l1.t;
                }
                else if(l3.s == l4.t)
                {
                    return l4.s == l1.t;
                }
            }
        }
        else if(l1.s == l2.t)
        {
            if(l2.s == l3.s)
            {
                if(l3.t == l4.s)
                {
                    return l4.t == l1.t;
                }
                else if(l3.t == l4.t)
                {
                    return l4.s == l1.t;
                }
            }
            else if(l2.s == l3.t)
            {
                if(l3.s == l4.s)
                {
                    return l4.t == l1.t;
                }
                else if(l3.s == l4.t)
                {
                    return l4.s == l1.t;
                }
            }
        }
        else if(l1.t == l2.s)
        {
            if(l2.t == l3.s)
            {
                if(l3.t == l4.s)
                {
                    return l4.t == l1.s;
                }
                else if(l3.t == l4.t)
                {
                    return l4.s == l1.s;
                }
            }
            else if(l2.t == l3.t)
            {
                if(l3.s == l4.s)
                {
                    return l4.t == l1.s;
                }
                else if(l3.s == l4.t)
                {
                    return l4.s == l1.s;
                }
            }
        }
        else if(l1.t == l2.t)
        {
            if(l2.s == l3.s)
            {
                if(l3.t == l4.s)
                {
                    return l4.t == l1.s;
                }
                else if(l3.t == l4.t)
                {
                    return l4.s == l1.s;
                }
            }
            else if(l2.s == l3.t)
            {
                if(l3.s == l4.s)
                {
                    return l4.t == l1.s;
                }
                else if(l3.s == l4.t)
                {
                    return l4.s == l1.s;
                }
            }
        }
    }

    return false;
}

bool check()
{
    vec l1(node(px1[0], py1[0]), node(px2[0], py2[0]));
    vec l2(node(px1[1], py1[1]), node(px2[1], py2[1]));
    vec l3(node(px1[2], py1[2]), node(px2[2], py2[2]));
    vec l4(node(px1[3], py1[3]), node(px2[3], py2[3]));

    if(check2(l1, l2, l3, l4)) return true;
    if(check2(l1, l2, l4, l3)) return true;
    if(check2(l1, l3, l2, l4)) return true;
    if(check2(l1, l3, l4, l2)) return true;
    if(check2(l1, l4, l2, l3)) return true;
    if(check2(l1, l4, l3, l2)) return true;

    return false;
}

int main()
{
    int n;
    scanf("%d", &n);

    while(n --)
    {
        for(int i = 0; i < 4; i++)
        {
            scanf("%d %d %d %d", &px1[i], &py1[i], &px2[i], &py2[i]);
        }

        if(check())
            printf("YES\n");
        else
            printf("NO\n");
    }
}