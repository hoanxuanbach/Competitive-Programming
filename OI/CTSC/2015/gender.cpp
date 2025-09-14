#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

template<class T>
struct flow_network{
	int n;
	vector<vector<int>> adj;
	struct E{
		int from, to;
		T capacity, flow;
		bool saturated() const{
			static constexpr T eps = 1e-9;
			return capacity - flow <= eps;
		}
	};
	vector<E> edge;
	flow_network(int n): n(n), adj(n){ }
	void clear_flow(){
		for(auto &e: edge) e.flow = 0;
	}
	int link(int from, int to, T cap){
		assert(0 <= min(from, to) && max(from, to) < n && cap >= 0);
		int ind = (int)edge.size();
		adj[from].push_back(ind);
		edge.push_back({from, to, cap, 0});
		adj[to].push_back(ind + 1);
		edge.push_back({to, from, cap, 0});
		return ind;
	}
	int orient(int from, int to, T cap){
        //cout << "orient " << from << ' ' << to << ' ' << cap << '\n';
		assert(0 <= min(from, to) && max(from, to) < n && cap >= 0);
		int ind = (int)edge.size();
		adj[from].push_back(ind);
		edge.push_back({from, to, cap, 0});
		adj[to].push_back(ind + 1);
		edge.push_back({to, from, 0, 0});
		return ind;
	}
	void adjust_undirected_edge_capacity(int id, T cap){
		assert(0 <= id && id < (int)edge.size() && id % 2 == 0 && cap >= 0);
		assert(edge[id].flow <= cap);
		assert(edge[id ^ 1].flow <= cap);
		edge[id].capacity = cap;
		edge[id ^ 1].capacity = cap;
	}
	void adjust_directed_edge_capacity(int id, T cap){
		assert(0 <= id && id < (int)edge.size() && id % 2 == 0 && cap >= 0);
		assert(edge[id].flow <= cap);
		edge[id].capacity = cap;
	}
	void add_flow(int i, T f){
		edge[i].flow += f;
		edge[i ^ 1].flow -= f;
	}
	friend ostream &operator<<(ostream &out, const flow_network &F){
		out << "\n";
		for(auto i = 0; i < (int)F.edge.size(); i += 2){
			auto &e = F.edge[i];
			out << "{" << e.from << " -> " << e.to << ", " << e.flow << "/" << e.capacity << "}\n";
		}
		return out;
	}
};

// Requires flow_network
template<class T>
struct dinic_maximum_flow{
	static constexpr T eps = (T)1e-9, inf = numeric_limits<T>::max();
	flow_network<T> &F;
	dinic_maximum_flow(flow_network<T> &F): F(F), ptr(F.n), level(F.n), q(F.n){ }
	vector<int> ptr, level, q;
	bool bfs(int source, int sink){
		fill(level.begin(), level.end(), -1);
		q[0] = sink;
		level[sink] = 0;
		for(auto beg = 0, end = 1; beg < end; ){
			int i = q[beg ++];
			for(auto ind: F.adj[i]){
				auto &e = F.edge[ind];
				auto &re = F.edge[ind ^ 1];
				if(re.capacity - re.flow > eps && level[e.to] == -1){
					level[e.to] = level[i] + 1;
					if(e.to == source) return true;
					q[end ++] = e.to;
				}
			}
		}
		return false;
	}
	T dfs(int u, T w, int sink){
		if(u == sink) return w;
		int &j = ptr[u];
		while(j >= 0){
			int ind = F.adj[u][j];
			auto &e = F.edge[ind];
			if(e.capacity - e.flow > eps && level[e.to] == level[u] - 1){
				T flow = dfs(e.to, min(e.capacity - e.flow, w), sink);
				if(flow > eps){
                    //cout << "flow " << e.from << ' ' << e.to << ' ' << flow << '\n';
					F.add_flow(ind, flow);
					return flow;
				}
			}
			-- j;
		}
		return 0;
	}
	// Find a maximum source-sink flow
	// O(V^2 E) ( O(E min(V^2/3, E^1/2)) for unit network )
	T maximum_flow(int source, int sink){
        //cout << "maximum_flow " << source << ' ' << sink << '\n';
		assert(0 <= source && source < F.n && 0 <= sink && sink < F.n);
		T flow = 0;
		while(bfs(source, sink)){
			for(auto i = 0; i < F.n; ++ i) ptr[i] = (int)F.adj[i].size() - 1;
			T sum = 0;
			while(true){
				T add = dfs(source, inf, sink);
				if(add <= eps) break;
				sum += add;
			}
			if(sum <= eps) break;
			flow += sum;
		}
		return flow;
	}
	// Find a minimum source-sink cut
	// O(V^2 E) ( O(E min(V^2/3, E^1/2)) for unit network )
	tuple<T, vector<int>, vector<int>> minimum_cut(int source, int sink){
		T cut_weight = maximum_flow(source, sink);
		vector<int> left, right;
		for(auto u = 0; u < F.n; ++ u) (!~level[u] ? left : right).push_back(u);
		return {cut_weight, left, right};
	}
};

