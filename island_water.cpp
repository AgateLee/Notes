#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

const int INF = 1 << 30;

int R, C;
int land[50][50];
bool v[50][50];
int area = 0;
set<int> low;

void init()
{
    low.clear();
    for(int i = 0; i < R; i++)
    {
        for(int j = 0; j < C; j++)
        {
            scanf("%d",&land[i][j]);
            low.insert(land[i][j]);
        }
    }
}

int check(int r, int c, int val)
{
    int temp = 0;

    if(r < 0 || r > R - 1 || c < 0 || c > C - 1)
    {
        return 0;
    }
    else if(r == 0 || r == R -1 || c == 0 || c == C - 1)
    {
        if(land[r][c] < area)
            area = land[r][c];
        return 0;
    }

    if(v[r][c])
    {
        return 0;
    }
    else
    {
        if(land[r][c] == val)
        {
            v[r][c] = true;
            temp = 1;

            temp += check(r - 1, c, val);
            temp += check(r + 1, c, val);
            temp += check(r, c + 1, val);
            temp += check(r, c - 1, val);

            return temp;
        }

        if(land[r][c] < area)
            area = land[r][c];

        return 0;
    }
}

int calc()
{
    int total = 0, temp;
    set<int>::iterator it;
    for(it = low.begin(); it != low.end(); it++)
    {
        for(int r = 0; r < R ;r ++)
            for(int c = 0; c < C; c ++)
            {
                if(land[r][c] != * it)
                    continue;

                // cout << r << "," << c << endl;
                memset(v, false, sizeof(v));
                area = INF;
                while((temp = check(r, c, * it)) > 0)
                {
                    // cout <<"!!" <<  temp << " " << area << endl;
                    if(area < * it)
                        break;
                    else
                    {
                        int add = area - * it;
                        for(int i = 0; i < R; i++)
                        {
                            for(int j = 0; j < C; j++)
                            {
                                if(v[i][j])
                                {
                                    land[i][j] += add;
                                    total += add;
                                }
                            }
                        }
                    }

                    area = INF;
                }
            }
    }

    return total;
}

int main()
{
    int T, t = 1;

    scanf("%d", &T);
    while(t <= T)
    {
        scanf("%d %d", &R, &C);
        init();
        cout << "Case #" << t << ": " << calc() << endl;
        t ++;
    }

    return 0;
}