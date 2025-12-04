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

const int N = 2e5 + 5;

int n, d[N], par[N], child[N];
vector<int> adj[N];

void dfs(int u, int p) {
	par[u] = p;
	for (int v : adj[u]) if (v != p) {
		d[v] = d[u] + 1;
		dfs(v, u);
		child[u] += (child[v] > 0);
	}
}

vector<int> find_diameter() {
	d[1] = 0;
	dfs(1, 0);
	int r = max_element(d + 1, d + n + 1) - d;

	d[r] = 0;
	dfs(r, 0);
	int p = max_element(d + 1, d + n + 1) - d;

	vector<int> path = {};
	while (p != 0) {
		path.push_back(p);
		p = par[p];
	}

	return path;
}

void Hollwo_Pelw(){
	cin >> n;
	for (int i = 1; i <= n; i++) {
		adj[i].clear();
	}
	for (int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	if (n == 2) {
		cout << "2 1\n";
		return ;
	}

	auto path = find_diameter();

	// res[1] = number of candidate leaf
	// res[2] .. res[mid] = res[i - 1] + 1

	int maxd = (path.size() - 1) / 2;

	vector<pair<int, int>> q;

	if ((int)path.size() % 2 == 1) {
		// center point
		int r = path[path.size() / 2];

		d[r] = 0;
		dfs(r, 0);

		for (int i = 1; i <= n; i++) {
			child[i] = d[i] == maxd ? 1 : 0;
		}

		dfs(r, 0);

		q.push_back({r, -1});

	} else {
		// center edge
		int r1 = path[path.size() / 2];
		int r2 = path[path.size() / 2 - 1];

		d[r1] = d[r2] = 0;
		dfs(r1, r2);
		dfs(r2, r1);

		for (int i = 1; i <= n; i++) {
			child[i] = d[i] == maxd ? 1 : 0;
		}

		dfs(r1, r2);
		dfs(r2, r1);

        int mn=min(child[r1],child[r2]);

		if(child[r1]==mn) q.push_back({r1, r1});
		if(child[r2]==mn) q.push_back({r2, r2});
	}

	vector<int> res;

	int s = count(d + 1, d + n + 1, maxd);

	for (int i = 0; i <= (int)path.size()/ 2; i++) {
		res.push_back(s + i);
	}

	// cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";

	// for (int i = 1; i <= n; i++) {
	// 	if (d[i] == 0) {
	// 		cout << "mid = " << i << '\n';
	// 	}
	// }
    int t=path.size()&1;
	for (int i=0;i<maxd;i++) {
		vector<pair<int, int>> nq;
		int best_child=n,mn=n;

		for (auto [u, g] : q){
			// cout << u << ' ' << g << ' ' << '\n';
            int cnt=0;
			for (int v : adj[u]) if (par[u] != v && child[v]) {
				// child
                cnt++;
				if (best_child > child[v]) {
					best_child = child[v];
					nq.clear();
				}
				if (best_child == child[v]) {
					int ng = g == -1 ? v : g;
					nq.push_back({v, ng});
				}
			}
            mn=min(mn,cnt);
		}
		// cout << "LAYER " << i << '\n';
		// for (auto [v, ng] : nq) {
		// 	cout << child[v] << " : " << v << ' ' << ng << '\n';
		// }
		// cout << best_child << '\n';
		q = nq;

		if(i==0){
			res.push_back(res.back() + max(1,mn-t));
		}        
		if(i+1<maxd) res.push_back(res.back() + best_child);
    }
    int sz=(int)res.size();
    res[sz-1]-=res[sz-2];
    
	for (int x : res) {
		cout << x << ' ';
	}

	cout << '\n';
}