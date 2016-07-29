#include <iostream>
#include <cstring>
using namespace std;

char P[10002];
char T[1000002];
char pos[256];

int Sunday()
{
    int len = strlen(T), len0 = strlen(P), 
        i, j, sum, next;

    memset(pos, -1, sizeof(pos));

    for(i = len0 - 1; i >= 0; i--)
    {
        if(pos[P[i]] == -1)
            pos[P[i]] = i;
    }

    i = j = sum = 0;

    while(i < len)
    {
        if(T[i] == P[j])
        {
            i++;
            j++;

            if(j == len0)
            {
                i = i - len0 + 1;
                j = 0;
                sum += 1;
            }
        }
        else
        {
            next = i - j + len0;
            if(P[T[next]] != -1)
            {
                i = next - pos[T[next]];
            }
            else
            {
                i = next + 1;
            }

            j = 0;
        }
    }

    return sum;
}

int main()
{
    int N;
    scanf("%d", &N);

    while(N --)
    {
        scanf("%s %s", P, T);
        printf("%d\n", Sunday());
    }

    return 0;
}