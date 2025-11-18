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

const int N = 1e3 + 5, W = 1 << 12;

struct disjoint_set {
	int par[N];
	disjoint_set() {
		iota(par, par + N, 0);
	}
	disjoint_set(int n) {
		iota(par, par + n, 0);
	}

	void reset(int n) {
		iota(par, par + n, 0);
	}
	
	int find(int u) {
		return par[u] == u ? u : par[u] = find(par[u]);
	}
	
	bool merge(int u, int v) {
		u = find(u), v = find(v);
		if (u == v) {
			return 0;
		}

		return par[u] = v, 1;
	}

	bool connect(int u, int v) {
		return find(u) == find(v);
	}
} trie[W];

int n, q;


void update(int b, int u, int v, int w) {
	if (b == -1) {
		trie[w].merge(u, v);
		return ;
	}

	if (trie[w].connect(u, v)) {
		return ;
	}

	if ((w >> b & 1) ) {
		update(b - 1, u, v, w ^ (1 << b));
	}

	update(b - 1, u, v, w);
}

void Hollwo_Pelw(){
	cin >> n >> q;

	for (int  i = 0;  i < W; i++) {
		trie[i].reset(n);
	}

	long long res = 0;

	for (int i = 0, u, v, w; i < q; i++) {
		char c;
		cin >> c >> u >> v;
		-- u, -- v;

		if (c == '+') {
			cin >> w;
			update(11, u, v, w);
		} else {
			int p = 0;
			
			if (!trie[p].connect(u, v)) {
				res += -1;
				continue ;
			}

			for (int b = 11; b >= 0; b --) {
				if (trie[p ^ (1 << b)].connect(u, v)) {
					p ^= 1 << b;
				}
			}

			res += p;
			// cout << p << '\n';
		}
	}

	cout << res << '\n';
}

// trie[mask] -> connect every mask