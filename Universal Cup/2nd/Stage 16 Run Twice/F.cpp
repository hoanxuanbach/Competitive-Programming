#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define fi first
#define se second
#define For(i, l, r) for (auto i = (l); i < (r); i++)
#define ForE(i, l, r) for (auto i = (l); i <= (r); i++)
#define FordE(i, l, r) for (auto i = (l); i >= (r); i--)
#define Fora(v, a) for (auto v: (a))
#define bend(a) (a).begin(), (a).end()
#define isz(a) ((signed)(a).size())

using ll = long long;
using ld = long double;
using pii = pair <int, int>;
using vi = vector <int>;
using vpii = vector <pii>;
using vvi = vector <vi>;

template<bool Enable_small_to_large = true>
struct disjoint_set{
	int n, _classes;
	vector<int> p;
	disjoint_set(int n): n(n), _classes(n), p(n, -1){ }
	int make_set(){
		p.push_back(-1);
		++ _classes;
		return n ++;
	}
	int classes() const{
		return _classes;
	}
	int root(int u){
		return p[u] < 0 ? u : p[u] = root(p[u]);
	}
	bool share(int a, int b){
		return root(a) == root(b);
	}
	int size(int u){
		return -p[root(u)];
	}
	bool merge(int u, int v){
		u = root(u), v = root(v);
		if(u == v) return false;
		-- _classes;
		if constexpr(Enable_small_to_large) if(p[u] > p[v]) swap(u, v);
		p[u] += p[v], p[v] = u;
		return true;
	}
	bool merge(int u, int v, auto act){
		u = root(u), v = root(v);
		if(u == v) return false;
		-- _classes;
		bool swapped = false;
		if constexpr(Enable_small_to_large) if(p[u] > p[v]) swap(u, v), swapped = true;
		p[u] += p[v], p[v] = u;
		act(u, v, swapped);
		return true;
	}
	void clear(){
		_classes = n;
		fill(p.begin(), p.end(), -1);
	}
	vector<vector<int>> group_up(){
		vector<vector<int>> g(n);
		for(auto i = 0; i < n; ++ i) g[root(i)].push_back(i);
		g.erase(remove_if(g.begin(), g.end(), [&](auto &s){ return s.empty(); }), g.end());
		return g;
	}
};

const int N = 1e3 + 5, M = 5e3 + 5;

int n, m;
vector <int> adj[N];
bool madj[N][N];

void connect_edge(int u, int v){
	adj[u].emplace_back(v);
	adj[v].emplace_back(u);
	madj[u][v] = madj[v][u] = true;
}

bool f(){
	vector <pair <int, int>> a;
	ForE(u, 1, n){
		a.emplace_back(pair{isz(adj[u]), u});
	}
	sort(bend(a), greater<>());

	a.resize(5);
	if (a[3].first == a[4].first){
		return false;
	}
	int cnt = 0;
	For(i, 0, 4){
		For(j, i + 1, 4){
			int u = a[i].second, v = a[j].second;
			cnt += madj[u][v];
		}
	}
	return cnt >= 5;
}

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	// freopen("KEK.inp", "r", stdin);
	// freopen("KEK.out", "w", stdout);
	cin >> n >> m;
	ForE(i, 1, m){
		int u, v; cin >> u >> v;
		connect_edge(u, v);
	}

	if (f()){
		cout << "ok" << endl;
		return 0;
	}
	vector <pair <int, int>> a;
	ForE(u, 1, n){
		a.emplace_back(isz(adj[u]), u);
	}
	sort(bend(a), greater<>());
	vector <pair <int, int>> edges;
	For(i, 0, 4){
		For(j, i + 1, 4){
			if (isz(edges) == 5) continue;
			int u = a[i].second, v = a[j].second;
			if (not madj[u][v]){
				connect_edge(u, v);
				edges.emplace_back(u, v);
			}
		}
	}
	cout << "mark" << endl;
	cout << isz(edges) << endl;
	for (auto &[u, v]: edges){
		cout << u << ' ' << v << endl;
	}
}

/*
==================================================+
INPUT                                             |
--------------------------------------------------|

--------------------------------------------------|
==================================================+
OUTPUT                                            |
--------------------------------------------------|

--------------------------------------------------|
==================================================+
*/