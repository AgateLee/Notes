#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int A, B, K;

int main()
{
    scanf("%d %d %d", &A, &B, &K);
    int r = K * min(A,B), l = 0, T;

    while(l <= r)
    {
        T = (r + l) / 2;
        
        int s = floor(T/A) + floor((T * 1.0 - 0.5) / B);
        // cout << l << " " << r << " " << T << " " << s << endl;
        if(l == r)
        {
            if(T*1.0/A == floor(T*1.0/A))
                printf("Takahashi\n");
            else
                printf("Aoki\n");

            break;
        }
        else if( s >= K)
        {
            r = T - 1;
        }
        else
        {
            l = T + 1;
        }
        // getchar();
    }

    return 0;
}