void solve(){
    int N,K,M,P;cin >> N >> K >> M >> P;

    vector<int> G(M),C(M),d(M,-1),f(M,-1);
    for(int i=0;i<M;i++){
        char cc;cin >> cc;
        G[i]=(cc=='M');
    }
    for(int i=0;i<M;i++) cin >> C[i];
    vector<vector<int>> S(K,vector<int>(N,0));
    for(int i=0;i<K;i++){
        for(int j=0;j<N;j++){
            cin >> S[i][j];S[i][j]--;
            d[S[i][j]]=j;
            f[S[i][j]]=i;
        }
    }
    
    //DSU
    vector<int> par(M);
    iota(par.begin(),par.end(),0);
    function<int(int)> findpar = [&](int u){
        if(u!=par[u]) return par[u]=findpar(par[u]);
        return u;
    };
    auto unite = [&](int u,int v){
        u=findpar(u);v=findpar(v);
        if(d[u]==-1) swap(u,v);
        if(u!=v) par[v]=u;
    };

    vector<int> X(P),Y(P),B(P),D(P);
    for(int i=0;i<P;i++){
        long double T;
        cin >> X[i] >> Y[i] >> B[i] >> T;
        D[i]=B[i]*T;X[i]--;Y[i]--;
        unite(X[i],Y[i]);
    }
    for(int i=0;i<M;i++) d[i]=d[findpar(i)];

    auto get = [&](int Z,int msk,int L){
        int s=M+2*P,t=s+1;
        flow_network<int> F(M+2*P+2);
        for(int i=0;i<M;i++) if(d[i]==Z){
            //cout << i << ' ' << f[i] << '\n';
            if(f[i]!=-1){
                if(msk>>f[i]&1) F.orient(s,i,C[i]),F.orient(i,t,inf);
                else F.orient(s,i,inf);
            }
            else F.orient(s,i,C[i]);
        }
        int total=0;
        for(int i=0;i<P;i++){
            if(d[X[i]]==Z){
                total+=(B[i]+D[i])*L;
                F.orient(M+i,X[i],inf);
                F.orient(M+i,Y[i],inf);
                F.orient(s,M+i,B[i]*L);
                F.orient(X[i],M+P+i,inf);
                F.orient(Y[i],M+P+i,inf);
                F.orient(M+P+i,t,D[i]*L);
            }
        }

        dinic_maximum_flow<int> dinic(F);
        int val=dinic.maximum_flow(s,t);
        //cout << "get " << L << ' ' << Z << ' ' << msk << ' ' << total-val << '\n';
        return total-val;
    };

    int A=N*K;
    vector<vector<vector<int>>> dp(N,vector<vector<int>>(A,vector<int>(1<<K,-inf)));
    auto calc = [&](int L){
        for(int i=0;i<N;i++) for(int j=0;j<A;j++) for(int x=0;x<(1<<K);x++) dp[i][j][x]=-inf;
        for(int x=0;x<(1<<K);x++) dp[0][0][x]=get(0,x,L);
        for(int i=1;i<N;i++) for(int x=0;x<(1<<K);x++){
            int val=get(i,x,L);
            for(int y=0;y<(1<<K);y++){
                int cnt=__builtin_popcount(x^y);
                for(int j=cnt;j<A;j++) dp[i][j][x]=max(dp[i][j][x],dp[i-1][j-cnt][y]+val);
            }
        }

        int res=-inf;
        for(int i=0;i<A;i++){
            int ln=10.0*log(i+1);
            if(ln==L) for(int x=0;x<(1<<K);x++){
                //cout << i << ' ' << x << ' ' << ln << ' ' << dp[N-1][i][x] << '\n';
                res=max(res,dp[N-1][i][x]);
            }
        }
        return res+get(-1,0,L);
    };

    int res=0,mx=10.0*log(A+1);
    for(int i=0;i<=mx;i++) res=max(res,calc(i));
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
