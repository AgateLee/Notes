#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

bool sign[28];

int main()
{
	char s[205], ans[28];
	int pos = 0;
	
	memset(sign, 0, sizeof(sign));
	scanf("%s", s);
	
	for(int i = 0; i < strlen(s); i++)
	{
		if(s[i] == 'J')
			s[i] = 'I';
			
		if(!sign[s[i] - 'A'])
		{
			sign[s[i] = 'A'] = true;
			ans[pos ++] = s[i];
		}
	}
	
	for(int i = pos, pos = 0; i < 25; i++)
	{
		while(sign[pos])
			pos ++;
			
		ans[i] = pos + 'A';
	}
	
	for(int i = 0; i < 25; i++)
	{
		printf("%c", ans[i]);
		if(i % 5 == 4)
			printf("\n");
	}

	return 0;
}
