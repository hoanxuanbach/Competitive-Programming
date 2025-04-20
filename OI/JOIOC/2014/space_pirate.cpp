#include<bits/stdc++.h>
using namespace std;
#define int long long
const int LG = 60;

signed main(){
	//freopen("SP.inp","r",stdin);
	//freopen("SP.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    
	int N,K;cin >> N >> K;

	vector<int> P(N);
    for(int i=0;i<N;i++) cin >> P[i],P[i]--;
	//cout << '\n';
	vector<int> path;
	int L=0,S=0;

	vector<int> X(N,-1),Y(N,-1);
	{//build path from 1
		vector<int> dist(N);
		
		int x=0;
		while(!dist[x]){
			path.push_back(x);
			dist[x]=(int)path.size();
			x=P[x];
		}
		S=(int)path.size();
		reverse(path.begin(),path.end());
		L=S-dist[x]+1;
		for(int i=0;i<S;i++) X[path[i]]=i;
	}

	vector<int> com,sz(N);
	vector<vector<int>> jmp(N,vector<int>(LG,0));
	vector<vector<int>> edge(N);
	
	{//calculate X_i, Y_i, and sparse table jmp[i]
		for(int i=0;i<N;i++){
			if(i!=path[0]) edge[P[i]].push_back(i);
			jmp[i][0]=P[i];
		}
		for(int j=1;j<LG;j++) for(int i=0;i<N;i++) jmp[i][j]=jmp[jmp[i][j-1]][j-1];
		
		function<void(int)> dfs = [&](int u){
			sz[u]=1;
			com.push_back(u);
			for(int v:edge[u]){
				if(!~X[v]) X[v]=X[u];
				Y[v]=Y[u]+1;
				dfs(v);
				sz[u]+=sz[v];
			}
		};
		Y[path[0]]=0;
		dfs(path[0]);
	}

	auto nxt = [&](int u,int d){
		for(int i=0;i<LG && d;i++){
			if(d>>i&1) u=jmp[u][i],d^=(1LL<<i);
		}
		return u;
	};

	vector<int> cnt(N);
	/*
	cout << S << ' ' << L << '\n';
	
	cout << "path\n";
	for(int x:path) cout << x << ' ';
	cout << '\n';
	*/
	{//case 1: from a vertex out of the path to all vertices 
		int i=L-1-(K-S)%L;
		cnt[path[i]]+=(N-S)*N;
	}
	/*
	cout << "Case 1:\n";
	for(int i=0;i<N;i++) cout << cnt[i] << ' ';
	cout << '\n';
	*/
	{//case 2: from a vertex in the path to vertices which are not in the same component with 1
		vector<vector<int>> val(N,vector<int>(LG,0));
		auto add = [&](int u,int d){
			for(int i=0;i<LG && d;i++){
				if(d>>i&1) val[u][i]++,u=jmp[u][i],d^=(1<<i);
			}
		};
		for(int i=0;i<N;i++){
			if(!~X[i]) add(nxt(i,K-S),S);//from K-S+1->K
			else{
				//case 3A:
				int T=S-max(L,X[i]+1);//from K-T+1->K
				//cout << '*' << i << ' ' << T << '\n';
				add(nxt(i,K-T),T); 
			}
		}
		for(int j=LG-1;j>=1;j--) for(int i=0;i<N;i++) val[i][j-1]+=val[i][j],val[jmp[i][j-1]][j-1]+=val[i][j];
		for(int i=0;i<N;i++) cnt[i]+=val[i][0];
	}
	/*
	cout << "Case 2+3A:\n";
	for(int i=0;i<N;i++) cout << cnt[i] << ' ';
	cout << '\n';
	*/
	//case 3: from a vertex in the path to vertices which are in the same component with 1	
	{//A: from a vertex not in cycle to other vertices not in subtree 
		//do above in case 2
	}


	{//B: from a vertex in the cycle to other vertices not in subtree
		if(L<S) for(int i=0;i<L;i++) sz[path[i]]-=sz[path[L]];

		vector<int> f(N+L),sum(N);
		vector<vector<int>> g(N+L),h(N+L);
		for(int i=-L;i<N;i++){
			f[L+i]=L+i-(K-S+L)%(L+i+1);
			g[f[L+i]].push_back(i);
			if(f[L+i]>i) h[f[L+i]-i-1].push_back(i);
			//cout << i << ' ' << f[L+i]-i-1 << '\n';
		}
		function<void(int)> dfs = [&](int u){
			for(int v:edge[u]) if(X[v]!=Y[v]) dfs(v);
			
			int d=Y[u]-X[u]-1;
			if(d>=0){
				int x=(f[L+d]<Y[u]?nxt(u,Y[u]-f[L+d]):path[f[L+d]-d-1]);
				cnt[x]+=sz[u];
				//cout << "add " << u << ' ' << d << ' ' << x << '\n';
			}

			d=Y[u]-L;
			{
				int x=(f[L+d]<Y[u]?nxt(u,Y[u]-f[L+d]):path[f[L+d]-d-1]);
				cnt[x]-=sz[u];
				//cout << "del " << u << ' ' << d << ' ' << x << '\n';
			}

			int x=lower_bound(g[Y[u]].begin(),g[Y[u]].end(),Y[u]-X[u])-upper_bound(g[Y[u]].begin(),g[Y[u]].end(),Y[u]-L);
			cnt[u]+=x*sz[u];
			//cout << "add_all " << u << ' ' << x << '\n';
			sum[Y[u]]+=sz[u];
		};
		for(int i=0;i<L;i++){
			dfs(path[i]);
			for(int d:h[i]) if(i+d+1>=0 && i+1<L && i+d+1<N){
				cnt[path[i]]-=sum[i+d+1];
				//cout << "del_sum " << path[i] << ' ' << cnt[path[i]] << ' ' << i+d+1 << ' ' << sum[i+d+1] << '\n';
			}
		}
		for(int i=-L;i<0;i++) cnt[path[f[L+i]-i-1]]+=sz[path[0]];
		if(L<S) for(int i=0;i<L;i++) sz[path[i]]+=sz[path[L]];
	}
	/*
	cout << "Case 3B:\n";
	for(int i=0;i<N;i++) cout << cnt[i] << ' ';
	cout << '\n';
	*/
	{//C: from a vertex in the path to other vertices in subtree
		vector<int> f(N,-1),sum(N,0);
		vector<vector<int>> g(N);
		for(int i=1;i<N;i++){
			f[i]=i-(K-S)%(i+1);
			for(int j=f[i];j<N;j+=i+1) g[j].push_back(i);
		}	
		function<void(int)> dfs = [&](int u){
			for(int v:edge[u]) if(X[v]==X[u]) dfs(v);
			
			//from u to path[0]
			int d=Y[u];
			if(d>0){
				int len=(Y[u]-f[d]+d+1)%(d+1);
				cnt[nxt(u,len)]+=sz[u];
			}

			//delete sz_u if par_u->path_i
			d=Y[u]-X[u]-1;
			if(d>0){
				int len=(Y[u]-1-f[d]+d+1)%(d+1);
				cnt[nxt(u,len+1)]-=sz[u];
			}

			//in range [Y_u-X_u,Y_u)
			int x=lower_bound(g[Y[u]].begin(),g[Y[u]].end(),Y[u])-lower_bound(g[Y[u]].begin(),g[Y[u]].end(),Y[u]-X[u]);
			cnt[u]+=x*sz[u];
			sum[Y[u]]+=sz[u]; 
		};
		for(int i=S-1;i>=0;i--){
			for(int x:g[i]) if(i+x+1<N) cnt[path[i]]-=sum[i+x+1];
			dfs(path[i]);
			cnt[path[i]]++;
		}
	}

	for(int i=0;i<N;i++) cout << cnt[i] << '\n';
}
