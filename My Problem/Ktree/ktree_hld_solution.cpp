#include <bits/stdc++.h>
using namespace std;
 
void just_do_it();
 
int main() {
	#ifdef KAMIRULEZ
		freopen("kamirulez.inp", "r", stdin);
		freopen("kamirulez.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	just_do_it();
	return 0;
}
 
const long long inf = 1e18L + 20;
const int maxN = 1e5 + 20;
set<pair<long long, int>> S[maxN][2];
vector<pair<int, int>> adj[maxN];
long long depth[maxN];
int dist[maxN];
int C[maxN];
int par[maxN];
int sz[maxN];
int head[maxN];
int heavy[maxN];
int Tin[maxN];
int Tout[maxN];
int dfs_T;
 
struct segment_tree {
	pair<long long, int> tree[maxN << 2];
	int N;
 
	void init(int _N) {
		N = _N;
		for (int i = 1; i <= (N << 2); i++) {
			tree[i] = make_pair(-inf, -1);
		}
	}
 
	void update(int id, int lt, int rt, int pos, pair<long long, int> val) {
		if (lt == rt) {
			tree[id] = val;
			return;
		}
		int mt = (lt + rt) >> 1;
		if (pos <= mt) {
			update(id << 1, lt, mt, pos, val);
		}
		else {
			update(id << 1 | 1, mt + 1, rt, pos, val);
		}
		tree[id] = max(tree[id << 1], tree[id << 1 | 1]);
	}
 
	void update(int pos, pair<long long, int> val) {
		update(1, 1, N, pos, val);
	}
 
	pair<long long, int> get(int id, int lt, int rt, int ql, int qr) {
		if (lt == ql && rt == qr) {
			return tree[id];
		}
		int mt = (lt + rt) >> 1;
		if (qr <= mt) {
			return get(id << 1, lt, mt, ql, qr);
		}
		else if (ql >= mt + 1) {
			return get(id << 1 | 1, mt + 1, rt, ql, qr);
		}
		else {
			return max(get(id << 1, lt, mt, ql, mt), get(id << 1 | 1, mt + 1, rt, mt + 1, qr));
		}
	}
 
	pair<long long, int> get(int ql, int qr) {
		if (ql > qr) {
			return make_pair(-inf, -1);
		}
		else {
			return get(1, 1, N, ql, qr);
		}
	}
 
} sub[2], path[2];
 
void dfs1(int u, int p) {
	par[u] = p;
	sz[u] = 1;
	for (auto [v, w]: adj[u]) {
		if (v == p) {
			continue;
		}
		par[v] = u;
		dist[v] = dist[u] + 1;
		depth[v] = depth[u] + w;
		dfs1(v, u);
		if (sz[v] > sz[heavy[u]]) {
			heavy[u] = v;
		}
		sz[u] += sz[v];
	}
}
 
void dfs2(int u) {
	Tin[u] = ++dfs_T;
	if (heavy[u]) {
		head[heavy[u]] = head[u];
		dfs2(heavy[u]);
		for (auto [v, w]: adj[u]) {
			if (v != par[u] && v != heavy[u]) {
				head[v] = v;
				dfs2(v);
			}
		}
	}
	Tout[u] = dfs_T;
}
 
void update(int u, int X, int type) {
	sub[X].update(Tin[u], (type ? make_pair(depth[u], u) : make_pair(-inf, -1)));
	long long tmp1 = depth[u];
	int tmp2 = u;
	if (type) {
		S[u][X].emplace(-tmp1, u);
	}
	else {
		S[u][X].erase(make_pair(-tmp1, u));
	}
	path[X].update(Tin[u], (S[u][X].empty() ? make_pair(-inf, -1) : *S[u][X].rbegin()));
	while (true) {
		u = head[u];
		if (u == 1) {
			break;
		}
		int pu = par[u];
		if (type) {
			S[pu][X].emplace(tmp1 - depth[pu] * 2, tmp2);
		}
		else {
			S[pu][X].erase(make_pair(tmp1 - depth[pu] * 2, tmp2));
		}
		path[X].update(Tin[pu], (S[pu][X].empty() ? make_pair(-inf, -1) : *S[pu][X].rbegin()));
		u = pu;
	}
}
 
int get_LCA(int u, int v) {
	while (head[u] != head[v]) {
		if (dist[head[u]] < dist[head[v]]) {
			swap(u, v);
		}
		u = par[head[u]];
	}
	if (dist[u] > dist[v]) {
		swap(u, v);
	}
	return u;
}
 
void flip(int u) {
	update(u, C[u], 0);
	C[u] ^= 1;
	update(u, C[u], 1);
}
 
pair<long long, int> get_path(int u, int v, int X) {
	long long tmp = depth[u];
	pair<long long, int> best = sub[X].get(Tin[u], Tout[u]);
	best.first -= tmp;
	while (head[u] != head[v]) {
		pair<long long, int> cur = path[X].get(Tin[head[u]], Tin[u] - 1);
		cur.first += tmp;
		best = max(best, cur);
		int pu = par[u];
		cur = sub[X].get(Tin[pu], Tin[u] - 1);
		cur.first += tmp - depth[pu] * 2;
		best = max(best, cur);
		cur = sub[X].get(Tout[u] + 1, Tout[pu]);
		cur.first += tmp - depth[pu] * 2;
		best = max(best, cur);
		u = pu;
	}
	pair<long long, int> cur = path[X].get(Tin[v], Tin[u] - 1);
	cur.first += tmp;
	best = max(best, cur);
	return best;
}
 
void just_do_it() {
	int N, Q;
	cin >> N >> Q;
	sub[0].init(N);
	sub[1].init(N);
	path[0].init(N);
	path[1].init(N);
	for (int u = 1; u <= N; u++) {
		cin >> C[u];
	}
	for (int i = 0; i < N - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}
	dfs1(1, -1);
	head[1] = 1;
	dfs2(1);
	for (int u = 1; u <= N; u++) {
		update(u, C[u], 1);
	}
	for (int i = 0; i < Q; i++) {
		int type;
		cin >> type;
		if (type == 1) {
			int u;
			cin >> u;
			flip(u);
		}
		else {
			int u, v, X, K;
			cin >> u >> v >> X >> K;
			int LCA = get_LCA(u, v);
 			vector<pair<long long, int>> res;
			for (int j = 0; j < K; j++) {
				pair<long long, int> best;
				if (LCA == u) {
					best = get_path(v, u, X);
				}
				else {
					best = sub[X].get(Tin[u], Tout[u]);
					best.first += depth[v] - depth[LCA] * 2;
				}
				res.push_back(best);
				if (j < K - 1) {
					flip(res.back().second);
				}
			}
			for (int j = 0; j < K; j++) {
				cout << res[j].first << " ";
			}
			cout << '\n';
			for (int j = 0; j < K - 1; j++) {
				flip(res[j].second);
			}
		}
	}
}
