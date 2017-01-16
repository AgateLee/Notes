#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

int main()
{
    char s[1002];
    int n, k;

    scanf("%d", &n);
    
    while(n --)
    {
        getchar();
        scanf("%s", s);
        scanf("%d", &k);

        int l = strlen(s), count = 0;
        int s1 = 0, s2 = l - k, d = s2 - s1;

        for(int i = 0; i < d; i++)
        {
            int c[4] = {0};
            for(int j = i; j < l; j += d)
            {
                switch(s[j])
                {
                    case 'A':
                        c[0] ++;
                    break;
                    case 'C':
                        c[1] ++;
                    break;
                    case 'T':
                        c[2] ++;
                    break;
                    case 'G':
                        c[3] ++;
                    break;
                }
            }

            int m = 0;
            for(int j = 0; j < 4; j++)
            {
                m = max(m, c[j]);
                count += c[j];
            }

            count -= m;
        }

        printf("%d\n", count);
    }

    return 0;
}