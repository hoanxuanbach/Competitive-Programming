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
 
const int maxn = 1e7+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

template<class T>
struct graph{
#ifdef LOCAL
	#define ASSERT(x) assert(x)
#else
	#define ASSERT(x) 42
#endif
	using Weight_t = T;
	struct Edge_t{
		int from, to;
		T cost;
		Edge_t &inplace_flip(){
			swap(from, to);
			return *this;
		}
		Edge_t flip() const{
			return (*this).inplace_flip();
		}
	};
	int n;
	vector<Edge_t> edge;
	vector<vector<int>> adj;
	function<bool(int)> ignore;
	graph(int n = 1): n(n), adj(n){
		ASSERT(n >= 1);
	}
	graph(const vector<vector<int>> &adj, bool undirected = true): n((int)adj.size()), adj(n){
		ASSERT(n >= 1);
		if(undirected){
			for(auto u = 0; u < n; ++ u) for(auto v: adj[u]) if(u < v) link(u, v);
		}
		else for(auto u = 0; u < n; ++ u) for(auto v: adj[u]) orient(u, v);
	}
	graph(const vector<vector<pair<int, T>>> &adj, bool undirected = true): n((int)adj.size()), adj(n){
		ASSERT(n >= 1);
		if(undirected){
			for(auto u = 0; u < n; ++ u) for(auto [v, w]: adj[u]) if(u < v) link(u, v, w);
		}
		else for(auto u = 0; u < n; ++ u) for(auto [v, w]: adj[u]) orient(u, v, w);
	}
	graph(int n, const vector<array<int, 2>> &edge, bool undirected = true): n(n), adj(n){
		ASSERT(n >= 1);
		for(auto [u, v]: edge) undirected ? link(u, v) : orient(u, v);
	}
	graph(int n, const vector<tuple<int, int, T>> &edge, bool undirected = true): n(n), adj(n){
		ASSERT(n >= 1);
		for(auto [u, v, w]: edge) undirected ? link(u, v, w) : orient(u, v, w);
	}
	int add_vertex(){
		adj.emplace_back();
		return n ++;
	}
	int operator()(int u, int id) const{
		ASSERT(0 <= id && id < (int)edge.size());
		ASSERT(edge[id].from == u || edge[id].to == u);
		return u ^ edge[id].from ^ edge[id].to;
	}
	int link(int u, int v, T w = {}){ // insert an undirected edge
		int id = (int)edge.size();
		adj[u].push_back(id), adj[v].push_back(id), edge.push_back({u, v, w});
		return id;
	}
	int orient(int u, int v, T w = {}){ // insert a directed edge
		int id = (int)edge.size();
		adj[u].push_back(id), edge.push_back({u, v, w});
		return id;
	}
	void clear(){
		for(auto [u, v, w]: edge){
			adj[u].clear();
			adj[v].clear();
		}
		edge.clear();
		ignore = {};
	}
	graph transpose() const{ // the transpose of the directed graph
		graph res(n);
		for(auto id = 0; id < (int)edge.size(); ++ id){
			if(ignore && ignore(id)) continue;
			res.orient(edge[id].to, edge[id].from, edge[id].cost);
		}
		return res;
	}
	int degree(int u) const{ // the degree (outdegree if directed) of u (without the ignoration rule)
		return (int)adj[u].size();
	}
	// The adjacency list is sorted for each vertex.
	vector<vector<int>> get_adjacency_list() const{
		vector<vector<int>> res(n);
		for(auto u = 0; u < n; ++ u) for(auto id: adj[u]){
			if(ignore && ignore(id)) continue;
			res[(*this)(u, id)].push_back(u);
		}
		return res;
	}
	void set_ignoration_rule(const function<bool(int)> &f){
		ignore = f;
	}
	void reset_ignoration_rule(){
		ignore = nullptr;
	}
	template<class ostream>
	friend ostream &operator<<(ostream &out, const graph &g){
		out << "\n";
		for(auto id = 0; id < (int)g.edge.size(); ++ id){
			if(g.ignore && g.ignore(id)) continue;
			auto &e = g.edge[id];
			out << "{" << e.from << ", " << e.to << ", " << e.cost << "}\n";
		}
		return out;
	}
	template<bool directed = false, bool has_weight = false>
	static graph read(int n, int m = -1, int offset = 1){
		ASSERT(n >= 1);
		if(m == -1) m = n - 1;
		ASSERT(m >= 0);
		graph<T> g(n);
		for(auto id = 0; id < m; ++ id){
			int u, v;
			T w = T{1};
			cin >> u >> v, u -= offset, v -= offset;
			if constexpr(has_weight) cin >> w;
			directed ? g.orient(u, v, w) : g.link(u, v, w);
		}
		return move(g);
	}
#undef ASSERT
};
// Requires graph
template<class T> // O(V^3)
int blossom_maximum_unweighted_matching(const graph<T> &g){
	vector<int> mate(g.n, -1), label(g.n), parent(g.n), orig(g.n);
	queue<int> q;
	vector<int> aux(g.n, -1);
	int aux_time = -1;
	auto lca = [&](int x, int y){
		++ aux_time;
		while(true){
			if(x != -1){
				if(aux[x] == aux_time) return x;
				aux[x] = aux_time;
				if(mate[x] == -1) x = -1;
				else x = orig[parent[mate[x]]];
			}
			swap(x, y);
		}
	};
	auto blossom = [&](int v, int w, int a){
		while(orig[v] != a){
			parent[v] = w, w = mate[v];
			if(label[w] == 1) label[w] = 0, q.push(w);
			orig[v] = orig[w] = a, v = parent[w];
		}
	};
	auto augment = [&](int v){
		while(v != -1){
			int pv = parent[v], nv = mate[pv];
			mate[v] = pv, mate[pv] = v, v = nv;
		}
	};
	auto bfs = [&](int root){
		fill(label.begin(), label.end(), -1);
		iota(orig.begin(), orig.end(), 0);
		while(!q.empty()) q.pop();
		q.push(root);
		label[root] = 0;
		while(!q.empty()){
			int v = q.front(); q.pop();
			for(auto id : g.adj[v]){
				if(g.ignore && g.ignore(id)) continue;
				auto &e = g.edge[id];
				int x = e.from ^ e.to ^ v;
				if(label[x] == -1){
					label[x] = 1, parent[x] = v;
					if(mate[x] == -1){
						augment(x);
						return true;
					}
					label[mate[x]] = 0, q.push(mate[x]);
					continue;
				}
				if(label[x] == 0 && orig[v] != orig[x]){
					int a = lca(orig[v], orig[x]);
					blossom(x, v, a), blossom(v, x, a);
				}
			}
		}
		return false;
	};
	auto greedy = [&](){
		vector<int> order(g.n);
		iota(order.begin(), order.end(), 0);
		shuffle(order.begin(), order.end(), mt19937(787788));
		for(auto i: order) if(mate[i] == -1) for(auto id: g.adj[i]){
			if(g.ignore && g.ignore(id)) continue;
			auto &e = g.edge[id];
			int to = e.from ^ e.to ^ i;
			if(mate[to] == -1){
				mate[i] = to, mate[to] = i;
				break;
			}
		}
	};
	greedy();
	for(auto i = 0; i < g.n; ++ i) if(mate[i] == -1) bfs(i);
    int cnt=0;
    for(int i=0;i<g.n;i++) if(i<mate[i]) cnt++;
	return cnt;
}

const int S=200;
void solve(){
    int n;cin >> n;
    vector<pii> E;

    int P=-1;
	vector<int> p(n+1);
    for(int i=2;i<=n;i++){
        if(!p[i]){
            if(i>n/4 && i<=n/3) P=i;
            for(int j=i;j<=n;j+=i){
                p[j]=i;
                if(n<=S) E.push_back({j,j/i});
            }
        }
    }
    if(n>S){
        cout << "first " << 2*P << '\n';
        return;
    }

    int M=-1,X=-1;
    
    for(int i=0;i<=n;i+=2){
        graph<int> G(n);
        for(auto [u,v]:E){
            if(u==i || v==i) continue;
            G.link(u-1,v-1);
            //cout << "link " << u << ' ' << v << '\n';
        }
        int T=blossom_maximum_unweighted_matching(G);
        //cout << i << ' ' << T << '\n';
        if(!i) M=T;
        else if(T==M) X=i;
    }
    if(X==-1) cout << "second\n";
    else cout << "first " << X << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
