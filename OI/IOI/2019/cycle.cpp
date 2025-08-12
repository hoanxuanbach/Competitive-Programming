#include "cycle.h"
#include<bits/stdc++.h>
using namespace std;

void escape(int n) {
	int x=jump(0);
	if(!x) x=jump(n/2);
	
	assert(x);
	int k=0;
	while((1<<(k+1))<n) k++;
	while(k>=0){
		if(x) x=jump((1<<k));
		else x=jump(n-(1<<k));
		k--;
	}
	if(!x) x=jump(n-1);
}
