#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

int check(string s, int l)
{
    int sum = 0, sum2 = 0, pos;
    char c;
    bool f = true;
    while(f)
    {
        f = false;
        // cout << s << endl;
        for(int i = 0; i < l;)
        {
            pos = i;
            c = s[i++];
            sum2 = 0;
            while(i < l && (s[i] == '*' || s[i] == c))
            {
                if(s[i] == '*') 
                {
                    i ++;
                    continue;
                }

                if(!sum2)
                {
                    sum2 ++;
                    s[pos] = '*';
                    f = true;
                }

                sum2 ++;
                s[i] = '*';

                i ++;
            }

            sum += sum2;
            // cout << c << " " << sum2 << endl;
        }
    }
    // cout << " is " << sum << endl;
    return sum;
}

int main()
{
    int n, sum;
    string s, s2;

    scanf("%d", &n);
    while(n--)
    {
        cin >> s;

        int l = s.length() + 1;
        sum = 0;
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < l; j++)
            {
                s2 = s.substr(0, j) + (char)('A' + i) + s.substr(j);
                sum = max(sum, check(s2, l));
            }
        }

        printf("%d\n", sum);
    }

    return 0;
}