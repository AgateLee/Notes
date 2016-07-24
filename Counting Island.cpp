#include <iostream>
#include <cstring>
#include <sstream>
#include <algorithm>
using namespace std;

typedef struct node{
    int x, y;
    int px, py;
} node, * pnode;

node land[1005][1005];
int total;

void show()
{
    for(int i = 0; i < 1000; i++)
        for(int j = 0; j < 1000; j++)
            if(land[i][j].x != -1)
                printf("%d(%d) %d(%d) -> %d %d\n",land[i][j].x,i, land[i][j].y,j, land[i][j].px, land[i][j].py);
}

void check(int x, int y, int a0, int b0)
{
    int a = a0, b = b0;

    while(land[a][b].x != land[a][b].px || land[a][b].y != land[a][b].py)
    {
        a0 = land[a][b].px;
        b0 = land[a][b].py;
        a = a0;
        b = b0;
    }
    
    if(land[a][b].px != x || land[a][b].py != y)
    {
        land[a][b].px = x;
        land[a][b].py = y;
        total --;
    }
}

int main()
{
    int n, x, y, a, b;
    memset(land, -1, sizeof(land));
    total = 0;

    scanf("%d", &n);
    while(n --)
    {
        scanf("%d %d", &x, &y);

        if(land[x][y].x == -1)
        {
            land[x][y].x = land[x][y].px = x;
            land[x][y].y = land[x][y].py = y;
            total ++;
        }

        if(y > 0 && land[x][y - 1].x != -1)
            check(x, y, x, y - 1);

        if(y < 1000 && land[x][y + 1].x != -1)
            check(x, y, x, y + 1);

        if(x > 0 && land[x - 1][y].x != -1)
            check(x, y, x - 1, y);

        if(x < 1000 && land[x + 1][y].x != -1)
            check(x, y, x + 1, y);
    
        printf("%d\n", total);
    }

    return 0;
}
