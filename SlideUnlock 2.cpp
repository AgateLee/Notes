#include <iostream>
#include <cstring>
using namespace std;

int ban[10][10];
int line[10];
int total[10];
bool v[10];
int dp[10][1024][10][10];

void init()
{
    memset(ban, 0, sizeof(ban));

    ban[1][3] = ban[3][1] = 2;
    ban[4][6] = ban[6][4] = 5;
    ban[7][9] = ban[9][7] = 8;
    ban[1][7] = ban[7][1] = 4;
    ban[2][8] = ban[8][2] = 5;
    ban[3][9] = ban[9][3] = 6;
    ban[1][9] = ban[9][1] = 5;
    ban[3][7] = ban[7][3] = 5;
}

int dfs(int len, int state, int pre, int gp, int use, int dest, bool zero)
{
    if(len <= 0)
    {
        if(use == dest)
            return 1;
        else
            return 0;
    }

    if(!zero && dp[len][state][pre][gp] != -1)
        return dp[len][state][pre][gp];

    int sum = 0;
    for(int i = 0; i <= 9; i++)
    {
        if(v[i])
            continue;

        if(zero)
        {
            if(!i)
            {
                if(len > 4)
                    sum += dfs(len - 1, 0, 0, 0, 0, dest, true);
            }
            else
            {
                if(total[pre] == 2)
                    continue;

                v[i] = true;
                sum += dfs(len - 1, 1<<i, i, 0, 0, dest, false);
                v[i] = false;
            }
        }
        else if(i)
        {
            if(ban[pre][i] && v[ban[pre][i]] == false)
            {
                continue;
            }
            else if((total[pre] > 0 || total[i] == 2) && !((line[pre]>>i) & 1))
            {
                continue;
            }
            else
            {
                int flag = 0;

                if(total[i] == 1 && ((line[pre]>>i) & 1)) //与前项满足
                {
                    flag = 1;
                    total[i] = 0;
                }

                v[i] = true;
                sum += dfs(len - 1, (1<<i) + state, i, pre, use + ((line[pre]>>i) & 1), dest, false);
                v[i] = false;

                if(flag)
                    total[i] = 1;
            }
        }
    }

    if(!zero)
        dp[len][state][pre][gp] = sum;

    return sum;
}

int main()
{
    init();

    int T, N, a, b;

    scanf("%d", &T);
    
    while(T --)
    {
        scanf("%d", &N);
        memset(v, false, sizeof(v));
        memset(dp, -1, sizeof(dp));
        memset(line, 0, sizeof(line));
        memset(total, 0, sizeof(total));
        
        for(int i = 1; i <= N; i++)
        {
            scanf("%d %d", &a, &b);
            line[a] |= (1<<b);
            line[b] |= (1<<a);
            total[a] ++;
            total[b] ++;
        }

        printf("%d\n", dfs(9, 0, 0, 0, 0, N, true));
    }

    return 0;
}