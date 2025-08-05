#include "jelly.h"
#include <bits/stdc++.h>
using namespace std;

int find_maximum_unique(int X, int Y, std::vector<int> a, std::vector<int> b) {
	int n=(int)a.size(),res=0;
	vector<pair<int,int>> P(n);
	for(int i=0;i<n;i++) P[i]={a[i],b[i]};
	sort(P.begin(),P.end());

	vector<int> val(X+1,-1);val[X]=Y;
	for(int i=0;i<=n;i++){
		
		int mx=-1;
		for(int j=0;j<=X;j++) mx=max(mx,val[j]);

		vector<int> S={0};
		for(int j=i;j<n;j++) S.push_back(P[j].second);
		sort(S.begin(),S.end());
		for(int j=1;j<=n-i;j++) S[j]+=S[j-1];
		for(int j=0;j<=n-i;j++) if(S[j]<=mx) res=max(res,i+j);

		if(i<n){
			for(int j=0;j<=X;j++){
				if(j>=P[i].first) val[j-P[i].first]=max(val[j-P[i].first],val[j]);
				val[j]-=P[i].second;
			}
		}
	}
	return res;
}
