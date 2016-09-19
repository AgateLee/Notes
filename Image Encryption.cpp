#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

class matrix{
public:
	int ** arr;
	int n;

	matrix()
	{
		n = 0;
		arr = NULL;
	}

	matrix(int i)
	{
		n = i;
		arr = new int *[i];
		for(int j = 0; j < i; j++)
		{
			arr[j] = new int[i];
		}
	}

	matrix(const matrix & t)
	{
		n = t.n;
		arr = new int *[t.n];
		for(int j = 0; j < t.n; j++)
		{
			arr[j] = new int[t.n];
		}

		for(int i = 0; i < t.n; i++)
		{
			for(int j = 0; j < t.n; j++)
				arr[i][j] = t.arr[i][j];
		}
	}

	void operator =(const matrix & t)
	{
		n = t.n;
		arr = new int *[t.n];
		for(int j = 0; j < t.n; j++)
		{
			arr[j] = new int[t.n];
		}

		for(int i = 0; i < t.n; i++)
		{
			for(int j = 0; j < t.n; j++)
				arr[i][j] = t.arr[i][j];
		}
	}

	bool operator <(const matrix & t) const
	{
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(arr[i][j] < t.arr[i][j])
					return true;
				else if(t.arr[i][j] < arr[i][j])
					return false;
			}
		}

		return false;
	}

	~matrix()
	{
		for(int j = 0; j < n; j++)
			delete[] arr[j];
		delete[] arr;
	}

	void show();
	void rotate();
	void rotate_block();

	//n is even
	matrix sub(int a, int b);
	void subcopy(matrix t, int a, int b);
};

void matrix::subcopy(matrix t, int a, int b)
{
	int len = n>>1;

	for(int i = 0; i < len; i++)
		for(int j = 0; j < len; j++)
			arr[a + i][b + j] = t.arr[i][j];
}

matrix matrix::sub(int a, int b)
{
	int len = n>>1;

	matrix temp(len);
	for(int i = 0; i < len; i++)
	{
		for(int j = 0; j < len; j++)
			temp.arr[i][j] = arr[i + a][j + b];
	}

	return temp;
}

void matrix::rotate()
{
	matrix m(* this);

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			arr[j][n - 1 - i] = m.arr[i][j];
		}
	}
}

void matrix::rotate_block()
{
	int len = n>>1;
	matrix lu = this->sub(0, 0), ru = this->sub(0, len),
		ld = this->sub(len, 0), rd = this->sub(len, len);

	this->subcopy(lu, 0, len);
	this->subcopy(ru, len, len);
	this->subcopy(ld, 0, 0);
	this->subcopy(rd, len, 0);
}

void matrix::show()
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
	printf("\n");
}

void dfs(matrix & cur, int n)
{
	if(n <= 1)
		return;
	else if(n % 2 == 1)
	{
		matrix ans = cur, tp = cur;

		// ans.show();
		for(int i = 0; i < 3; i++)
		{
			tp.rotate();
			if(tp < ans)
				ans = tp;

			// tp.show();
			// ans.show();
			// printf("~~~\n");
		}

		cur = ans;
	}
	else if(n % 2 == 0)
	{
		int len = n >> 1;
		matrix temp = cur.sub(0, 0);
		dfs(temp, len);
		cur.subcopy(temp, 0, 0);

		temp = cur.sub(0, len);
		dfs(temp, len);
		cur.subcopy(temp, 0, len);

		temp = cur.sub(len, 0);
		dfs(temp, len);
		cur.subcopy(temp, len, 0);

		temp = cur.sub(len, len);
		dfs(temp, len);
		cur.subcopy(temp, len, len);

		matrix ans = cur, tp = cur;

		// ans.show();
		for(int i = 0; i < 3; i++)
		{
			tp.rotate_block();
			if(tp < ans)
				ans = tp;

			// tp.show();
			// ans.show();
			// printf("~~~\n");
		}

		cur = ans;
	}
}

int main()
{
 	int n, ca;
 	freopen("input.txt", "r", stdin);
 	scanf("%d", &ca);
 	while(ca --)
 	{
 		scanf("%d", &n);

 		matrix m1(n), m2(n);

 		for(int i = 0; i < n; i++)
 		{
 			for(int j = 0; j < n; j++)
 			{
 				scanf("%d", &m1.arr[i][j]);
 			}
 		}

 		for(int i = 0; i < n; i++)
 		{
 			for(int j = 0; j < n; j++)
 			{
 				scanf("%d", &m2.arr[i][j]);
 			}
 		}

 		dfs(m1, n);
 		dfs(m2, n);

 		// m1.show();
 		// m2.show();

 		if(m1 < m2 || m2 < m1)
 			printf("No\n");
 		else
 			printf("Yes\n");
 	}

 	return 0;
}