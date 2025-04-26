#include<bits/stdc++.h>
using namespace std;
const int maxn = 205;

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

int n,m,k,c[maxn],res[maxn];
int d[maxn][maxn];
vector<int> edge[maxn];

bool check=true;
vector<int> cA,cB,A,B;
void dfs(int u){
    if(c[u]==1) cA.push_back(u);
    else cB.push_back(u);
    for(int v:edge[u]){
        if(!c[v]) c[v]=c[u]^3,dfs(v);
        else if(c[v]==c[u]) check=false;
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> k;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) d[i][j]=(i!=j)*n;
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;u--;v--;
        d[u][v]=d[v][u]=1;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) for(int k=0;k<n;k++) d[j][k]=min(d[j][k],d[j][i]+d[i][k]);
    for(int i=0;i<n;i++) if(!c[i]){
        cA.clear();
        cB.clear();
        c[i]=1,dfs(i);
        if((int)cA.size()<(int)cB.size()) swap(cA,cB);
        A.insert(A.end(),cA.begin(),cA.end());
        B.insert(B.end(),cB.begin(),cB.end());
    }
    if(!check){
        cout << "NIE\n";
        return 0;
    }
    for(int i=0;i<n;i++) c[i]=2;
    for(int u:A) c[u]=1;
    if(k&1){
        cout << (int)A.size() << '\n';
        for(int i=0;i<n;i++) cout << c[i] << ' ';
        cout << '\n';
        return 0;
    }
    int cnt=n;
    flow_network<int> F(n+2);
    for(int u:A) res[u]=1,F.orient(n,u,1);
    for(int u:B) res[u]=k,F.orient(u,n+1,1);
    for(int u:A) for(int v:B) if(d[u][v]<k-1) F.orient(u,v,n);
    dinic_maximum_flow<int> D(F);
    auto [val,lt,rt]=D.minimum_cut(n,n+1);
    cnt-=val;
    for(int u:lt) if(c[u]!=1) res[u]=0;
    for(int u:rt) if(c[u]!=2) res[u]=0;
    queue<int> q;
    for(int i=0;i<n;i++) if(res[i]==k) q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        if(res[u]==1) continue;
        for(int v:edge[u]){
            if(!res[v]) res[v]=res[u]-1,q.push(v);
        }
    }   
    for(int i=0;i<n;i++) if(!res[i]) res[i]=c[i];
    cout << cnt << '\n';
    for(int i=0;i<n;i++) cout << res[i] << ' ';
    cout << '\n';
}