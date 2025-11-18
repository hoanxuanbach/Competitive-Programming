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
	cin >> testcases;
	for (int test = 1; test <= testcases; test++){
		// cout << "Case #" << test << ": ";
		Hollwo_Pelw();
	}
#ifdef hollwo_pelw_local
	auto end = steady_clock::now();
	cout << "\nExecution time : " << duration_cast<milliseconds> (end - start).count() << "[ms]" << endl;
#endif
}

#define ll long long
#define sz(v) (int)(v.size())
#define vi vector<int>

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		for (int L = 0; L <= 30; L++) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

const int N = 2005;

vector<tuple<int, int, int>> vec[N][N];

void Hollwo_Pelw(){
	int n, m;
	cin >> n >> m;
	Dinic mf(n + m + 2);

	int S = n + m, T = n + m + 1;

	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);

		vec[x1][y1].push_back({x2, y2, i});
		mf.addEdge(S, i, 1);
	}

	for (int i = 0; i < m; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);

		for (int sx = max(0, x1 - 3); sx < x2; sx++) {
			for (int sy = max(0, y1 - 3); sy < y2; sy++) {
				for (auto [ex, ey, j] : vec[sx][sy]) {

					int xl = max(sx, x1);
					int xr = min(ex, x2);

					int yl = max(sy, y1);
					int yr = min(ey, y2);

					if (xl >= xr || yl >= yr) {
						continue ;
					}

					int GD = (xr - xl) * (yr - yl);
					int D = (ex - sx) * (ey - sy);

					if (2 * GD >= D) {
						mf.addEdge(j, i + n, 1);
					}
				}
			}
		}
		mf.addEdge(i + n, T, 1);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			vec[i][j].clear();
		}
	}

	cout << mf.calc(S, T) << '\n';
}