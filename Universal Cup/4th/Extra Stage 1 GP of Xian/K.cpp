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

const int inf = 1e9;
void solve(){
    int n;cin >> n;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<n;i++) cin >> b[i];

    if(a==b){
        cout << "Yes\n";
        return;
    }
    for(int i=0;i<n;i++) if((a[i]&b[i])!=b[i]){
        cout << "No\n";
        return;
    }

    flow_network<int> F(n+2);
    for(int i=0;i<n;i++) F.orient(n,i,1);
    for(int i=0;i<n;i++) F.orient(b[i],n+1,1);
    for(int i=0;i<n;i++) for(int j=0;j<20;j++) if(i>>j&1) F.orient(i,i^(1<<j),inf);
    
    dinic_maximum_flow<int> D(F);
    if(D.maximum_flow(n,n+1)==n) cout << "Yes\n";
    else cout << "No\n";
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
