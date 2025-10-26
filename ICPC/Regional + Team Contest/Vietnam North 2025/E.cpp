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

const long double EPS = 1e-12;
const int INF = 2; // it doesn't actually have to be infinity or a big number

int gauss (vector < vector<long double> > a, vector<long double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                long double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        long double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}

const int N = 505;

int deg[N], adj[N][N];

void Hollwo_Pelw(){
	int n, m;
	cin >> n >> m;
	vector<vector<long double>> coef(n, vector<long double>(n + 1));
	vector<long double> ans;

	vector<pair<int, int>> ed(m);

	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		-- u, -- v;
		deg[u] ++, deg[v] ++;
		adj[u][v] = adj[v][u] = 1;
		
		ed[i - 1] = {u, v};
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n; j++) {
			// coef[i][n] += (adj[i][j] > 0);
			coef[i][j] -= (long double) (adj[i][j] > 0) / deg[j];
 		}
 		coef[i][i] = 1;
	}

	coef[n - 1][n] = 0;
	coef[n - 1][n - 1] = 1;

	coef[0][n] ++;

	int num = gauss(coef, ans);

	auto g = [&](const pair<int, int> a) {
		return ans[a.first] / deg[a.first] + ans[a.second] / deg[a.second];
	};

	sort(ed.begin(), ed.end(), [&](const pair<int, int> &a, const pair<int, int> &b){
		return g(a) > g(b);
	});

	long double res = 0;

	for (int i = 0; i < m; i++) {
		res += g(ed[i]) * (i + 1);
	}

	// cout << res << '\n';
	// assert(res == 1);

	cout << fixed << setprecision(3);
	cout << res << '\n';
}
