#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second

using namespace std;
const int N = 1e5 + 7;

int n, m;
vector<vector<int>> adj;
int depth[N], low[N], parent[N], visited[N];
bool mark[N];

void tarjan(int u, int d) {
	visited[u] = true;
	depth[u] = d;
	low[u] = d;
	int childCount = 0;
	bool isArticulationPoint = false;

	for (int v: adj[u]) {
		if (v == parent[u]) continue;
		if (!visited[v]) {
			parent[v] = u;
			tarjan(v, d + 1);
			childCount++;
			low[u] = min(low[u], low[v]);
			if (low[v] >= depth[u]) {
				isArticulationPoint = true;
			}
		} else {
			low[u] = min(low[u], depth[v]);
		}
	}

	if (isArticulationPoint && parent[u] != 0) {
		bool check = low[u] < depth[u];
		for (int v: adj[u]) {
			if (v == parent[u] || parent[v] != u || low[v] < depth[u]) continue;
			if (low[v] != depth[u]) {
				check = false;
			}
		}
		mark[u] |= check;
	}
}

void solve() {
	cin >> n >> m;
	adj.assign(n + 1, vector<int>());

	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for (int i = 1; i <= n; ++i) {
		mark[i] = false;
	}

	for (int u = 1; u <= min(n, 10); ++u) {
		for (int i = 1; i <= n; ++i) {
			depth[i] = 0, low[i] = 0, parent[i] = 0, visited[i] = false;
		}
		tarjan(u, 0);	
	}

	bool found = false;
	for (int i = 1; i <= n; ++i) {
		if (mark[i]) {
			found = true;
			cout << i << " ";
		}
	}
	if (!found) {
		cout << "Empty\n";
	} else {
		cout << '\n';
	}
}

int main() {
#ifdef LOCAL
	freopen("main.inp", "r", stdin);
	freopen("main.out", "w", stdout);
#endif
	ios::sync_with_stdio(0);
	cin.tie(0);
	int test = 1;
	cin >> test;
	while (test--)
		solve();
	return 0;
}