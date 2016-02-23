#include <iostream>

using namespace std;

int G,m,l1,l2,r1,r2;

void find_mul(int turn)
{
    int quotient,remainder,temp;

    if(turn % 2 == 0)
    {
        quotient = r2 / r1;
        remainder = r2 - r1 * quotient;
        temp = quotient * l1 + l2;

        l2 = temp;
        r2 = remainder;
    }
    else
    {
        quotient = r1 / r2;
        remainder = r1 - r2 * quotient;

        if(r2 == 1)
        {
            quotient -= 1;
            remainder = 1;
        }

        temp = quotient * l2 + l1;

        l1 = temp;
        r1 = remainder;
    }
	
	cout << "turn:" << turn << endl;
	cout << l1 << " " << r1 << endl;
	cout << l2 << " " << r2 << endl << endl;
	
	if(r1 == 1)
		return;
	else
		find_mul(++ turn);
}

int main()
{
    cin >> G >> m;

    if(m > G) G -= (int)(G/m) * m;

    l1 = 1;
    l2 = 0;
    r1 = G;
    r2 = m;

    int turn = 1;

    if(r1 != 1)
    {
		cout << "turn:" << turn << endl;
		cout << l1 << " " << r1 << endl;
		cout << l2 << " " << r2 << endl << endl;
        turn ++;
        find_mul(turn);
    }

    cout << "ANS:" << l1 << endl;

    return 0;
}