#include "squares.h"
#include <bits/stdc++.h>
using namespace std;

int K=10;
string S;
bool init=false;
void Init(){
	init = true;

	vector<bool> del(1<<K);
	vector<vector<pair<int,int>>> G((1<<(K-1)));
	for(int i=0;i<(1<<(K-1));i++) for(int j=0;j<=1;j++){
		int ni=(i<<1|j)&((1<<(K-1))-1);
		G[i].push_back({ni,i<<1|j});
	}

	vector<int> path;
	function<void(int)> dfs = [&](int u){
		for(auto [v,id]:G[u]){
			if(del[id]) continue;
			del[id]=true;dfs(v);
		}
		path.push_back(u);
	};
	dfs(0);
	reverse(path.begin(),path.end());
	for(int i=K-1;i>0;i--) S+=char((path[0]>>i&1)+'0');
	for(int i=1;i<(int)path.size();i++) S+=char((path[i]&1)+'0');
}

std::vector<int> paint(int n) {
	if(!init) Init();
	vector<int> c;
	for(int i=0;i<n;i++) c.push_back(S[i]-'0');
	c.push_back(K);
	return c;
}

int find_location(int n, std::vector<int> c) {
	if(!init) Init();
	for(int i=0;i<K;i++) if(c[i]==-1) return n-i;
	for(int i=0;i<=n-K;i++){
		bool ok=true;
		for(int j=0;j<K;j++) if((S[i+j]-'0')!=c[j]) ok=false;
		if(ok) return i;
	}
	return -1;
}
