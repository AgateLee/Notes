#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

typedef struct node{
	double x, y, z;

	node() {x = y = z = 0;};
	node(double x1, double y1, double z1):x(x1), y(y1), z(z1){};

	node operator - (const node &B) const
	{
		return node(x - B.x, y - B.y, z - B.z);
	}

	double dot(const node & B) const
	{
		return x * B.x + y * B.y + z * B.z;
	}

	node cross(const node & B) const
	{
		return node(y * B.z - z * B.y, z * B.x - x * B.z, x * B.y - y * B.x);
	} 
} node;

bool oneSide(node P, node A, node B, node C)
{
	node AB = B - A;
	node AC = C - A;
	node AP = P - A;

	node v1 = AB.cross(AC);
	node v2 = AB.cross(AP);

	if(v1.dot(v2) >= 0)
		return true;
	else
		return false;
}

int main()
{
	node P, S[3];
	int n;
	bool flag;
	scanf("%d", &n);
	while(n--)
	{
		flag = true;
		scanf("%lf %lf", &P.x, &P.y);
		for(int i = 0; i < 3; i++)
		{
			scanf("%lf %lf", &S[i].x, &S[i].y);
			if(P.x == S[i].x && P.y == S[i].y)
			{
				flag = false;
				printf("YES\n");
			}
		}

		if(flag)
		{
			if(oneSide(P, S[0], S[1], S[2]) && oneSide(P, S[1], S[2], S[0]) && oneSide(P, S[2], S[0], S[1]))
				printf("YES\n");
			else
				printf("NO\n");
		}
	}

	return 0;
}