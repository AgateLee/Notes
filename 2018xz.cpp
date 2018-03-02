#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int cs[11];

void check() {
	if((cs[2] + 2) % 4 == cs[5] % 4);
	else return;
		
	if (cs[3] == 1 && cs[2] != cs[3] && cs[2] == cs[4] && cs[2] == cs[6]);
	else if(cs[3] == 2 && cs[2] == cs[3] && cs[2] == cs[4] && cs[2] != cs[6]);
	else if(cs[3] == 3 && cs[3] != cs[2] && cs[3] == cs[4] && cs[3] == cs[6]);
	else if(cs[3] == 4 && cs[2] == cs[3] && cs[2] != cs[4] && cs[2] == cs[6]);
	else return;
	
	if(cs[4] == 1 && cs[1] == cs[5]);
	else if(cs[4] == 2 && cs[2] == cs[7]);
	else if(cs[4] == 3 && cs[1] == cs[9]);
	else if(cs[4] == 4 && cs[6] == cs[10]);
	else return;
		
	if (cs[5] == 1 && cs[5] == cs[8] || 
	    cs[5] == 2 && cs[5] == cs[4] ||
		cs[5] == 3 && cs[5] == cs[9] ||
		cs[5] == 4 && cs[5] == cs[7]);
	else return;
		
	if (cs[6] == 1 && cs[2] == cs[4] && cs[2] == cs[8] ||
		cs[6] == 2 && cs[1] == cs[6] && cs[1] == cs[8] ||
		cs[6] == 3 && cs[3] == cs[10] && cs[3] == cs[8] ||
		cs[6] == 4 && cs[5] == cs[9] && cs[5] == cs[8]);
	else return;
		
	int sum[5] = {0};
	for(int i = 1; i <= 10; i++)
		sum[cs[i]] ++;
	int m = min(min(sum[1], sum[2]), min(sum[3], sum[4]));
	if (cs[7] == 1 && m == sum[3] ||
		cs[7] == 2 && m == sum[2] ||
		cs[7] == 3 && m == sum[1] ||
		cs[7] == 4 && m == sum[4]);
	else return;
	
	if (cs[8] == 1 && (cs[1] + 1 != cs[7] || cs[1] - 1 != cs[7]) ||
		cs[8] == 2 && (cs[1] + 1 != cs[5] || cs[1] - 1 != cs[5]) ||
		cs[8] == 3 && (cs[1] + 1 != cs[2] || cs[1] - 1 != cs[2]) ||
		cs[8] == 4 && (cs[1] + 1 != cs[10] || cs[1] - 1 != cs[10]));
	else return;
	
	if (cs[1] == cs[6]) {
		if (cs[9] == 1 && cs[5] != cs[6] ||
			cs[9] == 2 && cs[5] != cs[10] ||
			cs[9] == 3 && cs[5] != cs[2] ||
			cs[9] == 4 && cs[5] != cs[9]);
		else return;
	} else {
		if (cs[9] == 1 && cs[5] == cs[6] ||
			cs[9] == 2 && cs[5] == cs[10] ||
			cs[9] == 3 && cs[5] == cs[2] ||
			cs[9] == 4 && cs[5] == cs[9]);
		else return;
	}
	
	int mm = max(max(sum[1], sum[2]), max(sum[3], sum[4]));
	int dis = mm - m;
	if (cs[10] == 1 && dis == 3 ||
		cs[10] == 2 && dis == 2 ||
		cs[10] == 3 && dis == 4 ||
		cs[10] == 4 && dis == 1);
	else return;
	
	for (int i = 1; i <= 10; i++)
		printf("%d:%c ", i, 'A' + cs[i] - 1);
	printf(" OK\n");
}

void next_pro(int cur) {
	if (cur > 10) {
		check();		
		return;
	}
	
	for(int i = 1; i <= 4; i++) {
		cs[cur] = i;
		next_pro(cur + 1);
	}
}

int main() {
	memset(cs, 0, sizeof(cs));
	
	next_pro(1);
	
	return 0;
}