#include <iostream>
#include <cstring>
using namespace std;

int ban[10][10];
bool v[10];
int dp[10][1024][10];

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

int dfs(int len, int state, int pre, bool zero)
{
    if(len <= 0)
    {
        return 1;
    }

    if(!zero && dp[len][state][pre] != -1)
        return dp[len][state][pre];

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
                    sum += dfs(len - 1, 0, 0, true);
            }
            else
            {
                v[i] = true;
                sum += dfs(len - 1, 1<<i, i, false);
                v[i] = false;
            }
        }
        else if(i)
        {
            if(ban[pre][i] && v[ban[pre][i]] == false)
            {
                continue;
            }
            else
            {
                v[i] = true;
                sum += dfs(len - 1, (1<<i) + state, i, false);
                v[i] = false;
            }
        }
    }

    if(!zero)
        dp[len][state][pre] = sum;

    return sum;
}

int main()
{
    init();

    memset(v, false, sizeof(v));
    memset(dp, -1, sizeof(dp));
    printf("%d\n", dfs(9, 0, 0, true));

    return 0;
}