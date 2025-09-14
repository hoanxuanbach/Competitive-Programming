#include<bits/stdc++.h>
using namespace std;

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

void solve(){
    int n,m,k;cin >> n >> m >> k;
    vector<pair<int,int>> e(m);
    for(auto &[u,v]:e) cin >> u >> v,u--,v--;
    vector<int> deg(n);
    set<int> ss,st;
    deg[0]++;deg[n-1]++;
    for(int i=0;i<k;i++){
        int x;cin >> x;x--;
        auto [u,v]=e[x];
        ss.insert(x);
        deg[u]++;deg[v]++;
        st.insert(u);
        st.insert(v);
    }
    for(int i=0;i<n;i++) if(deg[i]>2){
        cout << -1 << '\n';
        return;
    }
    flow_network<int> F(n+2);
    for(int i=0;i<m;i++){
        if(ss.count(i)) continue;
        auto [u,v]=e[i];
        F.orient(st.count(u)?n:u,st.count(v)?n+1:v,1);
    }
    dinic_maximum_flow<int> D(F);
    cout << D.maximum_flow(n,n+1) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
