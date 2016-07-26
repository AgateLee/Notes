#include <iostream>
#include <cstring>
using namespace std;

int get(int n)
{
    if(n == 1 || n == 0)
        return 1;
    else if(n == 2)
        return 2;
    else if(n&0x01)
        return get(n>>1);
    else // 2x = x * 2 + 0 = (x - 1) * 2 + 2
        return get(n>>1) + get((n>>1) - 1);
}

int main()
{
    int n;

    scanf("%d", &n);
    printf("%d\n", get(n));
}