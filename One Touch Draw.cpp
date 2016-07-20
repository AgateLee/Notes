#include <iostream>
#include <vector>
using namespace std;

vector<int> path[102], s;
int mark[102][102];
int jump[102];
int N, M, J;

int dfs(int cur, int rest)
{
    int temp = -1;
    s.push_back(cur);

    if(rest == 0)
    {
        return 0;
    }

    if(jump[cur])
    {
        cur = jump[cur];
        s.push_back(cur);
    }

    for(int i = 0; i < path[cur].size(); i++)
    {
        switch(mark[cur][path[cur][i]])
        {
            case 1:
                mark[cur][path[cur][i]] = 11;
                mark[path[cur][i]][cur] = 11;
                temp = dfs(path[cur][i], rest - 1);
                mark[cur][path[cur][i]] = 1;
                mark[path[cur][i]][cur] = 1;
                break;
            case 2:
                mark[cur][path[cur][i]] = 21;
                mark[path[cur][i]][cur] = 21;
                temp = dfs(path[cur][i], rest - 1);
                mark[cur][path[cur][i]] = 2;
                mark[path[cur][i]][cur] = 2;
                break;
            case 21:
                mark[cur][path[cur][i]] = 22;
                mark[path[cur][i]][cur] = 22;
                temp = dfs(path[cur][i], rest - 1);
                mark[cur][path[cur][i]] = 21;
                mark[path[cur][i]][cur] = 21;
                break;
            case 3:
                mark[cur][path[cur][i]] = 31;
                temp = dfs(path[cur][i], rest - 1);
                mark[cur][path[cur][i]] = 3;
                break;
            case 4:
                mark[cur][path[cur][i]] = 41;
                temp = dfs(path[cur][i], rest - 1);
                mark[cur][path[cur][i]] = 4;
                break;
            case 41:
                mark[cur][path[cur][i]] = 42;
                temp = dfs(path[cur][i], rest - 1);
                mark[cur][path[cur][i]] = 41;
                break;
            case 11:
            case 22:
            case 31:
            case 42:
                continue;
                break;
            default:
                break;
        }

        if(temp == 0)
            return 0;
    }

    if(jump[cur])
    {
        s.pop_back();
    }

    s.pop_back();
    return -1;
}

int main()
{
    int x, y, c, count = 0;
    scanf("%d %d", &N, &M);
    memset(mark, 0, sizeof(mark));
    memset(jump, 0, sizeof(jump));

    for(int i = 1; i <= M; i++)
    {
        scanf("%d %d %d", &x, &y, &c);

        if(c == 0)
        {
            path[x].push_back(y);
            path[y].push_back(x);
            mark[x][y] = mark[y][x] = 1;
            count ++;
        }
        else if(c == 1)
        {
            path[x].push_back(y);
            path[y].push_back(x);
            mark[x][y] = mark[y][x] = 2;
            count += 2;
        }
        else if(c == 2)
        {
            path[x].push_back(y);
            mark[x][y] = 3;
            count ++;
        }
        else if(c == 3)
        {
            path[x].push_back(y);
            mark[x][y] = 4;
            count += 2;
        }
    }

    scanf("%d", &J);
    if(J == 2)
    {
        scanf("%d %d", &x, &y);
        jump[x] = y;
        jump[y] = x;
    }

    for(int i = 1; i <= N; i++)
    {
        s.clear();
        if(!dfs(i, count))
            break;
    }

    if(s.size() == 0)
        printf("-1\n");

    for(int i = 0; i < s.size(); i++)
        printf("%d ", s[i]);
    printf("\n");

    return 0;
}