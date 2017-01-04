#include <cstdio>
#include <fstream>
#include <cstring>
#include <iostream>
#include <stack>
#include <ctime>
using namespace std;

int gcd(int a, int b)
{
    return a == 0 ? b : gcd(b % a, a);
}

int main(int argc, char ** args)
{
    int ca, n, m, t, count, n0;
    bool flag = true;
    srand(time(0));
    scanf("%d", &ca);
    
    while(ca --)
    {
        scanf("%d", &n);
        n0 = n;
        flag = true;
        while(flag)
        {
            stack<bool> ans;
            count = 0;
            n = n0;

            do
            {
                m = rand() % n + 1;
            }
            while(gcd(m, n) != 1);
            // cout << "try " << n << " " << m << endl;

            do
            {
                if(n > m)
                {
                    n -= m;
                    // cout << count << " " << 0 << " : " << n << " " << m << endl;
                    ans.push(0);
                }
                else
                {
                    m -= n;
                    // cout << count << " " << 1 << " : " << n << " " << m << endl;
                    ans.push(1);
                }
                count ++;
            }
            while(m != 0 && n != 0 && count < 60);

            if(n == 0)
            {
                while(!ans.empty())
                {
                    printf("%d",ans.top());
                    ans.pop();
                }
                flag = false;
                printf("\n");
            }
            else if(m == 0)
            {
                while(!ans.empty())
                {
                    printf("%d",!ans.top());
                    ans.pop();
                }
                flag = false;
                printf("\n");
            }
        }
    }

    return 0;
}