#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int maxn = 1500005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
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
    int n,m;cin >> n >> m;

    auto cal = [&](vector<int> x,vector<vector<int>> a,vector<vector<int>> b){
        if(m==1){
            vector<pii> p(n);
            for(int i=0;i<n;i++) p[i]={x[i],i};
            sort(p.begin(),p.end());
            int cur=0,add=0;
            for(int i=0;i<n;i++) add-=a[i][0],cur+=a[p[i].se][0]*abs(p[0].fi-p[i].fi);
            int res=cur,id=0;
            for(int i=1;i<n;i++){
                add+=2*a[p[i-1].se][0];
                cur+=add*(p[i].fi-p[i-1].fi);
                if(cur<res) res=cur,id=i;
            }
            return pair<int,vector<int>>{res,{p[id].fi}};
        }
        else{
            //m*(n+1)
            vector<int> v=x;
            sort(v.begin(),v.end());
            int S=m*(n+1),T=m*(n+1)+1;
            flow_network<int> F(T+1);
            for(int i=0;i<m;i++){
                F.orient(S,i*(n+1),inf);
                //Flow.add_edge(i*(n+1),S,inf);
                F.orient(i*(n+1)+n,T,inf);
                //Flow.add_edge(T,i*(n+1)+n,inf);
                for(int j=0;j<n;j++){
                    int total=0;
                    for(int k=0;k<n;k++) total+=a[k][i]*abs(x[k]-v[j]);
                    F.orient(i*(n+1)+j,i*(n+1)+j+1,total);
                    //Flow.add_edge(i*(n+1)+j+1,i*(n+1)+j,inf);
                }
            }
            //cout << Flow.m << '\n';
            
            for(int i=0;i<m;i++) for(int j=0;j<m;j++) if(i!=j){
                for(int k=1;k<n;k++) F.orient(i*(n+1)+k,j*(n+1)+k,b[i][j]*(v[k]-v[k-1]));
            }
            
            dinic_maximum_flow<int> D(F);

            int res=D.maximum_flow(S,T);
            
            vector<int> ans(m);
            for(int i=0;i<m;i++) for(int j=0;j<n;j++) if(D.level[i*(n+1)+j]==-1 && D.level[i*(n+1)+j+1]!=-1) ans[i]=v[j];
            return pair<int,vector<int>>{res,ans}; 
        }
    };  


    vector<int> x(n),y(n);
    for(int i=0;i<n;i++) cin >> x[i] >> y[i];
    vector<vector<int>> a(n,vector<int>(m));
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin >> a[i][j];
    vector<vector<int>> b(m,vector<int>(m));
    for(int i=0;i<m;i++) for(int j=i+1;j<m;j++) cin >> b[i][j],b[j][i]=b[i][j];
    auto [sx,cx]=cal(x,a,b);
    auto [sy,cy]=cal(y,a,b);

    int tx=0,ty=0;
    cout << sx+sy << '\n';
    for(int i=0;i<m;i++){
        cout << cx[i] << ' ' << cy[i] << '\n';
        for(int j=0;j<n;j++) tx+=abs(cx[i]-x[j])*a[j][i],ty+=abs(cy[i]-y[j])*a[j][i];
        for(int j=0;j<i;j++) tx+=abs(cx[i]-cx[j])*b[i][j],ty+=abs(cy[i]-cy[j])*b[i][j];
    }
    //cout << tx+ty << '\n';
    assert((tx+ty)==(sx+sy));
}

signed main(){
    //freopen("locate6.in","r",stdin);
    //freopen("locate6.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}