#include <iostream>
#include <cstring>
using namespace std;

char P[10002];
char T[1000002];
int NEXT[10002];

void CalNext()
{
    NEXT[0] = -1;
    int len = strlen(P),i = 0,j = -1;

    while(i < len)
    {
        if(j == -1 || P[i] == P[j])
        {
            NEXT[++ i] = ++j;
            // printf("%d:%d, ", i - 1, NEXT[i]);
        }
        else
            j = NEXT[j];
    }
    // NEXT[len] = 0;
    // printf("%d:%d, ", len - 1, NEXT[len]);
}

int find()
{
    int ans = 0, i = 0, j = 0, len0 = strlen(P), len = strlen(T);

    while(i < len)
    {
        if(j == -1 || T[i] == P[j])
        {
            i ++;
            j ++;
        }
        else
        {
            j = NEXT[j];
        }

        if(j == len0)
            ans ++;
    }

    return ans;
}

int main()
{
    int N;
    scanf("%d", &N);

    while(N --)
    {
        scanf("%s %s", P, T);
        CalNext();
        printf("%d\n", find());
    }

    return 0;
}