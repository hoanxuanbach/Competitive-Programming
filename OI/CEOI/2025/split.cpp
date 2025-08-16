#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;

int solve(int n, int m, std::vector<std::vector<int>>& P){

	int S=n*m+1,T=0,res=0;
	
	vector<vector<int>> nxt(S,vector<int>(n,0));
	vector<vector<int>> G(n,vector<int>(n,0));
	for(int i=0;i<m;i++){
		int u=0;
		for(int j=0;j<n;j++){
			P[i][j]--;
			if(j) G[P[i][j]][P[i][j-1]]++;
			if(!nxt[u][P[i][j]]) nxt[u][P[i][j]]=++T;
			u=nxt[u][P[i][j]];
		}
	}

	vector<int> pos(n);
	auto check = [&](int i){
		for(int j=0;j<n;j++) pos[P[i][j]]=j;
		for(int j=0;j<m;j++){
			int cnt=0;
			for(int k=1;k<n;k++) cnt+=(pos[P[j][k-1]]>pos[P[j][k]]);
			if(cnt>1) return false;
		}
		return true;
	};
	for(int i=0;i<m;i++) res+=check(i);
	for(int i=0;i<n;i++) pos[P[0][i]]=i;
	

	int rev=0;
	vector<bool> used(n,false);
	vector<vector<pair<int,int>>> qq(n);
	function<void(int,int,int,int)> dfs = [&](int u,int x,int y,int i){
		//cout << "dfs " << u << ' ' << x << ' ' << y << ' ' << i << endl;
		for(int a=0;a<n;a++){
			if(used[a]) continue;
			used[a]=true;
			int add=0;
			for(int b=0;b<n;b++) if(!used[b]) add+=G[a][b];
			rev+=add;
			//cout << "get " << u << ' ' << x << ' ' << y << ' ' << a << ' ' << pos[a] << ' ' << add << ' ' << rev << endl;
			if(rev<=m){
				int v=nxt[u][a];
				if(i){
					if(x<i && a==P[0][x]){
						if(!v) qq[i].push_back({x+1,y});
						else dfs(v,x+1,y,i);
					}
					if((i+y)<n && a==P[0][i+y]){
						if(!v) qq[i].push_back({x,y+1});
						else dfs(v,x,y+1,i);
					}
				}
				else{
					int id=pos[a];
					if(x==id) dfs(v,x+1,y,i);
					else{
						if(v) dfs(v,x,1,id);
						else qq[id].push_back({x,1});
					}
				}
			}

			rev-=add;
			used[a]=false;
		}
	};
	dfs(0,0,0,0);

	for(int i=1;i<n;i++){
		vector<int> X,Y;
		for(int j=0;j<i;j++) X.push_back(P[0][j]);
		for(int j=i;j<n;j++) Y.push_back(P[0][j]);

		vector<vector<int>> cX(n,vector<int>(n-i+1,0)),cY(n,vector<int>(i+1,0));
		for(int j=0;j<n;j++) for(int k=n-i-1;k>=0;k--) cX[j][k]=cX[j][k+1]+G[j][Y[k]];
		for(int j=0;j<n;j++) for(int k=i-1;k>=0;k--) cY[j][k]=cY[j][k+1]+G[j][X[k]];

		vector<vector<int>> dp(i+1,vector<int>(n-i+1,0));
		dp[i][n-i]=1;
		for(int j=i;j>=0;j--) for(int k=n-i;k>=0;k--){
			if(j<i && !cX[X[j]][k] && !cY[X[j]][j+1]) dp[j][k]=(dp[j][k]+dp[j+1][k])%mod;
			if(k<n-i && !cY[Y[k]][j] && !cX[Y[k]][k+1]) dp[j][k]=(dp[j][k]+dp[j][k+1])%mod;
		}

		for(auto [x,y]:qq[i]){
			res=(res+dp[x][y])%mod;
			//cout << i << ' ' << x << ' ' << y << endl;
		}
	}
	return res;
}
