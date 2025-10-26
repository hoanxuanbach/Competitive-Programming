#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/trie_policy.hpp>
// #include <ext/rope>

using namespace std;
// using namespace __gnu_cxx;
// using namespace __gnu_pbds;

void Hollwo_Pelw();

signed main(){
#ifndef hollwo_pelw_local
	if (fopen(".inp", "r"))
		assert(freopen(".inp", "r", stdin)), assert(freopen(".out", "w", stdout));
#else
	using namespace chrono;
	auto start = steady_clock::now();
#endif
	cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
	int testcases = 1;
	// cin >> testcases;
	for (int test = 1; test <= testcases; test++){
		// cout << "Case #" << test << ": ";
		Hollwo_Pelw();
	}
#ifdef hollwo_pelw_local
	auto end = steady_clock::now();
	cout << "\nExecution time : " << duration_cast<milliseconds> (end - start).count() << "[ms]" << endl;
#endif
}

template<bool Enable_small_to_large = true>
struct disjoint_set{
#ifdef LOCAL
	#define ASSERT(x) assert(x)
#else
	#define ASSERT(x) 42
#endif
	int n, _group_count;
	vector<int> p;
	vector<list<int>> group;
	disjoint_set(){ }
	disjoint_set(int n): n(n), _group_count(n), p(n, -1), group(n){
		ASSERT(n >= 0);
		for(auto i = 0; i < n; ++ i) group[i] = {i};
	}
	int make_set(){
		p.push_back(-1);
		group.push_back(list<int>{n});
		++ _group_count;
		return n ++;
	}
	int root(int u){
		ASSERT(0 <= u && u < n);
		return p[u] < 0 ? u : p[u] = root(p[u]);
	}
	bool share(int u, int v){
		ASSERT(0 <= min(u, v) && max(u, v) < n);
		return root(u) == root(v);
	}
	int size(int u){
		ASSERT(0 <= u && u < n);
		return -p[root(u)];
	}
	bool merge(int u, int v){
		ASSERT(0 <= min(u, v) && max(u, v) < n);
		u = root(u), v = root(v);
		if(u == v) return false;
		-- _group_count;
		if constexpr(Enable_small_to_large) if(p[u] > p[v]) swap(u, v);
		p[u] += p[v], p[v] = u;
		group[u].splice(group[u].end(), group[v]);
		return true;
	}
	bool merge(int u, int v, auto act){
		ASSERT(0 <= min(u, v) && max(u, v) < n);
		u = root(u), v = root(v);
		if(u == v) return false;
		-- _group_count;
		bool swapped = false;
		if constexpr(Enable_small_to_large) if(p[u] > p[v]) swap(u, v), swapped = true;
		act(u, v, swapped);
		p[u] += p[v], p[v] = u;
		group[u].splice(group[u].end(), group[v]);
		return true;
	}
	int group_count() const{
		return _group_count;
	}
	const list<int> &group_of(int u){
		ASSERT(0 <= u && u < n);
		return group[root(u)];
	}
	vector<vector<int>> group_up(){
		vector<vector<int>> g(n);
		for(auto i = 0; i < n; ++ i) g[root(i)].push_back(i);
		g.erase(remove_if(g.begin(), g.end(), [&](auto &s){ return s.empty(); }), g.end());
		return g;
	}
	void clear(){
		_group_count = n;
		fill(p.begin(), p.end(), -1);
		for(auto i = 0; i < n; ++ i) group[i] = {i};
	}
	friend ostream &operator<<(ostream &out, disjoint_set dsu){
		auto gs = dsu.group_up();
		out << "{";
		if(!gs.empty()) for(auto i = 0; i < (int)gs.size(); ++ i){
			out << "{";
			for(auto j = 0; j < (int)gs[i].size(); ++ j){
				out << gs[i][j];
				if(j + 1 < (int)gs[i].size()) out << ", ";
			}
			out << "}";
			if(i + 1 < (int)gs.size()) out << ", ";
		}
		return out << "}";
	}
#undef ASSERT
};

#define int long long


const int N = 5e5 + 5;

int n, m, q, value, res[N], qu[N], qv[N];

void Hollwo_Pelw(){
	cin >> n >> m >> q >> value;	
	vector<array<int, 3>> edges(m);

	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		-- u, -- v;
		edges[i] = {u, v, w};
	}


	for (int i = 0; i < q; i++) {
		cin >> qu[i] >> qv[i];
		qu[i] --, qv[i] --;
	}

	disjoint_set<false> dis(n);

	int cur = 0;
	for (int bit = 60; bit --; ) {
		if (value >> bit & 1) {
			cur |= 1ll << bit;
		} else {
			int tmp = cur | (1ll << bit);

			dis.clear();
			for (auto &e : edges) {
				if ((e[2] & tmp) == tmp) {
					dis.merge(e[0], e[1]);
				}
			}

			for (int i = 0; i < q; i++) {
				res[i] |= dis.share(qu[i], qv[i]);
			}
		}
	}

	dis.clear();
	for (auto &e : edges) {
		if ((e[2] & cur) == cur) {
			dis.merge(e[0], e[1]);
		}
	}

	for (int i = 0; i < q; i++) {
		res[i] |= dis.share(qu[i], qv[i]);

		if (res[i]) {
			cout << "Yes\n";
		} else {
			cout << "No\n";
		}

	}
}